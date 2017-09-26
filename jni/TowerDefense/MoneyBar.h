/*
 *  MoneyBar.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __MoneyBar__
#define __MoneyBar__

#include "GlobalConfig.h"
#include "UIItem.h"
#include <vector>
#include "TextureAtlas.h"
#include "QuadHelper.h"
#include <deque>

namespace AnimalCrackers 
{

	namespace TowerDefense 
	{
		class MoneyBar : public UIItem 
		{
		private:
			int money;
			std::deque<int> digits;
			
			Texture *digitTextures[10];
			TextureAnimation *coinTexture;
			
			int atlasID;
			
			MoneyBar():UIItem(40,40),money(0)
			{};
			
			~MoneyBar()
			{
				delete coinTexture;
				for (int i=0; i<10; ++i) 
				{
					delete digitTextures[i];
				}
			};
			

			
		public:
			void addMoney(int incre)
			{
				setMoney(money+incre);
			};
			
					
			void decreaseMoney(int decre)
			{
				setMoney(money-decre);
			};
			
			int getMoney()
			{
				return money;
			};
			
			void init(int _atlas,int mon=0);
			
			void setMoney(int mon);
			
			static MoneyBar & getSingleton()
			{
				static MoneyBar obj;
				return obj;
			};
			
			void draw();
			
		};
	}

}

#endif