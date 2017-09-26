/*
 *  GameButton.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 10/12/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "GameButton.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		GameButton::GameButton():HotSpot(46,53),status(0)
		{
			HotSpot::onPressDelegate dp;
			dp.bind(this,&GameButton::onPress);
			addOnPressHandler(dp);
			
			HotSpot::onReleaseDelegate dr;
			dr.bind(this,&GameButton::onRelease);
			addOnReleaseHandler(dr);
		};
		
		void GameButton::setTexture(Texture *normal,Texture *pressed)
		{
			addAnimation(normal);
			addAnimation(pressed);
		};
		
		void GameButton::onPress()
		{
		//	isPressed=true;
			if(status)
				status=0;
			else 
			{
				status=1;
			}
		};
		
		void GameButton::onRelease()
		{
		//	isPressed=false;
			if(status)
				status=0;
			else 
			{
				status=1;
			}
		};
		
		GameButton::~GameButton()
		{
		};
		
		void GameButton::setStatus(int _status)
		{
			status=_status;
		}
		
		void GameButton::draw()
		{
		
				animationList[status]->apply();
				QuadHelper::getSingleton().drawQuad(x-width*0.5f,y-height*0.5f,width,height,animationList[status]->getCoordinates());
			
		};
		
		
	}
}