/*
 *  TowerIconButton.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __TowerIconButton__
#define __TowerIconButton__

#include "HotSpot.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class TowerIconButton : public HotSpot 
		{
		public:
			typedef fastdelegate::FastDelegate1<int> onIconPressedDelegate;
			
		public:
			TowerIconButton(int width,int height,int _id);
			~TowerIconButton(){};
			
			int getID()
			{
				return ID;
			};
			
			void addIconPressedHandler(onIconPressedDelegate d);
			
			void onPressed();
			
		private:
			int ID;
			std::vector<onIconPressedDelegate> iconPressedDelegateList;
			
		};
	}
}

#endif