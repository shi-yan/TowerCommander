/*
 *  SlowTower.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/11/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "SlowTower.h"


namespace AnimalCrackers
{
	namespace TowerDefense
	{
		void SlowTower::shotAtEnemy(int id,Enemy *e)
		{
			float offsetx=e->fakePosition.x-(position.x*TowerWidth+(TowerWidth*0.5f));
			float offsety=e->fakePosition.y-(position.y*TowerWidth+(TowerWidth*0.5f));
				
			float distance=offsetx*offsetx+
			offsety*offsety;
				
			if(distance<range)
			{
				shotAtEnemyID=id;
					
				towerTextures->animate();
					
				e->slowDown(damage);
				oldshotAtEnemyID=shotAtEnemyID;
					
			}
		}
	}
}