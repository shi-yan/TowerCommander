/*
 *  NotificationAnimation.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/12/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __NotificationAnimation__
#define __NotificationAnimation__

#include "GlobalConfig.h"
#include "SmallAnimation.h"
#include "TextureAnimation.h"
namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class NotificationAnimation : public SmallAnimation 
		{
		private:
			static TextureAnimation *notificationTextures[3];
			int animationType;
			int currentAnimationStep;
			
		public:
			static void setupNotificationAnimations();
			static void releaseNotificationAnimations();
			
			NotificationAnimation(int type):SmallAnimation(),animationType(type),currentAnimationStep(0)
			{
				
				setLastingTime(0.5f);
			};
			
			~NotificationAnimation(){};
			void animate();
			void draw();
			
		};
	}
}
#endif