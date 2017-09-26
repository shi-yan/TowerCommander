/*
 *  InGameMenu.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __InGameMenu__
#define __InGameMenu__

#include "GlobalConfig.h"
#include "UIItem.h"
#include "GameTimeManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class InGameMenu : public UIItem 
		{
		protected:
			Texture *background;
			bool isVisiable;
			
			int scrollOffset;
			bool isScrollingDown;
			double lastTime;
			
		public:
			InGameMenu():UIItem(480,320),background(NULL),isVisiable(false),scrollOffset(400),isScrollingDown(false),lastTime(0.0)
			{};

			virtual void draw()
			{};
			
			void beginScrollingDown(int _offset);
			void scrollDown();
			virtual ~InGameMenu()
			{
				if(background)
					delete background;
			};
		};
	}
}

#endif