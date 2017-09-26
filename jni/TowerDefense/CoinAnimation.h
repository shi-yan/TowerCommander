/*
 *  CoinAnimation.h
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __CoinAnimation__
#define __CoinAnimation__

#include "GlobalConfig.h"
#include "SmallAnimation.h"
#include <deque>
#include "TextureAnimation.h"
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class CoinAnimation : public SmallAnimation 
		{
		private:
			static TextureAnimation * digitTexture[10];
			static TextureAnimation * coinTexture;
			std::deque<int> digits;
			int currentTransparency;
			
		public:
			static void setDigitTextures();
			static void releaseDigitTextures();
			
			CoinAnimation(int mon);
			~CoinAnimation(){};
			
			void draw();
			void animate();
		};
	}
}

#endif