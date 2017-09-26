/*
 *  LifeBar.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __LifeBar__
#define __LifeBar__

#include "GlobalConfig.h"
#include "UIItem.h"
#include "QuadHelper.h"
#include "TextureAnimation.h"
#include <deque>

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class LifeBar : public UIItem 
		{
		private:
			int life;
			std::deque<int> digits;
			
			Texture *digitTextures[10];
			TextureAnimation *heartTexture;
			
			int atlasID;
			
			LifeBar():UIItem(40,40),life(0)
			{};
			
			~LifeBar()
			{
				delete heartTexture;
				for (int i=0; i<10; ++i) 
				{
					delete digitTextures[i];
				}
			};
			
		public:
			void playAnimation()
			{
			
			};
			
			void addLife(int incre)
			{
				setLife(life+incre);
			};
			
			int getLife()
			{
				return life;
			};
			
			void init(int _atlas,int lif=0);
		
			void setLife(int lif);
			
			static LifeBar & getSingleton()
			{
				static LifeBar obj;
				return obj;
			};
			
			void draw();
		};
	}
}

#endif