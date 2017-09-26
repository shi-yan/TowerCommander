/*
 *  HotSpot.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __HotSpot__
#define __HotSpot__

#include "GlobalConfig.h"
#include "UIItem.h"
#include "FastDelegate.h"
#include <vector>

namespace AnimalCrackers 
{
	namespace TowerDefense
	{
		class HotSpot:public UIItem
		{
			
		public:
			typedef fastdelegate::FastDelegate0<> onPressDelegate;
			typedef fastdelegate::FastDelegate0<> onReleaseDelegate;
			
		private:
			std::vector<onPressDelegate> pressDelegateList;
			std::vector<onReleaseDelegate> releaseDelegateList;
			
			bool isPressed;
				
		public:
			HotSpot(int _width,int _height):UIItem(_width, _height),isPressed(false)
			{
			
			};
			
			bool getIsPressed()
			{
				return isPressed;
			};

			virtual ~HotSpot()
			{
			};
			
			void draw()
			{
				UIItem::draw();
			};
			
			void pressed()
			{
			};
			
			void released()
			{
			};
			
			void addOnPressHandler(onPressDelegate d)
			{
				pressDelegateList.push_back(d);
			};
			
			void addOnReleaseHandler(onReleaseDelegate d)
			{
				releaseDelegateList.push_back(d);
			};
			
			bool handlePressEvent(int _x,int _y);
			
			bool handleReleaseEvent(int _x,int _y);
		};
	}
}

#endif