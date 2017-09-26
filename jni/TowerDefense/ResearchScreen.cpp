/*
 *  ResearchScreen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "ResearchScreen.h"
#include "QuadHelper.h"
#include "PlayerInfo.h"
#include "Tower.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		ResearchScreen::ResearchScreen():isShowResearchButton(false),isShowLock(false)
		{
			
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("lab.png");
			int towerAtlas=TextureAtlasManager::getSingleton().addNew("tower.png");
#else
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/lab.png");
			int towerAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/tower.png");
#endif		
			background=new Texture(atlas,0,0,800,480);
			
			researchButton=new MainMenuButton(200,71);
			
			Texture *researchButtonTexture=new Texture(atlas,801,1,200,71);
			
			Texture *researchButtonPressedTexture=new Texture(atlas,801,74,200,71);
			
			
			researchButton->addAnimation(researchButtonTexture);
			researchButton->addAnimation(researchButtonPressedTexture);
			
			researchButton->setPosition(670,416);
			researchButton->beginLoadingAnimation(1.0f, 0.05f);
			
			Texture *towerIcons[22];
			towerIcons[0]=new Texture(towerAtlas,0,0,40,60);
			towerIcons[1]=new Texture(towerAtlas,0,60,40,60);
			towerIcons[2]=new Texture(towerAtlas,0,120,40,60);
			towerIcons[3]=new Texture(towerAtlas,0,180,40,60);
			towerIcons[4]=new Texture(towerAtlas,0,240,40,60);
			towerIcons[5]=new Texture(towerAtlas,0,300,40,60);
			towerIcons[6]=new Texture(towerAtlas,0,360,40,60);
			towerIcons[7]=new Texture(towerAtlas,0,420,40,60);
			towerIcons[8]=new Texture(towerAtlas,0,480,40,60);
			towerIcons[9]=new Texture(towerAtlas,0,540,40,60);
			towerIcons[10]=new Texture(towerAtlas,0,600,40,60);
			towerIcons[11]=new Texture(towerAtlas,0,660,40,60);
			towerIcons[12]=new Texture(towerAtlas,0,720,40,60);
			towerIcons[13]=new Texture(towerAtlas,0,780,40,60);
			towerIcons[14]=new Texture(towerAtlas,0,840,40,60);
			towerIcons[15]=new Texture(towerAtlas,0,900,40,60);
			towerIcons[16]=new Texture(towerAtlas,480,780,40,60);
			towerIcons[17]=new Texture(towerAtlas,480,720,40,60);
			towerIcons[18]=new Texture(towerAtlas,480,660,40,60);
			towerIcons[19]=new Texture(towerAtlas,480,600,40,60);
			towerIcons[21]=new Texture(towerAtlas,480,540,40,60);
			towerIcons[20]=new Texture(towerAtlas,480,480,40,60);
			
	
			
			int x=60;
			int y=70;
			
			for (int i=0; i<22; ++i) 
			{
				x=60+(i%5)*60;
				y=70+70*(i/5);
				towerButtons[i]=new TowerIconButton(40,60,i);
				towerButtons[i]->addAnimation(towerIcons[i]);
				towerButtons[i]->setPosition(x+20,y+30);
				
				TowerIconButton::onIconPressedDelegate oipd;
				oipd.bind(this,&ResearchScreen::onIconPressed);
				towerButtons[i]->addIconPressedHandler(oipd);
			}
		
			towerButtons[20]->setPosition(60+200,100+70*4);
			towerButtons[21]->setPosition(60+260,100+70*4);
			
			circle=new Texture(atlas,801,147,54,69);
			
			circlex=60-7;
			circley=70-4;
			
			
			HotSpot::onReleaseDelegate ord;
			ord.bind(this,&ResearchScreen::onResearch);
			researchButton->addOnReleaseHandler(ord);
		}
		
		void ResearchScreen::onIconPressed(int i)
		{
			circlex=60+(i%5)*60-6;
			circley=70+70*(i/5)-2;
			
			if (i==20) {
				
				circlex=60+180-6;
				circley=70+70*4-2;
			}
			else if(i==21)
			{
				circlex=60+240-6;
				circley=70+70*4-2;
			}
			
			//point level, not purchased yet
			if (!PlayerInfo::getSingleton().getTowerAvailable(i) && Tower::getLevel(i)<=PlayerInfo::getSingleton().getCurrentLevel() && PlayerInfo::getSingleton().getPoints()>=Tower::getPoints(i)) {
				isShowResearchButton=true;
			}
			else if(Tower::getLevel(i)>PlayerInfo::getSingleton().getCurrentLevel()) {
				isShowLock=true;
				isShowResearchButton=false;
			}
			else {
				isShowResearchButton=false;
			}


			
		}
		
		void ResearchScreen::onResearch()
		{
			
		}
		
		void ResearchScreen::renew()
		{
			researchButton->beginLoadingAnimation(1.0f, 0.05f);
		}
		
		ResearchScreen::~ResearchScreen()
		{
			delete researchButton;
			delete background;
			
			for (int i=0; i<22; ++i) {
				delete towerButtons[i];
			}
			
			delete [] towerButtons;
		}
		
		void ResearchScreen::draw()
		{
			background->apply();
			QuadHelper::getSingleton().drawQuad(0,0,800,480,background->getCoordinates());
			
			if(isShowResearchButton)
			researchButton->draw();
			
		for (int i=0; i<22; ++i) 
		{
			towerButtons[i]->draw();
		}
			
			circle->apply();
			QuadHelper::getSingleton().drawQuad(circlex,circley,53,68,circle->getCoordinates());
			
		}
		
		
		void ResearchScreen::handlePressEvent(int x,int y)
		{
			for (int i=0; i<22; ++i) 
			{
				if (towerButtons[i]->handlePressEvent(x, y)) 
				{
					return;
				}
			}
			
			if (isShowResearchButton && researchButton->handlePressEvent(x, y)) 
			{
				
			}
		};
		
		void ResearchScreen::handleReleaseEvent(int x,int y)
		{
			if (isShowResearchButton && researchButton->handleReleaseEvent(x, y)) 
			{
				
			}
		};
	}
}