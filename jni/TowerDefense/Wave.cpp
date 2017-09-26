/*
 *  Wave.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "Wave.h"

namespace AnimalCrackers
{
	namespace TowerDefense {
		void Wave::insertAnEnemy(Enemy *e)
		{
			enemyList.push_back(e);
			
			
		}
		
		Enemy* Wave::nextEnemy()
		{
			
			if(enemyList.size()>0)
			{
				Enemy *e=enemyList[0];
				
				enemyList.erase(enemyList.begin());
				
				return e;
			}
			else
			{
				return NULL;
			}
		}
		
		Wave::~Wave()
		{
			for (int i=0; i<(int)enemyList.size(); ++i) {
				delete enemyList[i];
			}
			
			enemyList.clear();
		};
		
	}
}