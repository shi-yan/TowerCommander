/*
 *  EnemyFactory.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __EnemyFactory__
#define __EnemyFactory__

#include "GlobalConfig.h"
#include <vector>
#include <queue>
#include "Wave.h"
#include "Point.h"
#include "Texture.h"
#include "Enemy.h"
#include "TextureAtlas.h"
#include "GameTimeManager.h"
#include "AirEnemy.h"
#include "TextureAtlasManager.h"
#include "NextWaveBar.h"
#include "WalkableEnemy.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class EnemyFactory  
		{	
		private:
			std::queue<Wave*> waveQueue;
			std::vector<PointI> startingPositions;

			bool isBeginEnemy;
			Wave *currentWave;
			double oldTime;
			double countDownOldTime;
			double countDownNewTime;
			
			EnemyFactory():isBeginEnemy(false),currentWave(NULL),oldTime(0),overallWaveCount(0)
			{
			};

			~EnemyFactory()
			{
				currentWave=NULL;
				while (waveQueue.size()>0) 
				{
					Wave *tp=waveQueue.front();
					delete tp;
					waveQueue.pop();
				}
			};
			
			Enemy * getEnemyByType(int type);
			Texture *getAEnemyTexture(int atlas,int _id);
			Texture *getAirEnemyTexture(int atlas,int _id);
			int overallWaveCount;
			
		public:		
			
			int howManyLeft()
			{
				return (waveQueue.front()->getCount()+waveQueue.back()->getCount())*0.6f*waveQueue.size();
			};
			
			static EnemyFactory & getSingleton()
			{
				static EnemyFactory obj;
				return obj;
			};
		 
			void beginWave()
			{
				if(waveQueue.size()>0)
				{
					countDownOldTime=GameTimeManager::getSingleton().getCurrentTime();
					isBeginEnemy=false;
				}
			};

			Enemy* querryForAnEnemy();
			void countDown();
			double queryForNextWaveTime();
			void initWavesFromFile(FILE *fp);
			void setStartingPositions(std::vector<PointI> & inputStartingPositions);
			void clearStartingPositions();
			
			bool isWaveOver()
			{
				return waveQueue.size()==0 && isBeginEnemy==false && currentWave==NULL;
			}
			
			bool clear()
			{
				isBeginEnemy=(false);
			
				oldTime=(0);
				while (waveQueue.size()>0) 
				{
					Wave *tp=waveQueue.front();
					delete tp;
					waveQueue.pop();
				}
				
				if (	currentWave) {
					delete currentWave;
					currentWave=NULL;
				}

				return true;
			}
		};
	}
}

#endif