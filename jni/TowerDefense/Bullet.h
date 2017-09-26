/*
 *  Bullet.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/9/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __Bullet__
#define __Bullet__

#include "GlobalConfig.h"
#include "Sprite.h"
#include "Point.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class Bullet : public Sprite 
		{
		private:
			float speed;
			
		public:
			Bullet():Sprite(0,0,0),speed(2.5f)
			{
				setVisible(false);
			};
			
			virtual ~Bullet(){};
			
			float getSpeed()
			{
				return speed;
			};
			
			void setSpeed(float _s)
			{
				speed=_s;
			};
			
			void setPositionOffsetRotation(int bulletPosition,PointF &,PointI & offset,float angle,PointI & bulletOffset);
		};
	}
}

#endif