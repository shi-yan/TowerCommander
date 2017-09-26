/*
 *  SlowTower.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/11/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __SlowTower__
#define __SlowTower__

#include "GlobalConfig.h"
#include "Tower.h"
#include "SlowTower.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class SlowTower : public Tower 
		{
		public:
			SlowTower():Tower(){};
			~SlowTower(){};
			
			void shotAtEnemy(int id,Enemy *e);
			
		};
	}
}

#endif