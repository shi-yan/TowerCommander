/*
 *  AirEnemy.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __AirEnemy__
#define __AirEnemy__

#include "GlobalConfig.h"

#include "Enemy.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class AirEnemy : public Enemy 
		{
			
		public:
			AirEnemy():Enemy(){};
			
			void findPath();
			
			void renewDisplayPosition();
			
			enum Enemy::EnemyType getEnemyType()
			{
				return Enemy::Air;
			};
		};
	}
}

#endif