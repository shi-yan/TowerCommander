/*
 *  FlameTower.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/11/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __FlameTower__
#define __FlameTower__

#include "GlobalConfig.h"
#include "Enemy.h"
#include "Tower.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class FlameTower : public Tower 
		{
		public:
			FlameTower():Tower()
			{
				setTargetType(Tower::GroundOnly);
			};
			
			~FlameTower(){};
			
			void shotAtEnemy(int id,Enemy *e);
		};
		
	}
}

#endif