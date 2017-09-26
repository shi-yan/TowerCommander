/*
 *  Wave.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Wave__
#define __Wave__

#include "GlobalConfig.h"
#include "Enemy.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class Wave  
		{
			
		public:
			double waitTime;
			
		private:
			std::vector<Enemy*> enemyList;
			
		public:
			void setWaitTime(double t)
			{
				waitTime=t;
			};
			
			int getCount()
			{
				return enemyList.size();
			}
			
			void insertAnEnemy(Enemy *e);
			
			Enemy* nextEnemy();
			
			~Wave();
			
			
		};
	}
}

#endif