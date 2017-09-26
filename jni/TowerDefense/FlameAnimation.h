/*
 *  FlameAnimation.h
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __FlameAnimation__
#define __FlameAnimation__

#include "GlobalConfig.h"
#include "SmallAnimation.h"
#include "TextureAnimation.h"
#include "QuadHelper.h"
namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class FlameAnimation : public SmallAnimation 
		{
		private:
			static TextureAnimation *flameTextures[18];
			int animeType;
			int currentAnimationStep;
			
		public:
			static void setFlameTextures();
			static void releaseFlameTextures();
			
			FlameAnimation(int type):SmallAnimation(),animeType(type),currentAnimationStep(0)
			{};
			
			~FlameAnimation(){};
			void animate();
			void draw();
		};
	}
}
#endif