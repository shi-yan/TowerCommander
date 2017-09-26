/*
 *  WalkableEnemy.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __WalkableEnemy__
#define __WalkableEnemy__

#include "GlobalConfig.h"
#include "Enemy.h"
#include "TextureAnimation.h"
#include "QuadHelper.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class WalkableEnemy : public Enemy 
		{
			
		private:
			
			TextureAnimation *walkAnimation;
			
		public:
			
			WalkableEnemy():Enemy(){};
			
			~WalkableEnemy()
			{
				delete walkAnimation;
			};
			
			 void setTextureIndices(TextureAnimation * walk)
			{
				walkAnimation=walk;
			}
			
		public:
			bool move();
			
			void draw();
			
			virtual void setAnimation(int _id)
			{
				walkAnimation->setAnimation(_id);
			};
		};
	}
}

#endif