/*
 *  AndroidSoundManager.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 12/1/10.
 *  Copyright 2010 Animal Crackers Games. All rights reserved.
 *
 */

#include "AndroidSoundManager.h"
#include "GameTimeManager.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		jclass SoundManager::Android_soundClass=0;
		jmethodID SoundManager::Android_playMethodID=0;
		JavaVM *SoundManager::jVM=0;
		
		
		
		void SoundManager::play(enum SoundEffects soundEffect)
		{
			shouldPlay[soundEffect].shouldPlay=true;
		};
		
		void SoundManager::playImmediately(enum SoundEffects soundEffect)
		{
			JNIEnv *env;
			
			jVM->GetEnv( (void**) &env, JNI_VERSION_1_4);
			
			
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, "TowerCommander_JNI", "writeAudio audioBuffer=%p offset=%d length=%d");
#endif
			
			env->CallStaticIntMethod( Android_soundClass, Android_playMethodID, soundEffect);
			
		}
		
		void SoundManager::nowListen()
		{
			
			double currentTime=GameTimeManager::getSingleton().getCurrentTime();
			
			JNIEnv *env;
			
			jVM->GetEnv( (void**) &env, JNI_VERSION_1_4);
			
			
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, "TowerCommander_JNI", "writeAudio audioBuffer=%p offset=%d length=%d");
#endif
			
			for (int i=0; i<SOUND_EFFECT_COUNT; ++i) 
			{
				if (shouldPlay[i].shouldPlay) 
				{
					if (currentTime-shouldPlay[i].lastPlayed>1.0) 
					{
						shouldPlay[i].lastPlayed=currentTime;
						env->CallStaticIntMethod( Android_soundClass, Android_playMethodID, i);
					}
					
					shouldPlay[i].shouldPlay=false;
				}
				else
				{
					shouldPlay[i].lastPlayed=currentTime-0.800001;
				}
			}
			
		}
	}
}