/*
 *  AndroidControlManager.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 12/4/10.
 *  Copyright 2010 Animal Crackers Games. All rights reserved.
 *
 */

#include "AndroidControlManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense {
		
		jobject AndroidControlManager::Android_mainActivityObject=0;
		jmethodID AndroidControlManager::Android_showHelpDialog=0;
		JavaVM *AndroidControlManager::jVM=0;
		
		void AndroidControlManager::showHelpDialog()
		{
			LOGI("create texture from png 1");
			JNIEnv *env;
			
			LOGI("create texture from png 2");
			jVM->GetEnv( (void**) &env, JNI_VERSION_1_4);
			
			LOGI("create texture from png 3");
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, "TowerCommander_JNI", "writeAudio audioBuffer=%p offset=%d length=%d");
#endif
			
			
			
			LOGI("create texture from png 4");
			env->CallObjectMethod( Android_mainActivityObject,Android_showHelpDialog);
			
			
		}
	}
}