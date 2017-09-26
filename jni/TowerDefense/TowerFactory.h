/*
 *  TowerFactory.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */


#ifndef __TowerFactory__
#define __TowerFactory__

#include "GlobalConfig.h"
#include "Texture.h"
#include "Tower.h"
#include "GameMap.h"
#include "TextureAnimation.h"

namespace AnimalCrackers 
{

	namespace TowerDefense 
	{
		class TowerFactory
		{
	
		private:
		
			
			TowerFactory(){};
			~TowerFactory(){};
	
		public:
			static TowerFactory & getSingleton()
			{
				static TowerFactory obj;
				return obj;
			}
			
		
			void init()
			{		
			}
			
			void prepareDifferentAngel(TextureAnimation *ta)
			{
				for (int i=0; i<12; ++i) 
				{
					int k[1];
					k[0]=i;
					ta->addAnimation(k, 1);

				}
			}
	
			Tower *getTower(int x,int y,int type);
			
			
		};
	}
}

#endif