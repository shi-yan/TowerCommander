/*
 *  GameMap.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "GameMap.h"
#include "MoneyBar.h"
#include "SmallAnimationManager.h"
#include "TowerFactory.h"
#include "CurrentLevelStatistics.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void GameMap::init(PointI _dimension,int _screenWidth,int _screenHeight)
		{
			screenWidth=_screenWidth;
			screenHeight=_screenHeight;
		
			halfScreenWidth=(int)(screenWidth*0.5f);
			halfScreenHeight=(int)(screenHeight*0.5f);
		
			tileHSize=screenWidth/TileSize+2;
		
			if(screenWidth%TileSize!=0)
				tileHSize++;
		
			tileVSize=screenHeight/TileSize+2;
		
			if(screenHeight%TileSize!=0)
				tileVSize++;
		
			dimension = _dimension;
			mapTile = new int[dimension.x*dimension.y];
			collisionTile = new CollisionTileType[dimension.x* dimension.y];
		}
		
		void GameMap::upgradeATowerAt(int _x,int _y,int id)
		{
			Tower *tower=towerMatrix[_x+_y*dimension.x];
			
			if (tower) 
			{
				
				towerMatrix[_x+_y*dimension.x]=NULL;
				
				PointI towerPos(_x,_y);
				
				
				float r=tower->getRange();
				int range=(r-(float)(TileSize*0.5f))/(float)TileSize+1.0f;
				
				int xmin=_x-range>=0?_x-range:0;
				int xmax=_x+range<dimension.x?_x+range:dimension.x-1;
				
				int ymin=_y-range>=0?_y-range:0;
				int ymax=_y+range<dimension.y?_y+range:dimension.y-1;
				
				for(int	ax=xmin;ax<=xmax;++ax)
					for(int ay=ymin;ay<=ymax;++ay)
					{
						std::vector<PointI> &sl=shootingCache[ax+dimension.x*ay];
						
						for (int i=0; i<(int)sl.size(); ++i) 
						{
							if (sl[i]==towerPos) 
							{
								sl[i]=sl[0];
								break;
							}
						}
						
						sl.erase(sl.begin());
						
					}
				
				
				
				for (int i=0; i<(int)towerPool.size(); ++i) 
				{
					if (towerPool[i]==tower) 
					{
						towerPool[i]=towerPool[0];
					}
				}
				towerPool.erase(towerPool.begin());
				delete tower;
				
				tower=TowerFactory::getSingleton().getTower(_x, _y, id);
				insertATower(tower, _x, _y);
				
				
				SmallAnimationManager::getSingleton().addExplosion(_x*TileSize+TileSize*0.5f,_y*TileSize,1);
			}
		}

	
		bool GameMap::insertATower(Tower *tower, int x,int y)
		{
			
			if(towerMatrix[x+y*dimension.x]!=0)
			{
				SmallAnimationManager::getSingleton().addNotification(2);
				return false;
			}
    	
			if(collisionTile[x+y*dimension.x]!=Path)
			{
				
				SmallAnimationManager::getSingleton().addNotification(2);
				return false;
			}
    	
			for(std::vector<Enemy*>::iterator iter=enemyPool.begin();iter!=enemyPool.end();++iter)
			{
				if((*iter)->getEnemyType()!=Enemy::Air && (*iter)->position.x==x && (*iter)->position.y==y)
				{
					
					SmallAnimationManager::getSingleton().addNotification(2);
					return false;
				}
			}
    	
			PointI tempBlockPoint(x,y);
			
			for (std::vector<PointI>::iterator iter=startPoints.begin(); iter!=startPoints.end(); ++iter) 
			{
				pathFindEnemy->setPosition(*iter);
				std::deque<PointI> tmppath;
				if(!pathFindEnemy->findTempPathWithTempBlock(tmppath,tempBlockPoint))
				{
					
					SmallAnimationManager::getSingleton().addNotification(1);
					return false;
				}
			}
			
			
    	
			for(int i=0;i<(int)enemyPool.size();++i)
			{
				if (enemyPool[i]->getEnemyType()!=Enemy::Air) 
				{
					
				
					std::deque<PointI> tmppath;
			
					if(enemyPool[(i)]->findTempPathWithTempBlock(tmppath, tempBlockPoint))
					{

						//
						
						//在这改
						Enemy::WalkDirection beforeDirection = enemyPool[i]->direction;
						Enemy::WalkDirection afterDirection=Enemy::NONEDIR;
						
						if (tmppath.size()>1) 
						{
							if (tmppath[1].y < tmppath[0].y)
							{
								afterDirection = Enemy::North;
							}
							else if (tmppath[1].y > tmppath[0].y)
							{
								afterDirection = Enemy::South;
							}
							else if (tmppath[1].x > tmppath[0].x)
							{
								afterDirection = Enemy::East;    
							}
							else if (tmppath[1].x < tmppath[0].x)
							{
								afterDirection = Enemy::West;    
							}
						
						
							enemyPool[i]->path.clear();
						
						
							if (beforeDirection==afterDirection) 
							{
								enemyPool[i]->path.resize(tmppath.size());
								std::copy(tmppath.begin(),tmppath.end(),enemyPool[i]->path.begin());
								enemyPool[(i)]->pathStep=0;
							}
							else 
							{
								bool isOldProtentialBlocked=false;
							
								switch (beforeDirection) 
								{
									case Enemy::North:
									if (tempBlockPoint.y==tmppath[0].y-1 && tempBlockPoint.x==tmppath[0].x) 
									{
										isOldProtentialBlocked=true;
									}
									break;
									
									case Enemy::South:
										if (tempBlockPoint.y==tmppath[0].y+1 && tempBlockPoint.x==tmppath[0].x) 
										{
											isOldProtentialBlocked=true;
										}
									break;
									case Enemy::East:
										if (tempBlockPoint.y==tmppath[0].y && tempBlockPoint.x+1==tmppath[0].x) 
										{
											isOldProtentialBlocked=true;
										}
									break;
									case Enemy::West:
										if (tempBlockPoint.y==tmppath[0].y && tempBlockPoint.x-1==tmppath[0].x) 
										{
											isOldProtentialBlocked=true;
										}
									break;
									
								}
								
								if (isOldProtentialBlocked) {
									enemyPool[i]->path.resize(tmppath.size());
									std::copy(tmppath.begin(),tmppath.end(),enemyPool[i]->path.begin());
									enemyPool[(i)]->pathStep=0;
									enemyPool[(i)]->moved = 0.0f;		
								}
								else 
								{
									enemyPool[i]->path.resize(tmppath.size()+1);
									
									switch (beforeDirection) {
										case Enemy::North:
											enemyPool[i]->path[0]=PointI(tmppath[0].x,tmppath[0].y-1);
											enemyPool[i]->direction=Enemy::South;
											enemyPool[i]->setAnimation(Enemy::South);
											break;
										case Enemy::South:
											enemyPool[i]->path[0]=PointI(tmppath[0].x,tmppath[0].y+1);
											enemyPool[i]->direction=Enemy::North;
											enemyPool[i]->setAnimation(Enemy::North);
											break;
										case Enemy::West:
											enemyPool[i]->path[0]=PointI(tmppath[0].x-1,tmppath[0].y);
											enemyPool[i]->direction=Enemy::East;
											enemyPool[i]->setAnimation(Enemy::East);
											break;
										case Enemy::East:
											enemyPool[i]->path[0]=PointI(tmppath[0].x+1,tmppath[0].y);
											enemyPool[i]->direction=Enemy::West;
											enemyPool[i]->setAnimation(Enemy::West);
											break;
									}
									
								//	printf("new direction: %d\n",enemyPool[i]->direction);
								//	printf("new animation id: %d\n",enemyPool[i]->currentAnimationID);
									
									//	printf("new path: %d,%d\n",enemyPool[i]->path[0].x,enemyPool[i]->path[0].y);
									std::copy(tmppath.begin(),tmppath.end(),enemyPool[i]->path.begin()+1);
									
									//printf("new path: %d,%d\n",enemyPool[i]->path[0].x,enemyPool[i]->path[0].y);
									
									enemyPool[(i)]->pathStep=0;
									enemyPool[(i)]->moved =1.0f-enemyPool[i]->moved;	
									
									
									
								}

							
							
							}

						

						
						}
						else
						{
							enemyPool[i]->path.resize(tmppath.size());
							std::copy(tmppath.begin(),tmppath.end(),enemyPool[i]->path.begin());
							enemyPool[(i)]->pathStep=0;
							enemyPool[i]->moved=0.0f;
						}
					}
					else
					{
					
						SmallAnimationManager::getSingleton().addNotification(1);
						return false;
					}
				}
			}
    	
    	
			tower->setPosition(PointI(x,y)); 
			towerPool.push_back(tower);
			towerMatrix[x+y*dimension.x]=tower;
			
			
			float r=tower->getRange();
			int range=(r-(float)(TileSize*0.5f))/(float)(TileSize)+1.0f;
			
			int xmin=x-range>=0?x-range:0;
			int xmax=x+range<dimension.x?x+range:dimension.x-1;
    		
			int ymin=y-range>=0?y-range:0;
			int ymax=y+range<dimension.y?y+range:dimension.y-1;
			
			for(int	ax=xmin;ax<=xmax;++ax)
				for(int ay=ymin;ay<=ymax;++ay)
				{
					shootingCache[ax+dimension.x*ay].push_back(PointI(x,y));
					
					//	printf("insert %d\n",ax+dimension.x*ay);
				}
		
			return true;
		}
    
		void GameMap::shotAtEnemies()
		{
			for(std::vector<Tower*>::iterator iter=towerPool.begin();iter!=towerPool.end();++iter)
			{
				
				(*iter)->afterShootingAtEnemy();
			}
		
			int k=0;
		
			for(std::vector<Enemy*>::iterator iter=enemyPool.begin();iter!=enemyPool.end();++iter)
			{
				(*iter)->setSlowDownRate(1.0f);
				
				if(shootingCache[(*iter)->position.x+(*iter)->position.y*dimension.x].size()>0)
				{
					std::vector<PointI>::iterator begina=shootingCache[(*iter)->position.x+(*iter)->position.y*dimension.x].begin();
					
					std::vector<PointI>::iterator enda=shootingCache[(*iter)->position.x+(*iter)->position.y*dimension.x].end();
					
					
					for(std::vector<PointI>::iterator itera=begina;itera!=enda;++itera)
					{
						towerMatrix[(*itera).x+dimension.x*(*itera).y]->shotAtEnemy(k,(*iter));
					}
				}
				
				(*iter)->applyLastingDamage();
				k++;
			}
		}
	
		std::vector<PointI> & GameMap::getStartPoints()
		{
			return startPoints;
		}
		
		void GameMap::loadFromFile(const char* filename,int _screenWidth,int _screenHeight)
		{
			
			
			mapCenterPosition.x=0;
			mapCenterPosition.y=0;
			
			screenWidth=_screenWidth;
			screenHeight=_screenHeight;
		
			halfScreenWidth=(int)(screenWidth*0.5f);
			halfScreenHeight=(int)(screenHeight*0.5f);
		
			tileHSize=screenWidth/TileSize+2;
		
			if(screenWidth%TileSize!=0)
				tileHSize++;
		
			tileVSize=screenHeight/TileSize+2;
		
			if(screenHeight%TileSize!=0)
				tileVSize++;
    	
			int uniqueTileCount=0;
		
			std::map<int, int> existTiles;
//#ifdef __ANDROID__
			FILE *fc = fopen(filename,"rb");
//#else
			
//			FILE *fc = fopen("../../../../assets/exportedmap3.map","rb");
//#endif
			int width=0;
			fread(&width, sizeof(int), 1, fc);
		
			int height=0;
			fread(&height, sizeof(int), 1, fc);
		
			dimension=PointI(width,height);
		
			mapTile=new int[width*height];
			towerMatrix=new Tower*[width*height];
			shootingCache=new std::vector<PointI>[width*height];
			
			Enemy::initializeEnemyOrder(height);
		
			for(int x=0;x<dimension.x;++x)
				for(int y=0;y<dimension.y;++y)
					towerMatrix[x+y*dimension.x]=NULL;
		
			int *tempMapTile=new int[width*height];
		
			for(int y=0;y<dimension.y;++y)
				for(int x=0;x<dimension.x;++x)
				{
					int originalTileID=0;
					fread(&originalTileID, sizeof(int), 1, fc);
				
					tempMapTile[x+dimension.x*y]=originalTileID;
				
					if(existTiles.find(originalTileID)==existTiles.end())
					{
						
						//printf("original tile id %d\n",originalTileID);
						existTiles[originalTileID]= uniqueTileCount;
						uniqueTileCount++;
					}
				}
			
			int *tempObstacleLists=new int[dimension.y*dimension.x];
			
			std::map<int,int> existObstableTiles;
	
			int uniqueObstacleTileCount=0;
			
			for (int y=0; y<dimension.y; ++y) 
			{
				for (int x=0; x<dimension.x; ++x) 
				{
					int originalTileID=0;
					fread(&originalTileID, sizeof(int), 1, fc);
					
					if (originalTileID!=-1) 
					{
						
					
						tempObstacleLists[x+y*dimension.x]=(originalTileID);
					
					
						if (existObstableTiles.find(originalTileID)==existObstableTiles.end()) {
							existObstableTiles[originalTileID]=uniqueObstacleTileCount++;
						}
					}
						
						else {
							tempObstacleLists[x+y*dimension.x]=-1;
						}

					
				}
			}
			
			fclose(fc);
			
			
			std::vector<std::string> obstacleTilenameList;
					int realpos=0;
			for (std::map<int,int>::iterator iter=existObstableTiles.begin(); iter!=existObstableTiles.end(); ++iter) {
				int tilepos=iter->second;
				int originalTileID=iter->first;
				
				std::string tilename="";
				
				printf("obstacle original id %d\n",originalTileID);
				switch (originalTileID) 
				{
#ifdef __ANDROID__
					case 0: tilename="obstacleTile/bg1169.png";break;
					case 1: tilename="obstacleTile/bg2129.png";break;
					case 2: tilename="obstacleTile/bg3089.png";break;
					case 3: tilename="obstacleTile/bg4049.png";break;
					case 4: tilename="obstacleTile/bg4528.png";break;
					case 5: tilename="obstacleTile/bg4529.png";break;
					case 6: tilename="obstacleTile/bg689.png";break;
					case 7: tilename="obstacleTile/house1.png";break;
					case 8: tilename="obstacleTile/house2.png";break;
					case 9: tilename="obstacleTile/house3.png";break;
					case 10: tilename="obstacleTile/house4.png";break;
					case 11: tilename="obstacleTile/tree.png";break;
					case 12: tilename="obstacleTile/tree2.png";break;
					case 13: tilename="obstacleTile/trr1.png";break;
					case 14: tilename="obstacleTile/trr2.png";break;
						
#else
	
					case 0: tilename="../../../../assets/obstacleTile/bg1169.png";break;
					case 1: tilename="../../../../assets/obstacleTile/bg2129.png";break;
					case 2: tilename="../../../../assets/obstacleTile/bg3089.png";break;
					case 3: tilename="../../../../assets/obstacleTile/bg4049.png";break;
					case 4: tilename="../../../../assets/obstacleTile/bg4528.png";break;
					case 5: tilename="../../../../assets/obstacleTile/bg4529.png";break;
					case 6: tilename="../../../../assets/obstacleTile/bg689.png";break;
					case 7: tilename="../../../../assets/obstacleTile/house1.png";break;
					case 8: tilename="../../../../assets/obstacleTile/house2.png";break;
					case 9: tilename="../../../../assets/obstacleTile/house3.png";break;
					case 10: tilename="../../../../assets/obstacleTile/house4.png";break;
					case 11: tilename="../../../../assets/obstacleTile/tree.png";break;
					case 12: tilename="../../../../assets/obstacleTile/tree2.png";break;
					case 13: tilename="../../../../assets/obstacleTile/trr1.png";break;
					case 14: tilename="../../../../assets/obstacleTile/trr2.png";break;
#endif
						
						
					default:break;
				}
				
				obstacleTilenameList.push_back(tilename);
				iter->second=realpos++;
			}
			
			
			int obstacleSqr=0;
			int obstacleTileAtlas=TextureAtlasManager::getSingleton().addNew(obstacleTilenameList,40,80,obstacleSqr);
			
				
			collisionTile=new CollisionTileType[dimension.x*dimension.y];
			
			startPoints.clear();
			
			for(int x=0;x<dimension.x;++x)
				for(int y=0;y<dimension.y;++y)
				{
					if (tempMapTile[x+dimension.x*y]==125) 
					{
						collisionTile[x+dimension.x*y]=Start;
						startPoints.push_back(PointI(x,y));
					}
					else if(tempMapTile[x+dimension.x*y]==126)
					{
						collisionTile[x+dimension.x*y]=End;
					}
					else
					collisionTile[x+dimension.x*y]=Path;
				}
			
			
			obstacleLists=new std::vector<Sprite*>[dimension.y];
			for (int y=0; y<dimension.y; ++y)
				for (int x=0; x<dimension.x; ++x) 
				{
					if(tempObstacleLists[x+y*dimension.x]!=-1)
					{
						collisionTile[x+dimension.x*y]=Block;
						Sprite *newSprite=new Sprite(0,0,0);
						newSprite->setSize(TileSize,TileSize*2);
						newSprite->setXY(TileSize*x,TileSize*y-TileSize);
						
						int texid=existObstableTiles[tempObstacleLists[x+y*dimension.x]];
						
						//printf("texid %d\n",texid);
						
						newSprite->addTexture( new Texture(obstacleTileAtlas,texid%obstacleSqr*40,texid/obstacleSqr*80,40,80));
						newSprite->setAnimation(0);
						obstacleLists[y].push_back(newSprite);
						
					}
				}
			
			delete [] tempObstacleLists;
			
	
		
			std::vector<std::string> tilenameList;
#ifdef __ANDROID__
			tilenameList.push_back("groundTile/a0.png");
#else
			tilenameList.push_back("../../../../assets/groundTile/a0.png");
#endif
			realpos=1;
			for (std::map<int,int>::iterator iter=existTiles.begin(); iter!=existTiles.end(); ++iter) 
			{
				int tilepos=iter->second;
			
				int	originalTileID=iter->first;
				
			//	printf("_unique id %d\n",tilepos);
			//	printf("_original tile id %d\n",originalTileID);
			
				std::string tilename="";
			
				switch(originalTileID)
				{
						
#ifdef __ANDROID__
					case 0: tilename="groundTile/gt000.png";break;
					case 1: tilename="groundTile/gt001.png";break;
					case 2: tilename="groundTile/gt002.png";break;
					case 3: tilename="groundTile/gt003.png";break;
					case 4: tilename="groundTile/gt004.png";break;
					case 5: tilename="groundTile/gt005.png";break;
					case 6: tilename="groundTile/gt006.png";break;
					case 7: tilename="groundTile/gt007.png";break;
					case 8: tilename="groundTile/gt008.png";break;
					case 9: tilename="groundTile/gt009.png";break;
					case 10: tilename="groundTile/gt010.png";break;
					case 11: tilename="groundTile/gt011.png";break;
					case 12: tilename="groundTile/gt012.png";break;
					case 13: tilename="groundTile/gt013.png";break;
					case 14: tilename="groundTile/gt014.png";break;
					case 15: tilename="groundTile/gt015.png";break;
					case 16: tilename="groundTile/gt016.png";break;
					case 17: tilename="groundTile/gt017.png";break;
					case 18: tilename="groundTile/gt018.png";break;
					case 19: tilename="groundTile/gt019.png";break;
					case 20: tilename="groundTile/gt020.png";break;
					case 21: tilename="groundTile/gt021.png";break;
					case 22: tilename="groundTile/gt022.png";break;
					case 23: tilename="groundTile/gt023.png";break;
					case 24: tilename="groundTile/gt024.png";break;
					case 25: tilename="groundTile/gt025.png";break;
					case 26: tilename="groundTile/gt026.png";break;
					case 27: tilename="groundTile/gt027.png";break;
					case 28: tilename="groundTile/gt028.png";break;
					case 29: tilename="groundTile/gt029.png";break;
					case 30: tilename="groundTile/gt030.png";break;
					case 31: tilename="groundTile/gt031.png";break;
					case 32: tilename="groundTile/gt032.png";break;
					case 33: tilename="groundTile/gt033.png";break;
					case 34: tilename="groundTile/gt034.png";break;
					case 35: tilename="groundTile/gt035.png";break;
					case 36: tilename="groundTile/gt036.png";break;
					case 37: tilename="groundTile/gt037.png";break;
					case 38: tilename="groundTile/gt038.png";break;
					case 39: tilename="groundTile/gt039.png";break;
					case 40: tilename="groundTile/gt040.png";break;
					case 41: tilename="groundTile/gt041.png";break;
					case 42: tilename="groundTile/gt042.png";break;
					case 43: tilename="groundTile/gt043.png";break;
					case 44: tilename="groundTile/gt044.png";break;
					case 45: tilename="groundTile/gt045.png";break;
					case 46: tilename="groundTile/gt046.png";break;
					case 47: tilename="groundTile/gt047.png";break;
					case 48: tilename="groundTile/gt048.png";break;
					case 49: tilename="groundTile/gt049.png";break;
					case 50: tilename="groundTile/gt050.png";break;
					case 51: tilename="groundTile/gt051.png";break;
					case 52: tilename="groundTile/gt052.png";break;
					case 53: tilename="groundTile/gt053.png";break;
					case 54: tilename="groundTile/gt054.png";break;
					case 55: tilename="groundTile/gt055.png";break;
					case 56: tilename="groundTile/gt056.png";break;
					case 57: tilename="groundTile/gt057.png";break;
					case 58: tilename="groundTile/gt058.png";break;
					case 59: tilename="groundTile/gt059.png";break;
					case 60: tilename="groundTile/gt060.png";break;
					case 61: tilename="groundTile/gt061.png";break;
					case 62: tilename="groundTile/gt062.png";break;
					case 63: tilename="groundTile/gt063.png";break;
					case 64: tilename="groundTile/gt064.png";break;
					case 65: tilename="groundTile/gt065.png";break;
					case 66: tilename="groundTile/gt066.png";break;
					case 67: tilename="groundTile/gt067.png";break;
					case 68: tilename="groundTile/gt068.png";break;
					case 69: tilename="groundTile/gt069.png";break;
					case 70: tilename="groundTile/gt070.png";break;
					case 71: tilename="groundTile/gt071.png";break;
					case 72: tilename="groundTile/gt072.png";break;
					case 73: tilename="groundTile/gt073.png";break;
					case 74: tilename="groundTile/gt074.png";break;
					case 75: tilename="groundTile/gt075.png";break;
					case 76: tilename="groundTile/gt076.png";break;
					case 77: tilename="groundTile/gt077.png";break;
					case 78: tilename="groundTile/gt078.png";break;
					case 79: tilename="groundTile/gt079.png";break;
					case 80: tilename="groundTile/gt080.png";break;
					case 81: tilename="groundTile/gt081.png";break;
					case 82: tilename="groundTile/gt082.png";break;
					case 83: tilename="groundTile/gt083.png";break;
					case 84: tilename="groundTile/gt084.png";break;
					case 85: tilename="groundTile/gt085.png";break;
					case 86: tilename="groundTile/gt086.png";break;
					case 87: tilename="groundTile/gt087.png";break;
					case 88: tilename="groundTile/gt088.png";break;
					case 89: tilename="groundTile/gt089.png";break;
					case 90: tilename="groundTile/gt090.png";break;
					case 91: tilename="groundTile/gt091.png";break;
					case 92: tilename="groundTile/gt092.png";break;
					case 93: tilename="groundTile/gt093.png";break;
					case 94: tilename="groundTile/gt094.png";break;
					case 95: tilename="groundTile/gt095.png";break;
					case 96: tilename="groundTile/gt096.png";break;
					case 97: tilename="groundTile/gt097.png";break;
					case 98: tilename="groundTile/gt098.png";break;
					case 99: tilename="groundTile/gt099.png";break;
					case 100: tilename="groundTile/gt100.png";break;
					case 101: tilename="groundTile/gt101.png";break;
					case 102: tilename="groundTile/gt102.png";break;
					case 103: tilename="groundTile/gt103.png";break;
					case 104: tilename="groundTile/gt104.png";break;
					case 105: tilename="groundTile/gt105.png";break;
					case 106: tilename="groundTile/gt106.png";break;
					case 107: tilename="groundTile/gt107.png";break;
					case 108: tilename="groundTile/gt108.png";break;
					case 109: tilename="groundTile/gt109.png";break;
					case 110: tilename="groundTile/gt110.png";break;
					case 111: tilename="groundTile/gt111.png";break;
					case 112: tilename="groundTile/gt112.png";break;
					case 113: tilename="groundTile/gt113.png";break;
					case 114: tilename="groundTile/gt114.png";break;
					case 115: tilename="groundTile/gt115.png";break;
					case 116: tilename="groundTile/gt116.png";break;
					case 117: tilename="groundTile/gt117.png";break;
					case 118: tilename="groundTile/gt118.png";break;
					case 119: tilename="groundTile/gt119.png";break;
					case 120: tilename="groundTile/gt120.png";break;
					case 121: tilename="groundTile/gt121.png";break;
					case 122: tilename="groundTile/gt122.png";break;
					case 123: tilename="groundTile/gt123.png";break;
					case 124: tilename="groundTile/gt124.png";break;
					case 125: tilename="groundTile/gt125.png";break;
					case 126: tilename="groundTile/gt126.png";break;
					default: tilename="groundTile/gt000.png";
						
#else
					case 0: tilename="../../../../assets/groundTile/gt000.png";break;
					case 1: tilename="../../../../assets/groundTile/gt001.png";break;
					case 2: tilename="../../../../assets/groundTile/gt002.png";break;
					case 3: tilename="../../../../assets/groundTile/gt003.png";break;
					case 4: tilename="../../../../assets/groundTile/gt004.png";break;
					case 5: tilename="../../../../assets/groundTile/gt005.png";break;
					case 6: tilename="../../../../assets/groundTile/gt006.png";break;
					case 7: tilename="../../../../assets/groundTile/gt007.png";break;
					case 8: tilename="../../../../assets/groundTile/gt008.png";break;
					case 9: tilename="../../../../assets/groundTile/gt009.png";break;
					case 10: tilename="../../../../assets/groundTile/gt010.png";break;
					case 11: tilename="../../../../assets/groundTile/gt011.png";break;
					case 12: tilename="../../../../assets/groundTile/gt012.png";break;
					case 13: tilename="../../../../assets/groundTile/gt013.png";break;
					case 14: tilename="../../../../assets/groundTile/gt014.png";break;
					case 15: tilename="../../../../assets/groundTile/gt015.png";break;
					case 16: tilename="../../../../assets/groundTile/gt016.png";break;
					case 17: tilename="../../../../assets/groundTile/gt017.png";break;
					case 18: tilename="../../../../assets/groundTile/gt018.png";break;
					case 19: tilename="../../../../assets/groundTile/gt019.png";break;
					case 20: tilename="../../../../assets/groundTile/gt020.png";break;
					case 21: tilename="../../../../assets/groundTile/gt021.png";break;
					case 22: tilename="../../../../assets/groundTile/gt022.png";break;
					case 23: tilename="../../../../assets/groundTile/gt023.png";break;
					case 24: tilename="../../../../assets/groundTile/gt024.png";break;
					case 25: tilename="../../../../assets/groundTile/gt025.png";break;
					case 26: tilename="../../../../assets/groundTile/gt026.png";break;
					case 27: tilename="../../../../assets/groundTile/gt027.png";break;
					case 28: tilename="../../../../assets/groundTile/gt028.png";break;
					case 29: tilename="../../../../assets/groundTile/gt029.png";break;
					case 30: tilename="../../../../assets/groundTile/gt030.png";break;
					case 31: tilename="../../../../assets/groundTile/gt031.png";break;
					case 32: tilename="../../../../assets/groundTile/gt032.png";break;
					case 33: tilename="../../../../assets/groundTile/gt033.png";break;
					case 34: tilename="../../../../assets/groundTile/gt034.png";break;
					case 35: tilename="../../../../assets/groundTile/gt035.png";break;
					case 36: tilename="../../../../assets/groundTile/gt036.png";break;
					case 37: tilename="../../../../assets/groundTile/gt037.png";break;
					case 38: tilename="../../../../assets/groundTile/gt038.png";break;
					case 39: tilename="../../../../assets/groundTile/gt039.png";break;
					case 40: tilename="../../../../assets/groundTile/gt040.png";break;
					case 41: tilename="../../../../assets/groundTile/gt041.png";break;
					case 42: tilename="../../../../assets/groundTile/gt042.png";break;
					case 43: tilename="../../../../assets/groundTile/gt043.png";break;
					case 44: tilename="../../../../assets/groundTile/gt044.png";break;
					case 45: tilename="../../../../assets/groundTile/gt045.png";break;
					case 46: tilename="../../../../assets/groundTile/gt046.png";break;
					case 47: tilename="../../../../assets/groundTile/gt047.png";break;
					case 48: tilename="../../../../assets/groundTile/gt048.png";break;
					case 49: tilename="../../../../assets/groundTile/gt049.png";break;
					case 50: tilename="../../../../assets/groundTile/gt050.png";break;
					case 51: tilename="../../../../assets/groundTile/gt051.png";break;
					case 52: tilename="../../../../assets/groundTile/gt052.png";break;
					case 53: tilename="../../../../assets/groundTile/gt053.png";break;
					case 54: tilename="../../../../assets/groundTile/gt054.png";break;
					case 55: tilename="../../../../assets/groundTile/gt055.png";break;
					case 56: tilename="../../../../assets/groundTile/gt056.png";break;
					case 57: tilename="../../../../assets/groundTile/gt057.png";break;
					case 58: tilename="../../../../assets/groundTile/gt058.png";break;
					case 59: tilename="../../../../assets/groundTile/gt059.png";break;
					case 60: tilename="../../../../assets/groundTile/gt060.png";break;
					case 61: tilename="../../../../assets/groundTile/gt061.png";break;
					case 62: tilename="../../../../assets/groundTile/gt062.png";break;
					case 63: tilename="../../../../assets/groundTile/gt063.png";break;
					case 64: tilename="../../../../assets/groundTile/gt064.png";break;
					case 65: tilename="../../../../assets/groundTile/gt065.png";break;
					case 66: tilename="../../../../assets/groundTile/gt066.png";break;
					case 67: tilename="../../../../assets/groundTile/gt067.png";break;
					case 68: tilename="../../../../assets/groundTile/gt068.png";break;
					case 69: tilename="../../../../assets/groundTile/gt069.png";break;
					case 70: tilename="../../../../assets/groundTile/gt070.png";break;
					case 71: tilename="../../../../assets/groundTile/gt071.png";break;
					case 72: tilename="../../../../assets/groundTile/gt072.png";break;
					case 73: tilename="../../../../assets/groundTile/gt073.png";break;
					case 74: tilename="../../../../assets/groundTile/gt074.png";break;
					case 75: tilename="../../../../assets/groundTile/gt075.png";break;
					case 76: tilename="../../../../assets/groundTile/gt076.png";break;
					case 77: tilename="../../../../assets/groundTile/gt077.png";break;
					case 78: tilename="../../../../assets/groundTile/gt078.png";break;
					case 79: tilename="../../../../assets/groundTile/gt079.png";break;
					case 80: tilename="../../../../assets/groundTile/gt080.png";break;
					case 81: tilename="../../../../assets/groundTile/gt081.png";break;
					case 82: tilename="../../../../assets/groundTile/gt082.png";break;
					case 83: tilename="../../../../assets/groundTile/gt083.png";break;
					case 84: tilename="../../../../assets/groundTile/gt084.png";break;
					case 85: tilename="../../../../assets/groundTile/gt085.png";break;
					case 86: tilename="../../../../assets/groundTile/gt086.png";break;
					case 87: tilename="../../../../assets/groundTile/gt087.png";break;
					case 88: tilename="../../../../assets/groundTile/gt088.png";break;
					case 89: tilename="../../../../assets/groundTile/gt089.png";break;
					case 90: tilename="../../../../assets/groundTile/gt090.png";break;
					case 91: tilename="../../../../assets/groundTile/gt091.png";break;
					case 92: tilename="../../../../assets/groundTile/gt092.png";break;
					case 93: tilename="../../../../assets/groundTile/gt093.png";break;
					case 94: tilename="../../../../assets/groundTile/gt094.png";break;
					case 95: tilename="../../../../assets/groundTile/gt095.png";break;
					case 96: tilename="../../../../assets/groundTile/gt096.png";break;
					case 97: tilename="../../../../assets/groundTile/gt097.png";break;
					case 98: tilename="../../../../assets/groundTile/gt098.png";break;
					case 99: tilename="../../../../assets/groundTile/gt099.png";break;
					case 100: tilename="../../../../assets/groundTile/gt100.png";break;
					case 101: tilename="../../../../assets/groundTile/gt101.png";break;
					case 102: tilename="../../../../assets/groundTile/gt102.png";break;
					case 103: tilename="../../../../assets/groundTile/gt103.png";break;
					case 104: tilename="../../../../assets/groundTile/gt104.png";break;
					case 105: tilename="../../../../assets/groundTile/gt105.png";break;
					case 106: tilename="../../../../assets/groundTile/gt106.png";break;
					case 107: tilename="../../../../assets/groundTile/gt107.png";break;
					case 108: tilename="../../../../assets/groundTile/gt108.png";break;
					case 109: tilename="../../../../assets/groundTile/gt109.png";break;
					case 110: tilename="../../../../assets/groundTile/gt110.png";break;
					case 111: tilename="../../../../assets/groundTile/gt111.png";break;
					case 112: tilename="../../../../assets/groundTile/gt112.png";break;
					case 113: tilename="../../../../assets/groundTile/gt113.png";break;
					case 114: tilename="../../../../assets/groundTile/gt114.png";break;
					case 115: tilename="../../../../assets/groundTile/gt115.png";break;
					case 116: tilename="../../../../assets/groundTile/gt116.png";break;
					case 117: tilename="../../../../assets/groundTile/gt117.png";break;
					case 118: tilename="../../../../assets/groundTile/gt118.png";break;
					case 119: tilename="../../../../assets/groundTile/gt119.png";break;
					case 120: tilename="../../../../assets/groundTile/gt120.png";break;
					case 121: tilename="../../../../assets/groundTile/gt121.png";break;
					case 122: tilename="../../../../assets/groundTile/gt122.png";break;
					case 123: tilename="../../../../assets/groundTile/gt123.png";break;
					case 124: tilename="../../../../assets/groundTile/gt124.png";break;
					case 125: tilename="../../../../assets/groundTile/gt125.png";break;
					case 126: tilename="../../../../assets/groundTile/gt126.png";break;
					default: tilename="../../../../assets/groundTile/gt000.png";
#endif
				}
			
				tilenameList.push_back(tilename);
				iter->second=realpos++;
			}
			
			
			for(int y=0;y<dimension.y;++y)
				for(int x=0;x<dimension.x;++x)
					
				{
					mapTile[x+dimension.x*y]=(int) existTiles[tempMapTile[x+dimension.x*y]];
				}
			
			delete [] tempMapTile;
		
			int sqr=0;
			backgroundTileAtlas=TextureAtlasManager::getSingleton().addNew(tilenameList,40,40,sqr);
		
			backgroundSprites=new Sprite*[tileHSize*tileVSize];
		
			
		
			int h=0;
			int v=0;
		
			for(int i=0;i<(int)tilenameList.size();++i)
			{
				backgroundTiles.push_back( Texture(backgroundTileAtlas,h*40,v*40,40,40));
			
				h++;
			
				if(h>=sqr)
				{
					v++;
					h=0;
				}
			}
		
			for(int x=0;x<tileHSize;++x)
				for(int y=0;y<tileVSize;++y)
				{
					Sprite *tempSprite=new Sprite(x*TileSize,y*TileSize,TileSize,TileSize,0);
					backgroundSprites[x+tileHSize*y]=tempSprite;
				
					for(int i=0;i<(int)backgroundTiles.size();++i)
						tempSprite->addTexture(backgroundTiles[i].clone());
				}

		
			pan(halfScreenWidth,halfScreenHeight);
		}
    
		void GameMap::draw()
		{
			for(int x=0;x<tileHSize;++x)
				for(int y=0;y<tileVSize;++y)
				{
					backgroundSprites[x+y*tileHSize]->draw();	
				}
			
			Enemy::clearEnemyOrder();
			
			for (int i=0; i<(int)enemyPool.size(); ++i) 
			{
				Enemy::registerEnemyOrder(enemyPool[i]->getPathY(),i);
			}
			
			for (int y=0; y<dimension.y; ++y) 
			{
				if (obstacleLists[y].size()>0) 
				{
					for (std::vector<Sprite*>::iterator iter=obstacleLists[y].begin(); iter!=obstacleLists[y].end(); ++iter) 
					{
						(*iter)->draw();
					}
				}
				
				for(int x=0;x<dimension.x;++x)
				{
					if(towerMatrix[x+dimension.x*y]!=NULL)
					{
						towerMatrix[x+dimension.x*y]->draw();
					}
				}
				
				std::vector<int> & enemyofthislevel=Enemy::getEnemyOrderByY(y);
				
				for (std::vector<int>::iterator iter=enemyofthislevel.begin(); iter!=enemyofthislevel.end(); ++iter) 
				{
					enemyPool[*iter]->draw();
				}
			}
		

			
		
		}
		
		void GameMap::zoom(int newtilesize)
		{
			TileSize=newtilesize;
			
			
			//zoom background tile size
			for (int x=0; x<tileHSize; ++x) {
				for (int y=0; y<tileVSize; ++y) {
					delete backgroundSprites[x+y*tileHSize];
				}
			}
			
			delete [] backgroundSprites;
			
			
			tileHSize=screenWidth/TileSize+2;
			
			if(screenWidth%TileSize!=0)
				tileHSize++;
			
			tileVSize=screenHeight/TileSize+2;
			
			if(screenHeight%TileSize!=0)
				tileVSize++;
			
			backgroundSprites=new Sprite*[tileHSize*tileVSize];
			
					
			for(int x=0;x<tileHSize;++x)
				for(int y=0;y<tileVSize;++y)
				{
					Sprite *tempSprite=new Sprite(x*TileSize,y*TileSize,TileSize,TileSize,0);
					backgroundSprites[x+tileHSize*y]=tempSprite;
					
					for(int i=0;i<(int)backgroundTiles.size();++i)
						tempSprite->addTexture(backgroundTiles[i].clone());
				}
			
			
			
			
			
			//change background tile number
			
			for (int y=0; y<dimension.y; ++y) {
				for (std::vector<Sprite*>::iterator iter=obstacleLists[y].begin(); iter!=obstacleLists[y].end(); ++iter) {
					(*iter)->setSize(TileSize,TileSize);
				}
			}
			
			
			
			//zoom obstacle size
			//zoom viecle size
			
			for (std::vector<Enemy*>::iterator iter=enemyPool.begin(); iter!=enemyPool.end(); ++iter) {
				//wrong
				if ((*iter)->getEnemyType()==Enemy::Ground) {
					
					(*iter)->setSize(TileSize,TileSize);
				}
				else 
				{
					(*iter)->setSize(TileSize,TileSize*2);
				}

			}
			
			//zoom tower size
			
			for (std::vector<Tower*>::iterator iter=towerPool.begin(); iter!=towerPool.end(); ++iter) {
				(*iter)->setSize(TileSize,TowerHeight);
			}
			
			
			int currentx=mapCenterPosition.x;
			int currenty=mapCenterPosition.y;
			
			mapCenterPosition.x=0;
			mapCenterPosition.y=0;
			
			pan(currentx, currenty);
		}
    
		void GameMap::pan(int offsetX,int offsetY)
		{
			//printf("1 map center x:%d\n",mapCenterPosition.x);
			mapCenterPosition.x+=offsetX;
    	
			mapCenterPosition.y+=offsetY;
    	
			if(dimension.x<12 || dimension.y<10)
			{
				mapCenterPosition.x=halfScreenWidth;
				mapCenterPosition.y=halfScreenHeight;
			}
			else
			{
				if(mapCenterPosition.x<halfScreenWidth-TileSize*2+1)
					mapCenterPosition.x=halfScreenWidth-TileSize*2+1;
				else if(mapCenterPosition.x>dimension.x*TileSize-halfScreenWidth+TileSize*2-1)
					mapCenterPosition.x=dimension.x*TileSize-halfScreenWidth+TileSize*2-1;
    		
				if(mapCenterPosition.y<halfScreenHeight-TileSize*2+1)
					mapCenterPosition.y=halfScreenHeight-TileSize*2+1;
				else if(mapCenterPosition.y>dimension.y*TileSize-halfScreenHeight+TileSize*2-1)
					mapCenterPosition.y=dimension.y*TileSize-halfScreenHeight+TileSize*2-1;
			}
    	
			int left=mapCenterPosition.x-halfScreenWidth;
			int top=mapCenterPosition.y-halfScreenHeight;
			int right=mapCenterPosition.x+halfScreenWidth;
			int bottom=mapCenterPosition.y+halfScreenHeight;
    	

			
			int xmin=0;
			int xmax=right/TileSize+1;
			int ymin=0;
			int ymax=bottom/TileSize+1;
			
			
			
    		
			if (left<0) 
			{
				xmin=(left)/TileSize-1;
				spriteXOffset=(left+2*TileSize)%TileSize;
			}
			else 
			{
				spriteXOffset=left%TileSize;
				xmin=left/TileSize;
			}

			if(top<0)
			{
				ymin=(top)/TileSize-1;
				spriteYOffset=(top+2*TileSize)%TileSize;
			}
			else 
			{
				spriteYOffset=top%TileSize;
				ymin=top/TileSize;
			}

			
			//printf("xmin %d\n ymin %d\n",xmin,ymin);
			
			if(!(oldxmin==xmin && oldymin==ymin))
			{
				for(int x=xmin;x<=xmax;++x)
				{
					for(int y=ymin;y<=ymax;++y)
					{
						if(x>=0 && x<dimension.x && y>=0 && y<dimension.y)
						{
							backgroundSprites[x-xmin+(y-ymin)*tileHSize]->setAnimation(mapTile[x+y*dimension.x]);
						}
						//backgroundSprites[x-xmin][y-ymin].setTileIndex(2);
						else
						{
							backgroundSprites[x-xmin+tileHSize*(y-ymin)]->setAnimation(0);
						}//	
					}	
				}
			}
    	
			//printf("x offset:%d,y offset: %d\n",spriteXOffset,spriteYOffset);
		
			if(oldspriteoffsetx!=spriteXOffset || oldspriteoffsety!=spriteYOffset)
			{
				for(int x=0;x<tileHSize;++x)
					for(int y=0;y<tileVSize;++y)
					{
						backgroundSprites[x+tileHSize*y]->setOffsetXY(-spriteXOffset, -spriteYOffset);	
					}
				
			
			}
    	
			oldspriteoffsetx=spriteXOffset;
			oldspriteoffsety=spriteYOffset;
    	
			oldxmin=xmin;
			oldymin=ymin;
			PointI p=getMapOffset();
    	
			for(std::vector<Tower*>::iterator iter=towerPool.begin();iter!=towerPool.end();++iter)
			{
				(*iter)->setXY((*iter)->accuratePosition.x-p.x, (*iter)->accuratePosition.y-p.y);
			}
			
			
			for (int y=0; y<dimension.y; ++y) 
			{
				if (obstacleLists[y].size()>0) 
				{
					for (std::vector<Sprite*>::iterator iter=obstacleLists[y].begin(); iter!=obstacleLists[y].end(); ++iter) 
					{
						(*iter)->setOffsetXY(-p.x, -p.y);	
					}
				}
			}
		}
		
			
		void GameMap::airWalkable(PointI currentPosition,std::vector<int> & result)
		{
			//std::vector<WalkableDirection> result;
		
			if (currentPosition.x < 0 || currentPosition.y<0 || currentPosition.x>dimension.x-1 || currentPosition.y>dimension.y-1)
			{
				//outside the scope
				return ;
			}
			else 
			{
				if( (currentPosition.x>=0 && currentPosition.x<dimension.x && currentPosition.y-1>=0 && currentPosition.y-1<dimension.y) )
				{
					result.push_back(North);
				}
			
				if ((currentPosition.x >= 0 && currentPosition.x < dimension.x && currentPosition.y + 1 >= 0 && currentPosition.y + 1 < dimension.y) )
				{
					result.push_back(South);
				}
			
				if ((currentPosition.x - 1 >= 0 && currentPosition.x - 1 < dimension.x && currentPosition.y >= 0 && currentPosition.y < dimension.y) )
				{
					result.push_back(West);
				}
			
				if ((currentPosition.x + 1 >= 0 && currentPosition.x + 1 < dimension.x && currentPosition.y >= 0 && currentPosition.y < dimension.y) )
				{
					result.push_back(East);
				}
			
				return ;
			}
		}
	
		void GameMap::walkable(PointI currentPosition,std::vector<int> & result) 
		{
			//	std::vector<WalkableDirection> result;
		
			if (currentPosition.x < 0 || currentPosition.y<0 || currentPosition.x>dimension.x-1 || currentPosition.y>dimension.y-1)
			{
				//outside the scope
				return ;
			}
			else 
			{
			
				if (collisionTile[currentPosition.x+dimension.x*currentPosition.y] == Block || towerMatrix[currentPosition.x+dimension.x*currentPosition.y]!=NULL)
				{
					return ;
				}
				else 
				{
					if( (currentPosition.x>=0 && currentPosition.x<dimension.x && currentPosition.y-1>=0 && currentPosition.y-1<dimension.y) && !(collisionTile[currentPosition.x+(currentPosition.y-1)*dimension.x]==Block) && towerMatrix[currentPosition.x+(currentPosition.y-1)*dimension.x]==NULL)
					{
						result.push_back(North);
					}
				
					if ((currentPosition.x >= 0 && currentPosition.x < dimension.x && currentPosition.y + 1 >= 0 && currentPosition.y + 1 < dimension.y) && !(collisionTile[currentPosition.x+( currentPosition.y + 1)*dimension.x] == Block) && towerMatrix[currentPosition.x+(currentPosition.y+1)*dimension.x]==NULL)
					{
						result.push_back(South);
					}
				
					if ((currentPosition.x - 1 >= 0 && currentPosition.x - 1 < dimension.x && currentPosition.y >= 0 && currentPosition.y < dimension.y) && !(collisionTile[(currentPosition.x - 1)+ currentPosition.y*dimension.x] == Block) && towerMatrix[currentPosition.x-1+currentPosition.y*dimension.x]==NULL)
					{
						result.push_back(West);
					}
				
					if ((currentPosition.x + 1 >= 0 && currentPosition.x + 1 < dimension.x && currentPosition.y >= 0 && currentPosition.y < dimension.y) && !(collisionTile[(currentPosition.x + 1)+dimension.x* currentPosition.y] == Block)&& towerMatrix[currentPosition.x+1+currentPosition.y*dimension.x]==NULL)
					{
						result.push_back(East);
					}
					return ;
				}
			}
		}
		
		void GameMap::removeDeadEnemy()
		{
			
			std::vector<Enemy*> tempEnemyPool;
			
			tempEnemyPool.reserve(enemyPool.size()*0.5f);
			
			for (std::vector<Enemy*>::iterator iter=enemyPool.begin(); iter!=enemyPool.end(); ++iter) 
			{
				
				if((*iter)->isDead)
				{
					delete (*iter);
					(*iter)=NULL;
				}
				else 
				{
					tempEnemyPool.push_back(*iter);
				}
				
			}
			
			enemyPool.clear();
			
			enemyPool.resize(tempEnemyPool.size());
			
			std::copy(tempEnemyPool.begin(),tempEnemyPool.end(),enemyPool.begin());
			
		}
		
		
		void GameMap::sellTower(int _x,int _y)
		{
			Tower *tower=towerMatrix[_x+_y*dimension.x];
			
			if (tower) 
			{
				towerMatrix[_x+_y*dimension.x]=NULL;
				
				PointI towerPos(_x,_y);
				
				
				float r=tower->getRange();
				int range=(r-(float)(TileSize*0.5f))/(float)(TileSize)+1.0f;
				
				int xmin=_x-range>=0?_x-range:0;
				int xmax=_x+range<dimension.x?_x+range:dimension.x-1;
				
				int ymin=_y-range>=0?_y-range:0;
				int ymax=_y+range<dimension.y?_y+range:dimension.y-1;
				
				for(int	ax=xmin;ax<=xmax;++ax)
					for(int ay=ymin;ay<=ymax;++ay)
					{
						std::vector<PointI> &sl=shootingCache[ax+dimension.x*ay];
						
						for (int i=0; i<(int)sl.size(); ++i) 
						{
							if (sl[i]==towerPos) 
							{
								sl[i]=sl[0];
								break;
							}
						}
						
						sl.erase(sl.begin());
						
					}
				
				
				int money=tower->getSellMoney(tower->getTowerType());
				
				CurrentLevelStatistics::getSingleton().addMoneyEarned(money);
				
				SmallAnimationManager::getSingleton().addCoin(_x*TileSize+TileSize*0.5f,_y*TileSize+TileSize*0.5f,money);
				
				
				for (int i=0; i<(int)towerPool.size(); ++i) 
				{
					if (towerPool[i]==tower) 
					{
						towerPool[i]=towerPool[0];
					}
				}
				towerPool.erase(towerPool.begin());
				delete tower;
				MoneyBar::getSingleton().addMoney(money);
			}
		}
	}
}