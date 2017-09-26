/*
 *  Enemy.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "Enemy.h"
#include "GameMap.h"
#include <queue>
#include "PathFindNode.h"
#include "QuadHelper.h"
#include "MoneyBar.h"
#include "CurrentLevelStatistics.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		TextureAnimation *Enemy::bloodTexture=NULL;
		
		std::vector<int> *Enemy::enemyOrder=NULL;
		
		int Enemy::ydimension=0;
		
		void Enemy::setKilled()
		{
			isDead=true;
			
			PointI mapOffset=GameMap::getSingleton().getMapOffset();
			
			SmallAnimationManager::getSingleton().addCoin(x+mapOffset.x,y+mapOffset.y,money);
			
			SmallAnimationManager::getSingleton().addExplosion(x+mapOffset.x+20,y+mapOffset.y+20,explosionType);
			
			CurrentLevelStatistics::getSingleton().addMoneyEarned(money);
			
			CurrentLevelStatistics::getSingleton().addEnemiesKilled(1);
			
			MoneyBar::getSingleton().addMoney(money);
			
		}
		
		void Enemy::draw()
		{
			Sprite::draw();
			
			Enemy::bloodTexture->setAnimationStep(currentBloodAnimationID);
			Enemy::bloodTexture->apply();
			
			QuadHelper::getSingleton().drawQuad(x+offsetX+2,y+offsetY-10,35,4,Enemy::bloodTexture->getCoordinates());
		}
		
		void Enemy::setBloodTexture()
		{
			
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("ui.png");
#else
			
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/ui.png");
#endif
			Enemy::bloodTexture=new TextureAnimation(atlas,0,177,35,32,35,4);
			int k[8]={0,1,2,3,4,5,6,7};
			Enemy::bloodTexture->addAnimation(k, 8);
			bloodTexture->setAnimation(0);
		}
		
		bool Enemy::findTempPathWithTempBlock(std::deque<PointI> & tmppath,PointI tempBlockPoint)
		{
			std::vector<PathFindNode*> nodepool;
			nodepool.reserve(1000);
			
			bool *hasBeenVisited=new bool[GameMap::getSingleton().dimension.x*GameMap::getSingleton().dimension.y];
			
			for(int x=0;x<GameMap::getSingleton().dimension.x;++x)
				for(int y=0;y<GameMap::getSingleton().dimension.y;++y)
					hasBeenVisited[x+y*GameMap::getSingleton().dimension.x]=false;
			
			hasBeenVisited[tempBlockPoint.x+tempBlockPoint.y*GameMap::getSingleton().dimension.x]=true;
			
			std::queue<PathFindNode*> breadthFirstQueue;
			
			PathFindNode *initialnode=new PathFindNode(position);
			
			breadthFirstQueue.push( initialnode);
			nodepool.push_back(initialnode);
			
			
			while ( breadthFirstQueue.size() > 0 && !GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos))
			{
				PathFindNode *tempnode=breadthFirstQueue.front();
				breadthFirstQueue.pop();
				PointI tempPosition=tempnode->pos;
				std::vector<int> walkableTiles;
				walkableTiles.reserve(4);
				GameMap::getSingleton().walkable(tempPosition,walkableTiles);
				
				for (std::vector<int>::iterator walkabledir=walkableTiles.begin(); walkabledir!= walkableTiles.end();++walkabledir)
				{
					switch (*walkabledir)
					{
						case North:
						{
							if(hasBeenVisited[tempPosition.x+GameMap::getSingleton().dimension.x*(tempPosition.y - 1)]==false )
							{
								PathFindNode *newnode=new PathFindNode ( PointI(tempPosition.x, tempPosition.y - 1));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+GameMap::getSingleton().dimension.x*(tempPosition.y - 1)]=true;
							}
						}
							break;
						case South:
						{
							if(hasBeenVisited[tempPosition.x+GameMap::getSingleton().dimension.x*(tempPosition.y + 1)]==false )
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x, tempPosition.y + 1));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+GameMap::getSingleton().dimension.x*(tempPosition.y + 1)]=true;
							}
						}
							break;
						case West:
						{
							if(hasBeenVisited[tempPosition.x-1+GameMap::getSingleton().dimension.x*tempPosition.y]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x - 1, tempPosition.y));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								
								hasBeenVisited[tempPosition.x-1+GameMap::getSingleton().dimension.x*tempPosition.y]=true;
							}
						}
							break;
						case East:
						{
							if(hasBeenVisited[tempPosition.x+1+GameMap::getSingleton().dimension.x*tempPosition.y ]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x + 1, tempPosition.y));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								
								hasBeenVisited[tempPosition.x+1+GameMap::getSingleton().dimension.x*tempPosition.y ]=true;
							}
						}
							break;
					}
					
				}
				
			}
			
			delete [] hasBeenVisited;
			
			
			
			if (breadthFirstQueue.size() == 0) 
			{
				
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) {
					delete (*iter);
				}
				
				nodepool.clear();
				
				return false;
			}
			else if (GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos)) 
			{
				tmppath.clear();
				
				PathFindNode* tempnode=breadthFirstQueue.front();
				
				while(tempnode->pre!=NULL)
				{
					tmppath.push_front(tempnode->pos);
					tempnode = tempnode->pre;
				}
				
				tmppath.push_front( tempnode->pos);
				
		
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) {
					delete (*iter);
				}
				
				nodepool.clear();
				
				return true;
				
			}
			
			return false;
			
			
		}
		
		void Enemy::lastingDamage(int d)
		{
			accumulatedLastingDamage+=d;
		}
		
		void Enemy::immediateDamage(float d)
		{
			if (!isDead) 
			{
				
			
				health-=d;
			
				if (health<0.0f) 
				{
					health=0.0f;
				
					setKilled();
				}
			
				currentBloodAnimationID	=7-(int)(7.0f*(float)health/(float)fullHealth);
			}
		}
		
		void Enemy::slowDown(float rate)
		{
			slowDownRate*=rate;
		}
		
		void Enemy::applyLastingDamage()
		{
			if(!isDead)
			if(accumulatedLastingDamage)
			{
				while(++applyLastingDamageCounter>10)
				{
					applyLastingDamageCounter=0;
				
					health-=1;
					accumulatedLastingDamage--;
					
					if (health<0) 
					{
						health=0;
						setKilled();
						break;
					}
					
					
				}
			
				currentBloodAnimationID	=7-(int)(7.0f*(float)health/(float)fullHealth);
				applyLastingDamageCounter++;
			}
		}
		
		void Enemy::beginMove()
		{
			lastMoveTime=GameTimeManager::getSingleton().getCurrentTime()-0.07;
		
		}
		
		bool Enemy::findTempPath(std::deque<PointI> & tmppath)
		{
			std::vector<PathFindNode *> nodepool;
			nodepool.reserve(1000);
			
			bool* hasBeenVisited=new bool[GameMap::getSingleton().dimension.x*GameMap::getSingleton().dimension.y];
			for(int x=0;x<GameMap::getSingleton().dimension.x;++x)
				for(int y=0;y<GameMap::getSingleton().dimension.y;++y)
					hasBeenVisited[x+GameMap::getSingleton().dimension.x*y]=false;
			
			std::queue<PathFindNode*> breadthFirstQueue;
			PathFindNode *initialNode=new PathFindNode(position);
			breadthFirstQueue.push(initialNode);
			nodepool.push_back(initialNode);
			
			
			while ( breadthFirstQueue.size() > 0 && !GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos))
			{
				PathFindNode *tempnode=breadthFirstQueue.front();
				breadthFirstQueue.pop();
				PointI tempPosition=tempnode->pos;
				std::vector<int> walkableTiles; 
				walkableTiles.reserve(4);
				GameMap::getSingleton().walkable(tempPosition,walkableTiles);
				
				for (std::vector<int>::iterator walkabledir=walkableTiles.begin();walkabledir!=walkableTiles.end();++walkabledir)
				{
					switch (*walkabledir)
					{
							
							
						case GameMap::North:
						{
							if(hasBeenVisited[tempPosition.x + GameMap::getSingleton().dimension.x*(tempPosition.y - 1)]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x, tempPosition.y - 1));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+ GameMap::getSingleton().dimension.x* (tempPosition.y - 1)]=true;
							}
						}
							break;
						case GameMap::South:
						{
							if(hasBeenVisited[tempPosition.x + GameMap::getSingleton().dimension.x*(tempPosition.y + 1)]==false)
							{
								PathFindNode *newnode = new PathFindNode(PointI(tempPosition.x, tempPosition.y + 1));
									nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+ GameMap::getSingleton().dimension.x* (tempPosition.y + 1)]=true;
							}
						}
							break;
						case GameMap::West:
						{
							if(hasBeenVisited[tempPosition.x-1 +GameMap::getSingleton().dimension.x* tempPosition.y]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x - 1, tempPosition.y));
									nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								
								hasBeenVisited[tempPosition.x-1+ GameMap::getSingleton().dimension.x* tempPosition.y]=true;
							}
						}
							break;
						case GameMap::East:
						{
							if(hasBeenVisited[tempPosition.x+1 + GameMap::getSingleton().dimension.x*tempPosition.y ]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x + 1, tempPosition.y));
									nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								
								hasBeenVisited[tempPosition.x+1+GameMap::getSingleton().dimension.x*tempPosition.y ]=true;
							}
						}
							break;
					}
					
				}
				
			}
			
			delete [] hasBeenVisited;
			
			
			
			if (breadthFirstQueue.size() == 0) 
			{
				//no path;
				
				//error blocked way
				
				//breadthFirstQueue.clear();
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) {
					delete (*iter);
				}
				
				nodepool.clear();
				return false;
			}
			else if (GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos)) 
			{
				tmppath.clear();
				
				PathFindNode *tempnode=breadthFirstQueue.front();
				
				while(tempnode->pre!=NULL)
				{
					tmppath.push_front(tempnode->pos);
					tempnode = tempnode->pre;
				}
				
				tmppath.push_front( tempnode->pos);
				
				//breadthFirstQueue.clear();
				
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) {
					delete (*iter);
				}
				
				nodepool.clear();
				
				return true;
				
			}
			
			return false;
		}
		
		void Enemy::renewDisplayPosition()
		{
			PointI p=GameMap::getSingleton().getMapOffset();
			setXY(fakePosition.x-TileSize/2-p.x, fakePosition.y-TileSize/2-p.y);
		}
		
		void Enemy::findPath()
		{
		//	LOGI("ground find path");
			std::deque<PointI> tmppath;	
			std::vector<PointI> testP;
			//path.clear();
			
			if(findTempPath(tmppath))
			{
				//path=tmppath;
				for (std::deque<PointI>::iterator iter=tmppath.begin(); iter!=tmppath.end(); ++iter) 
				{
					PointI p((*iter).x,(*iter).y);
					path.push_back(p);
				}
				
				pathStep=0;
			}
		}
		
		
		bool Enemy::move() 
		{
		
			
			if (pathStep==0 && moved==0.0f)
			{
				if (path[(pathStep + 1)].y < path[(pathStep)].y)
				{
					direction = North;
					setAnimation(North);
				}
				else if (path[(pathStep + 1)].y > path[(pathStep)].y){
					direction = South;
					setAnimation(South);    
				}
				else if (path[(pathStep + 1)].x > path[(pathStep)].x){
					direction = East;
					setAnimation(East);    
				}
				else if (path[(pathStep + 1)].x < path[(pathStep)].x){
					
					direction = West;
					setAnimation(West);    
				}
			}
			
			
			movestart.x = (float)path[(pathStep)].x*TileSize + TileSize*0.5f;
			movestart.y = (float)path[(pathStep)].y*TileSize + TileSize * 0.5f;
			
			if (pathStep >=(int) path.size() - 1)
			{
				return true;
			}
			else
			{
				moveend.x = (float)path[(pathStep + 1)].x*TileSize+TileSize*0.5f;
				moveend.y = (float)path[(pathStep + 1)].y*TileSize + TileSize * 0.5f;
			}
			double currentMoveTime=GameTimeManager::getSingleton().getCurrentTime();
			while (currentMoveTime-lastMoveTime>0.06) 
			{
				lastMoveTime+=0.06;
			moved += speed*slowDownRate;
			}
		
			
			if (moved < 1.0f)
			{
				fakePosition.x = ((float)movestart.x) *(1.0f- moved) + ( moved) *(float) moveend.x;
				fakePosition.y = ((float)movestart.y) * (1.0f-moved) + ( moved) * (float)moveend.y;
			}
			else 
			{
				//change direction
				
				do
				{
					moved -= 1.0f;
					
					pathStep++;
					
					if (pathStep > (int)path.size() - 1) 
					{
						moved = 0.0f;
						pathStep = 0;
					}
					
					position = path[(pathStep)];
					
					if (pathStep < path.size() - 1)
					{
						if (path[(pathStep + 1)].y < path[(pathStep)].y)
						{
							direction = North;
							setAnimation(North);
						}
						else if (path[(pathStep + 1)].y > path[(pathStep)].y){
							direction = South;
							setAnimation(South);    
						}
						else if (path[(pathStep + 1)].x > path[(pathStep)].x){
							direction = East;
							setAnimation(East);    
						}
						else if (path[(pathStep + 1)].x < path[(pathStep)].x){
							
							direction = West;
							setAnimation(West);    
						}
					}
					
					movestart.x = (float)path[(pathStep)].x*TileSize + TileSize * 0.5f;
					movestart.y = (float)path[(pathStep)].y*TileSize + TileSize * 0.5f;
					
					if (pathStep >= (int)path.size() - 1)
						moveend = movestart;
					else
					{
						moveend.x = (float)path[(pathStep + 1)].x*TileSize + TileSize * 0.5f;
						moveend.y = (float)path[(pathStep + 1)].y*TileSize + TileSize * 0.5f;
					}
					
					fakePosition.x = ((float)movestart.x) *(1.0f- moved) + ( moved) * (float)moveend.x;
					fakePosition.y = ((float)movestart.y) * (1.0f-moved) + ( moved) * (float)moveend.y;
					
					
					
				}
				while(moved>=1.0f);
			}
			
			//Enemy::registerEnemyOrder(path[pathStep].y,);
			
			renewDisplayPosition();
				
			
			return false;
		}
		
		
	}
}