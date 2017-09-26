/*
 *  Screen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Screen__
#define __Screen__

#include "GlobalConfig.h"
#include "FastDelegate.h"
#include <vector>
namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class Screen
		{
		public:
			
			typedef fastdelegate::FastDelegate0<> onBackDelegate;
		protected:
			int width;
			int height;
			std::vector<onBackDelegate> backDelegateList;
			
		public:
			Screen();
			virtual ~Screen();
			
			virtual void init(int _width,int _height);
			virtual void reSize(int _width,int _height);
			
			virtual void draw();
			
			virtual void handlePressEvent(int _x,int _y);
			virtual void handleReleaseEvent(int _x,int _y);
			virtual void handleMoveEvent(int _x,int _y);
			virtual void handleBackEvent();
			
			virtual void renew(){};
			void addBackEventHandler(onBackDelegate d);
			void onBack();
		};
		
	}
}

#endif