/*
 *  AndroidSoundManager.h
 *  towerdefense
 *
 *  Created by Shi Yan on 12/1/10.
 *  Copyright 2010 Animal Crackers Games. All rights reserved.
 *
 */

#ifndef __SoundManager__
#define __SoundManager__

#include "GlobalConfig.h"
#include <jni.h>

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		struct ShouldPlay
		{
			bool shouldPlay;
			double lastPlayed;
		};
		
		class SoundManager
		{
		public:
			enum SoundEffects
			{
				BUTTON,
				MACHINEGUN,
				LASER,
				SOUND_EFFECT_COUNT,
				
			};
			
			static jclass Android_soundClass;
			static jmethodID Android_playMethodID;
			static JavaVM *jVM;
			
		private:
			SoundManager()
			{
				for (int i=0; i<SOUND_EFFECT_COUNT; ++i) 
				{
					shouldPlay[i].shouldPlay=false;
				}
			};
			
			~SoundManager(){};
			
			struct ShouldPlay shouldPlay[SOUND_EFFECT_COUNT];
			
		public:
			static SoundManager & getSingleton()
			{
				static SoundManager obj;
				return obj;
			};
			
			
			void play(enum SoundEffects soundEffect);
			
			void playImmediately(enum SoundEffects soundEffect);
			
			void nowListen();
			
		};
	}
}

#endif