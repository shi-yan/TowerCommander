/*
 *  InGameMenu.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "InGameMenu.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		void InGameMenu::beginScrollingDown(int _offset)
		{
			scrollOffset=_offset;
			isScrollingDown=true;
			lastTime=GameTimeManager::getSingleton().getCurrentTime();
		}
		
		void InGameMenu::scrollDown()
		{
			if (isScrollingDown) 
			{
				double nowTime=GameTimeManager::getSingleton().getCurrentTime();
				
				while ((nowTime-lastTime)>=0.02) 
				{
					lastTime+=0.02;
					
					scrollOffset-=40;
					
					if (scrollOffset<0) 
					{
						scrollOffset=0;
						break;
					}
				}
				
				if (scrollOffset<=0) 
				{
					isScrollingDown=false;
				}
				
			}
		}
	}
}