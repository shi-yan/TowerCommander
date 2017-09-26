/*
 *  GameMap.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __GameMap__
#define __GameMap__

#include "GlobalConfig.h"
#include <vector>
#include "TextureAtlasManager.h"
#include "Point.h"
#include "Sprite.h"
#include "Tower.h"
#include "Enemy.h"
#include <map>
#include <iostream>
namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class GameMap
		{
		public:
			enum WalkableDirection
			{
				North,
				South,
				West,
				East,
			};
			
			enum CollisionTileType
			{
				Start,
				End,
				Block,
				Path,
			};
			
		public:
			PointI dimension;
			
			int *mapTile;
			enum CollisionTileType *collisionTile;
			
			std::vector<PointI> & getStartPoints();
			
		private:
			
			int backgroundTexture;
			PointI mapCenterPosition;
			Sprite ** backgroundSprites;
			Tower ** towerMatrix;
			std::vector<PointI> *shootingCache;
			Enemy *pathFindEnemy;
			
			int backgroundTileAtlas;
			
			std::vector<Tower*> towerPool;
			std::vector<Enemy*> enemyPool;
			std::vector<Texture> tileTexture;
			std::vector<Sprite*> *obstacleLists;
			
			int screenWidth;
			int screenHeight;
			
			int halfScreenWidth;
			int halfScreenHeight;
			
			int tileHSize;
			int tileVSize;
			
			
		private:
			GameMap()
			:backgroundTexture(0),
			screenWidth(0),
			screenHeight(0),
			halfScreenWidth(0),
			halfScreenHeight(0),
			tileHSize(0),
			tileVSize(0),
			dimension(),
			mapTile(NULL),
			collisionTile(0),
			backgroundSprites(NULL),
			towerMatrix(NULL),
			spriteXOffset(0),
			spriteYOffset(0),
			oldxmin(-5),
			oldymin(-7),
			oldspriteoffsetx(-5),
			oldspriteoffsety(-7),
			shootingCache(NULL),pathFindEnemy(new Enemy())
			{};
			
			std::vector<Texture > backgroundTiles;
			
			~GameMap()
			{
				for (std::vector<Enemy*>::iterator iter=enemyPool.begin(); iter!=enemyPool.end(); ++iter) 
				{
					delete (*iter);
				}
				
				for (std::vector<Tower*>::iterator iter=towerPool.begin(); iter!=towerPool.end(); ++iter) 
				{
					delete (*iter);
				}
				
				for (int x=0; x<tileHSize; ++x) 
				{
					for (int y=0; y<tileVSize; ++y) 
					{
						delete backgroundSprites[x+y*tileHSize];
					}
				}
				
				delete [] backgroundSprites;
				delete [] towerMatrix;
				delete [] shootingCache;
				delete pathFindEnemy;
				
				delete [] mapTile;
				delete [] collisionTile;
				
				backgroundTiles.clear();
			};
			
				

	
		public:
			
			void zoom(int newtilesize);
			
			bool isMapEmpty()
			{
				return dimension.x==0 && dimension.y==0;
			}
			
			void clearMap()
			{
				
			
				
				for (std::vector<Enemy*>::iterator iter=enemyPool.begin(); iter!=enemyPool.end(); ++iter) 
				{
					delete (*iter);
				}
				
				enemyPool.clear();
				
				for (std::vector<Tower*>::iterator iter=towerPool.begin(); iter!=towerPool.end(); ++iter) 
				{
					delete (*iter);
				}
				
				towerPool.clear();
				
				for (int x=0; x<tileHSize; ++x) 
				{
					for (int y=0; y<tileVSize; ++y) 
					{
						delete backgroundSprites[x+y*tileHSize];
					}
				}
				
				delete [] backgroundSprites;
				backgroundSprites=NULL;
				delete [] towerMatrix;
				towerMatrix=NULL;
				delete [] shootingCache;
				shootingCache=NULL;
				
				delete [] mapTile;
				mapTile=NULL;
				
				delete [] collisionTile;
				collisionTile=NULL;
				
				backgroundTexture=(0);
				screenWidth=(0);
				screenHeight=(0);
				halfScreenWidth=(0);
				halfScreenHeight=(0);
				tileHSize=(0);
				tileVSize=(0);
				dimension.x=0;
				dimension.y=0;
				spriteXOffset=(0);
				spriteYOffset=(0);
				oldxmin=(-5);
				oldymin=(-7);
				oldspriteoffsetx=(-5);
				oldspriteoffsety=(-7);
				
				Enemy::releaseEnemyOrder();
				
				backgroundTiles.clear();
				
			};
			
			void insertAnEnemy(Enemy *e)
			{
				enemyPool.push_back(e);
			};
	
			std::vector<Enemy*> & getEnemyPool()
			{
				return enemyPool;
			};
	
			void removeDeadEnemy();
    
			static GameMap & getSingleton()
			{
				static GameMap obj;
				return obj;
			};
	
			void init(PointI _dimension,int _screenWidth,int _screenHeight);
	
			std::vector<PointI> startPoints;
			std::vector<PointI> endPoints;
	
			bool insertATower(Tower *tower, int x,int y);
    
		/*	Enemy * getEnemy(int id)
			{
				return enemyPool[id];
			};
    
			bool withinRange(Tower tower, Enemy enemy)
			{
				return true;
			}*/
    
			void shotAtEnemies();
			void loadFromFile(const char* filename,int _screenWidth,int _screenHeight);
			
			PointI getMapOffset()
			{
				//return PointI(0,0);
				return  PointI(	mapCenterPosition.x-halfScreenWidth,mapCenterPosition.y-halfScreenHeight);
			};
    
		private:
			int spriteXOffset;
			int spriteYOffset;
    
			int oldxmin;
			int oldymin;
    
			int oldspriteoffsetx;
			int oldspriteoffsety;
			
		public:
			void draw();
			void pan(int offsetX,int offsetY);		
			
			void sellTower(int _x,int _y);
			
			bool isEnd(PointI currentPosition) 
			{
				if ((currentPosition.x >= 0 && currentPosition.x < dimension.x && currentPosition.y >= 0 && currentPosition.y < dimension.y) && (collisionTile[currentPosition.x+dimension.x*currentPosition.y ] == End))
				{
					return true;
				}
				
				return false;
			}
			
			void airWalkable(PointI currentPosition,std::vector<int> & result);			
			void walkable(PointI currentPosition,std::vector<int> & result);
			
			void upgradeATowerAt(int _x,int _y,int _id);
			
			Tower* getTowerAt(int _x,int _y)
			{
				return towerMatrix[_x+_y*dimension.x];
			};
		};
	}
}

#endif