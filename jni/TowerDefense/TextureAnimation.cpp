/*
 *  TextureAnimation.cpp
 *  JumpNRun
 *
 *  Created by Shi Yan on 8/31/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "TextureAnimation.h"
#include "GameTimeManager.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		void TextureAnimation::animate()
		{
			if(timeOfLastAnimationStep<0)
			{
				timeOfLastAnimationStep=GameTimeManager::getSingleton().getCurrentTime();
			}
			else
			{
				double currentTime=GameTimeManager::getSingleton().getCurrentTime();
				
				double intervel=currentTime-timeOfLastAnimationStep;
				
				while(intervel-speed>=0.0f)
				{
					
					if(isRepeat)
					{
						currentStep=(currentStep+1)%animations[currentAnimationID].size();
					}
					else 
					{
						if (!isFinished) 
						{
							if(currentStep<animations[currentAnimationID].size()-1)
								currentStep++;
							else 
							{
								isFinished=true;
							}
							
						}
					}
					
					timeOfLastAnimationStep+=speed;
					intervel-=speed;
				}
			}
		}
		
	}
}