/*
 *  TowerIconButton.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "TowerIconButton.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		TowerIconButton::TowerIconButton(int width,int height,int _id):HotSpot(width,height),ID(_id)
		{
			HotSpot::onPressDelegate opd;
			opd.bind(this,&TowerIconButton::onPressed);
			addOnPressHandler(opd);
		
		}
		
		
		void TowerIconButton::onPressed()
		{
			for (std::vector<onIconPressedDelegate>::iterator iter=iconPressedDelegateList.begin(); iter!=iconPressedDelegateList.end(); ++iter) 
			{
				(*iter)(getID());
			}
		}
		
		void TowerIconButton::addIconPressedHandler(onIconPressedDelegate d)
		{
			iconPressedDelegateList.push_back(d);
		}
	}
}