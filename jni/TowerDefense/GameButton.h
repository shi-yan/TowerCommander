/*
 *  GameButton.h
 *  towerdefense
 *
 *  Created by Shi Yan on 10/12/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __GameButton__
#define __GameButton__

#include "GlobalConfig.h"
#include "Texture.h"
#include "FastDelegate.h"
#include "HotSpot.h"
#include <vector>
#include "QuadHelper.h"
#include "Point.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class GameButton : public HotSpot
		{
		private:
			int status;
			
		public:
			GameButton();
			
			void setTexture(Texture *normal,Texture *pressed);
			
			void onPress();
			
			void onRelease();
			
			void setStatus(int);
			
			virtual ~GameButton();
			
			void draw();
		};
	}
}

#endif