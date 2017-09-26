/*
 *  MainMenuButton.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "MainMenuButton.h"

#ifdef	__ANDROID__

#include "AndroidSoundManager.h"
#else
#include "QtSoundManager.h"
#endif

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void MainMenuButton::beginLoadingAnimation(float _begin,float _interval)
		{
			animationInterval=_interval;
			animationBeginTime=_begin;
			hasLoadingAnimationFinished=false;
			loadingAnimationOldTime=GameTimeManager::getSingleton().getCurrentTime();
			elapsed=0;
			sizeFactor=minSize;
		};
		
		
		void MainMenuButton::onPress()
		{
			status=1;
		}
		
		void MainMenuButton::onRelease()
		{
			status=0;
			SoundManager::getSingleton().playImmediately(SoundManager::BUTTON);
		}
		
		void MainMenuButton::draw()
		{
			if (!hasLoadingAnimationFinished) 
			{
				updateLoadingAnimation();
				
				animationList[status]->apply();
				
				float rx=x-(float)(width*0.5f*sizeFactor);
				float ry=y-(float)(height*0.5f*sizeFactor);
				
				QuadHelper::getSingleton().drawQuad(rx,ry,width*sizeFactor,height*sizeFactor,animationList[status]->getCoordinates());
				
			}
			else
			{
				setCurrentAnimation(status);
				HotSpot::draw();
			}
		};
		
		void MainMenuButton::updateLoadingAnimation()
		{
			double currentTime=GameTimeManager::getSingleton().getCurrentTime();
			double interval=currentTime-loadingAnimationOldTime;
			
			if (animationBeginTime>0) 
			{
				animationBeginTime-=interval;
				if(animationBeginTime<0)
					elapsed=-animationBeginTime;
			}
			else 
			{
				elapsed+=interval;
			}
			
			
			while (elapsed>animationInterval) 
			{
				//////////////
				
				if (sizeFactor>=maxSize) 
				{
					hasLoadingAnimationFinished=true;
					sizeFactor=maxSize;
					break;
				}
				else 
				{
					sizeFactor+=0.001;
				}
				
				
				elapsed-=animationInterval;
			}
			
			
		};
		
	}
}