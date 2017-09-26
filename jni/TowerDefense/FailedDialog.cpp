/*
 *  FailedDialog.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/19/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "FailedDialog.h"
#include "QuadHelper.h"
#include "GameTimeManager.h"

namespace AnimalCrackers
{
	namespace  TowerDefense {
		FailedDialog::FailedDialog():InGameMenu()
		{
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("newdialogs.png");
#else
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/newdialogs.png");
#endif
			
			background=new Texture(atlas,1,441,325,273);
			
			Texture *normal=new Texture(atlas,803,1,200,70);
			Texture *pressed=new Texture(atlas,803,74,200,70);
			
			continueButton=new GameButton();
			continueButton->setSize(167, 59);
			continueButton->setTexture(normal, pressed);
			
			 label=new Texture(atlas,328,474,212,25);
			
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			
			pointDigitTexture=new TextureAnimation(atlas,0,715,130,15,13,15);
			pointDigitTexture->addAnimation(k,10);
			pointDigitTexture->setAnimation(0);
			
			HotSpot::onReleaseDelegate ocr;
			ocr.bind(this,&FailedDialog::onContinue);
			continueButton->addOnReleaseHandler(ocr);
		};
		
		FailedDialog::~FailedDialog()
		{
			delete background;
			delete continueButton;
			delete label;
			
			delete pointDigitTexture;
		};
		
		
		void FailedDialog::draw()
		{
			int offset=0;
			
			if (isScrollingDown) 
			{
				offset=scrollOffset;
				scrollDown();
				
			}
			
			background->apply();
			
			QuadHelper::getSingleton().drawQuad(400-325*0.5f,240-273*0.5f-offset,325,273,background->getCoordinates());
			
			continueButton->setPosition(400, 200+173-60-offset);
			continueButton->draw();
			
			label->apply();
			QuadHelper::getSingleton().drawQuad(400-106,140-offset,212,25,label->getCoordinates());
			
			double currentTime=GameTimeManager::getSingleton().getCurrentTime();
			
			if (currentTime>goalPoints) {
				
			
			while (currentTime-oldUpdatePointsTime>0.05)
			{
				oldUpdatePointsTime+=0.05;
				
				currentPoints-=1;
				
				if (currentPoints<goalPoints) {
					continue;
				}
				
				refreshDigits(currentPoints);
			}
			}
			
			drawPoints(400-digits.size()*13*0.5,160+73-offset);
		}
		
		void FailedDialog::drawPoints(int x,int y)
		{
			int currentx=x;
			int currenty=y;
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) {
				pointDigitTexture->setAnimationStep(*iter);
				pointDigitTexture->apply();
				
				QuadHelper::getSingleton().drawQuad(currentx,y,13,15,pointDigitTexture->getCoordinates());
				
				currentx+=13;
			}
		}
		
		void FailedDialog::setupFailedDialog(int _from,int _to)
		{
			currentPoints=_from;
			goalPoints=_to;
			oldUpdatePointsTime=GameTimeManager::getSingleton().getCurrentTime();
		}
		
		void FailedDialog::refreshDigits(int value)
		{
			digits.clear();
			while (value>9) 
			{
				int di=value%10;
				digits.push_front(di);
				value=(value-di)/10;
			}
			
			digits.push_front(value);
		}
		
	}
}