/*
 *  AndroidControlManager.h
 *  towerdefense
 *
 *  Created by Shi Yan on 12/4/10.
 *  Copyright 2010 Animal Crackers Games. All rights reserved.
 *
 */

#ifndef __AndroidControlManager__
#define __AndroidControlManager__
#include <jni.h>
#include "GlobalConfig.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class AndroidControlManager  {
		public:
			
			static jobject Android_mainActivityObject;
			static jmethodID Android_showHelpDialog;
			static JavaVM *jVM;
			
		private:
			AndroidControlManager(){};
			~AndroidControlManager(){};
		public:
			static AndroidControlManager & getSingleton()
			{
				static AndroidControlManager obj;
				return obj;
			};
			
			void showHelpDialog();
		
		};
	}
}

#endif