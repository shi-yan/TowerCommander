/*
 *  NotificationAnimation.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/12/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "NotificationAnimation.h"
#include "TextureAtlasManager.h"
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		TextureAnimation *NotificationAnimation::notificationTextures[3];
		
		void NotificationAnimation::setupNotificationAnimations()
		{
#ifdef __ANDROID__
			
			int atlas=TextureAtlasManager::getSingleton().addNew("notification.png");
#else
			
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/notification.png");
#endif
			
			notificationTextures[0]=new TextureAnimation(atlas,0,0,270,106,270,106/4);
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			notificationTextures[0]->addAnimation(k,4);
			notificationTextures[0]->setAnimation(0);
			
			notificationTextures[1]=new TextureAnimation(atlas,0,104,399,116,399,116/4);
			notificationTextures[1]->addAnimation(k, 4);
			notificationTextures[1]->setAnimation(0);
			
			notificationTextures[2]=new TextureAnimation(atlas,0,218,352,96,352,96/4);
			notificationTextures[2]->addAnimation(k, 4);
			notificationTextures[2]->setAnimation(0);
			
			
		}
		
		void NotificationAnimation::releaseNotificationAnimations()
		{
			for(int i=0;i<3;++i)
			{
				if(notificationTextures[i])
					delete notificationTextures[i];
			}
		}
		
		
		
		void NotificationAnimation::draw()
		{
			
			notificationTextures[animationType]->setAnimationStep(currentAnimationStep);
			
			notificationTextures[animationType]->apply();
			
			QuadHelper::getSingleton().drawQuad(400-notificationTextures[animationType]->getTileWidth()*0.5f,240-notificationTextures[animationType]->getTileHeight()*0.5f,notificationTextures[animationType]->getTileWidth(),notificationTextures[animationType]->getTileHeight(),notificationTextures[animationType]->getCoordinates());
			
		}
		
		void NotificationAnimation::animate()
		{
			SmallAnimation::animate();
			int aniSize=notificationTextures[animationType]->getCurrentAnimationFrames();
			currentAnimationStep=(float)aniSize*elapsedTime/lastingTime;
			if (currentAnimationStep==aniSize) {
				currentAnimationStep=aniSize-1;
			}
		}
		
	}
}