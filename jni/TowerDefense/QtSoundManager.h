/*
 *  SoundManager.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __SoundManager__
#define __SoundManager__

#include "GlobalConfig.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class SoundManager  
		{
		public:
			enum SoundEffects
			{
				BUTTON,
				MACHINEGUN,
				LASER,
			};
		private:
			SoundManager(){};
			~SoundManager(){};
		public:
			static SoundManager & getSingleton()
			{
				static SoundManager obj;
				return obj;
			};
			
			void play(enum SoundEffects effect)
			{
			};
			
			void playImmediately(enum SoundEffects soundEffect)
			{
			};
			
			void nowListen(){};
		};
	}
}

#endif