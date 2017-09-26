/*
 *  MainMenuButton.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __MainMenuButton__
#define __MainMenuButton__

#include "GlobalConfig.h"
#include "HotSpot.h"
#include "GameTimeManager.h"
#include "QuadHelper.h"
namespace AnimalCrackers 
{
	namespace TowerDefense
	{
		class MainMenuButton : public HotSpot
		{
		private:
			float animationInterval;
			float animationBeginTime;
			bool hasLoadingAnimationFinished;
			double loadingAnimationOldTime;
			double elapsed;
			float sizeFactor;
			float minSize;
			float maxSize;
			
			int status;
			
		public:
			MainMenuButton(int _width,int _height)
			:HotSpot(_width,_height),
			animationInterval(0.0f),
			animationBeginTime(0.0f),
			hasLoadingAnimationFinished(true),
			loadingAnimationOldTime(0.0),
			elapsed(0.0),
			sizeFactor(0.5f),
			minSize(0.5f),
			maxSize(1.0f),
			status(0)
			{
				HotSpot::onReleaseDelegate rd;
				rd.bind(this,&MainMenuButton::onRelease);
				addOnReleaseHandler(rd);
				
				HotSpot::onPressDelegate pd;
				pd.bind(this,&MainMenuButton::onPress);
				addOnPressHandler(pd);
			};
			
			~MainMenuButton()
			{};
			

			
			void beginLoadingAnimation(float _begin,float _interval);
			void draw();
			void updateLoadingAnimation();
			
			void onPress();
			void onRelease();
		};
	}
}

#endif