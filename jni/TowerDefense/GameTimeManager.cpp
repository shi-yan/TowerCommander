/*
 *  GameTimeManager.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/20/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "GameTimeManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		double GameTimeManager::gameBegin()
		{
			return beginTime=getCurrentTime();
		};
		
		double GameTimeManager::getElapsedTime()
		{
			return getCurrentTime()-beginTime;
		};
		
		double GameTimeManager::refreshCurrentTime()
		{
			struct timeval tim;
			
			gettimeofday(&tim, NULL); 
			
			double time=tim.tv_sec+((double)tim.tv_usec/1000000.0);
			
			return currentTime=time;
		};
		
		double GameTimeManager::getCurrentTime()
		{
				return currentTime;
		};
	}
}