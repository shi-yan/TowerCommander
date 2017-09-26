/*
 *  HotSpot.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "HotSpot.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		bool HotSpot::handlePressEvent(int _x,int _y)
		{
			float halfWidth=width*0.5f;
			float halfHeight=height*0.5f;
			
			if (_x>x-halfWidth && _x<x+halfWidth && _y>y-halfHeight && _y<y+halfHeight) 
			{
				isPressed=true;
				for (std::vector<onPressDelegate>::iterator iter=pressDelegateList.begin(); iter!=pressDelegateList.end(); ++iter) 
				{
					(*iter)();
				}
				
				return true;
			}
			else 
			{
				return false;
			}
		};
		
		bool HotSpot::handleReleaseEvent(int _x,int _y)
		{
			float halfWidth=width*0.5f;
			float halfHeight=height*0.5f;
			
			if ((_x>x-halfWidth && _x<x+halfWidth && _y>y-halfHeight && _y<y+halfHeight)  || isPressed) 
			{
				isPressed=false;
				
				printf("event size:%d\n",releaseDelegateList.size());
				for (std::vector<onReleaseDelegate>::iterator iter=releaseDelegateList.begin(); iter!=releaseDelegateList.end(); ++iter) 
				{
					(*iter)();
				}
				
				return true;
			}
			else 
			{
				return false;
			}
		};	
	}
}