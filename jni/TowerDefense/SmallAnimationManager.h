/*
 *  SmallAnimationManager.h
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __SmallAnimationManager__
#define __SmallAnimationManager__

#include "GlobalConfig.h"
#include "TextureAnimation.h"
#include <vector>
#include "FlameAnimation.h"
#include "CoinAnimation.h"
#include "NotificationAnimation.h"


namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class SmallAnimationManager 
		{
		private:
			SmallAnimationManager(){};
			~SmallAnimationManager();
			
			std::vector<FlameAnimation*> flameAnimationList;
			std::vector<CoinAnimation*> coinAnimationList;
			std::vector<NotificationAnimation*> notificationAnimationList;
			
		public:
			static SmallAnimationManager & getSingleton()
			{
				static SmallAnimationManager obj;
				return obj;
			};
			
			void init();
			void release();
			
			void addCoin(int _x,int _y,int mon);
			
			void addExplosion(int _x,int _y,int type);
			
			void addNotification(int type);
			
			void draw();
		};
	}
}

#endif