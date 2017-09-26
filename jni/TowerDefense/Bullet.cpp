/*
 *  Bullet.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/9/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "Bullet.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
	
		void Bullet::setPositionOffsetRotation(int bulletPosition,PointF & accuratePosition,PointI & offset,float angle,PointI & bulletOffset)
		{
			setOffsetXY(-width*0.5, bulletPosition+height);
			setXY(accuratePosition.x-offset.x+bulletOffset.x,accuratePosition.y-offset.y+bulletOffset.y);
			setRotation((float)(360-angle/PI*180));
			animate();
		}
	}
}