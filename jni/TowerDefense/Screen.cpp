/*
 *  Screen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "Screen.h"
#ifdef	__ANDROID__

#include "AndroidSoundManager.h"
#else
#include "QtSoundManager.h"
#endif

namespace AnimalCrackers {
	namespace TowerDefense {
		
		Screen::Screen()
		{
			onBackDelegate obd;
			obd.bind(this,&Screen::onBack);
			addBackEventHandler(obd);
		}
		
		Screen::~Screen()
		{
		
		}
		
		void Screen::init(int _width,int _height)
		{
			width=_width;
			height=_height;
		}
		
		void Screen::reSize(int _width,int _height)
		{
			width=_width;
			height=_height;
		}
		
		void Screen::draw()
		{
		}
		
		void Screen::onBack()
		{
			
			SoundManager::getSingleton().playImmediately(SoundManager::BUTTON);
		}
		
		
		void Screen::handlePressEvent(int _x,int _y)
		{
			
		}
		
		void Screen::handleReleaseEvent(int _x,int _y)
		{
			
		}
		
		void Screen::handleMoveEvent(int _x,int _y)
		{
			
		}
		
		void Screen::addBackEventHandler(onBackDelegate d)
		{
			backDelegateList.push_back(d);
		}

		
		void Screen::handleBackEvent()
		{
			for (std::vector<onBackDelegate>::iterator iter=backDelegateList.begin(); iter!=backDelegateList.end(); ++iter) {
				(*iter)();
			}
		}
	}
}
