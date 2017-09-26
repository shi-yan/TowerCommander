/*
 *  LevelSelectorScreen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "LevelSelectorScreen.h"
#include "TextureAtlasManager.h"
#include "PlayerInfo.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		LevelSelectorScreen::LevelSelectorScreen():Screen(),currentLevel(0)
		{
			
#ifdef __ANDROID__
			int leveSelectorScreenAtlas=TextureAtlasManager::getSingleton().addNew("mainmenu.png");
			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("levelthumbs.png");
#else
			int leveSelectorScreenAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/mainmenu.png");
			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/levelthumbs.png");
#endif
			levelSelectorBackground=new Texture(leveSelectorScreenAtlas,0,479,800,480);
			achievementsButton=new MainMenuButton(200,71);
			playButton=new MainMenuButton(200,71);
			researchButton=new MainMenuButton(200,71);
			
			Texture *achievementsButtonTexture=new Texture(leveSelectorScreenAtlas,801,585,200,71);
			Texture *playButtonTexture=new Texture(leveSelectorScreenAtlas,801,293,200,71);
			Texture *researchButtonTexture=new Texture(leveSelectorScreenAtlas,801,439,200,71);
			
			Texture *achievementsButtonPressedTexture=new Texture(leveSelectorScreenAtlas,801,658,200,71);
			Texture *playButtonPressedTexture=new Texture(leveSelectorScreenAtlas,801,366,200,71);
			Texture *researchButtonPressedTexture=new Texture(leveSelectorScreenAtlas,801,512,200,71);
			
			playButton->addAnimation(playButtonTexture);
			achievementsButton->addAnimation(achievementsButtonTexture);
			researchButton->addAnimation(researchButtonTexture);
			playButton->addAnimation(playButtonPressedTexture);
			achievementsButton->addAnimation(achievementsButtonPressedTexture);
			researchButton->addAnimation(researchButtonPressedTexture);
			
			playButton->setPosition(670, 290);
			playButton->beginLoadingAnimation(1.0f, 0.05f);
			researchButton->setPosition(670, 363);
			researchButton->beginLoadingAnimation(3.0f, 0.05f);
			achievementsButton->setPosition(670,436);
			achievementsButton->beginLoadingAnimation(6.0f,0.05f);
			
			HotSpot::onReleaseDelegate opr;
			opr.bind(this,&LevelSelectorScreen::onPlayLevelSelected);
			playButton->addOnReleaseHandler(opr);
			
			HotSpot::onReleaseDelegate orr;
			orr.bind(this,&LevelSelectorScreen::onResearchButtonReleased);
			researchButton->addOnReleaseHandler(orr);
			
			HotSpot::onReleaseDelegate oar;
			oar.bind(this,&LevelSelectorScreen::onAchievementsButtonReleased);
			achievementsButton->addOnReleaseHandler(oar);
			
			leftButton=new MainMenuButton(102,101);
			rightButton=new MainMenuButton(102,101);
			
			Texture *leftTextureNormal=new Texture(leveSelectorScreenAtlas,801,730,102,101);
			Texture *leftTexturePressed=new Texture(leveSelectorScreenAtlas,801,730,102,101);
			
			Texture *rightTextureNormal=new Texture(leveSelectorScreenAtlas,905,730,102,101);
			Texture *rightTexturePressed=new Texture(leveSelectorScreenAtlas,905,730,102,101);
			
			leftButton->addAnimation(leftTextureNormal);
			leftButton->addAnimation(leftTexturePressed);
			rightButton->addAnimation(rightTextureNormal);
			rightButton->addAnimation(rightTexturePressed);
			
			leftButton->setSize(102,101);
			rightButton->setSize(102,101);
			
			HotSpot::onReleaseDelegate olr;
			olr.bind(this,&LevelSelectorScreen::onLeft);
			leftButton->addOnReleaseHandler(olr);
			
			HotSpot::onReleaseDelegate orrr;
			orrr.bind(this,&LevelSelectorScreen::onRight);
			rightButton->addOnReleaseHandler(orrr);
			
			leftButton->setPosition(100,417);
			
			rightButton->setPosition(238,417);
			
			levelDigitsTexture=new TextureAnimation(leveSelectorScreenAtlas,800,877,130,15,13,15);
			
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			
			levelDigitsTexture->addAnimation(k, 10);
			
			levelThumbs[0]=new Texture(levelThumbsAtlas,1,1,198,193);
			levelThumbs[1]=new Texture(levelThumbsAtlas,201,1,198,193);
			levelThumbs[2]=new Texture(levelThumbsAtlas,401,1,198,193);
			
			levelLocals[0]=new Texture(levelThumbsAtlas,601,1,117,18);
			levelLocals[1]=new Texture(levelThumbsAtlas,601,21,170,22);
			levelLocals[2]=new Texture(levelThumbsAtlas,601,45,114,18);
			
			fetchLevelInfoFromFile();
			
		}
		
		void LevelSelectorScreen::renew()
		{	
			playButton->beginLoadingAnimation(1.0f, 0.05f);
			researchButton->beginLoadingAnimation(3.0f, 0.05f);
			achievementsButton->beginLoadingAnimation(6.0f,0.05f);
			currentLevel=PlayerInfo::getSingleton().getCurrentLevel();
		
			refreshLevelDigits(levelDigits,currentLevel);
			
			refreshLevelDigits(moneyDigits,levelMoney[currentLevel]);
			refreshLevelDigits(enemyDigits,levelEnemies[currentLevel]);
			refreshLevelDigits(aiDigits,levelAIs[currentLevel]);
		}
		
		
		
		void LevelSelectorScreen::onLeft()
		{
			currentLevel--;
			if (currentLevel<0) 
			{
				currentLevel=overallLevel-1;
			}
			else if(currentLevel>=overallLevel)
			{
				currentLevel=0;
			}
			
			refreshLevelDigits(levelDigits,currentLevel);
			
			refreshLevelDigits(moneyDigits,levelMoney[currentLevel]);
			refreshLevelDigits(enemyDigits,levelEnemies[currentLevel]);
			refreshLevelDigits(aiDigits,levelAIs[currentLevel]);
		}
		
		void LevelSelectorScreen::fetchLevelInfoFromFile()
		{
			for (int i=0; i<overallLevel; ++i) 
			{
				
				char filename[256];

#ifdef __ANDROID__

				sprintf(filename, "/sdcard/TowerCommander/level%d.lev",i+1);
#else
				sprintf(filename, "../../../../assets/level%d.lev",i+1);
#endif
				FILE *fp=fopen(filename, "rb");
				
				int money=0;
				fread(&money, sizeof(int), 1, fp);
				
				int health=0;				
				fread(&health, sizeof(int), 1, fp);
				
				int overallEnemy=0;
				int wavecount=0;
				fread(&wavecount, sizeof(int), 1, fp);
				
				for (int e=0; e<wavecount; ++e) 
				{
					int time=0;
					fread(&time, sizeof(int), 1, fp);
					int enemycount=0;
					fread(&enemycount, sizeof(int), 1,fp );
					
					overallEnemy+=enemycount;
					
					for (int e=0; e<enemycount; ++e) 
					{
						int etype=0;
						fread(&etype, sizeof(int), 1, fp);
					}
				}
				
				levelAIs[i]=1;
				levelEnemies[i]=overallEnemy;
				levelMoney[i]=money;
				
				fclose(fp);
			}
		}
		
		void LevelSelectorScreen::onRight()
		{
		
			currentLevel++;
			if (currentLevel<0) {
				currentLevel=overallLevel-1;
			}
			else if(currentLevel>=overallLevel)
			{
				currentLevel=0;
			}
			
			refreshLevelDigits(levelDigits,currentLevel);
			
			refreshLevelDigits(moneyDigits,levelMoney[currentLevel]);
			refreshLevelDigits(enemyDigits,levelEnemies[currentLevel]);
			refreshLevelDigits(aiDigits,levelAIs[currentLevel]);
		}
		
		LevelSelectorScreen::~LevelSelectorScreen()
		{
			delete levelSelectorBackground;
			
	
			delete playButton;
			delete achievementsButton;
			delete researchButton;
			
			delete leftButton;
			delete rightButton;
			
			//delete levelLabel;
			
			for (int i=0; i<overallLevel; ++i) 
			{
				delete levelThumbs[i];
				delete levelLocals[i];
			}
			
		}
		
		void LevelSelectorScreen::onAchievementsButtonReleased()
		{
			for (std::vector<onAchievementsDelegate>::iterator iter=achievementsDelegateList.begin(); iter!=achievementsDelegateList.end(); iter++) 
			{
				(*iter)(currentLevel);
			}
		}
		
		void LevelSelectorScreen::onResearchButtonReleased()
		{
			for(std::vector<onResearchDelegate>::iterator iter=researchDelegateList.begin();iter!=researchDelegateList.end();iter++)
			{
				(*iter)();
			}
		}
		
		void LevelSelectorScreen::onPlayLevelSelected()
		{
			for (std::vector<onPlayDelegate>::iterator iter=playDelegateList.begin(); iter!=playDelegateList.end(); ++iter) 
			{
				(*iter)(currentLevel);
			}
		}
		
		void LevelSelectorScreen::addPlayButtonHandler(onPlayDelegate d)
		{
			playDelegateList.push_back(d);
		}
		
		void LevelSelectorScreen::addResearchButtonHandler(onResearchDelegate d)
		{
			researchDelegateList.push_back(d);
		}
		
		void LevelSelectorScreen::addAchievementsButtonHandler(onAchievementsDelegate d)
		{
			achievementsDelegateList.push_back(d);
		}
		
		void LevelSelectorScreen::handlePressEvent(int _x,int _y)
		{
			
			if (playButton->handlePressEvent(_x, _y)) {
				
			}
			else if(researchButton->handlePressEvent(_x, _y))
			{
			
			}
			else if(achievementsButton->handlePressEvent(_x, _y))
			{
			
			}
		}
		
		void LevelSelectorScreen::handleReleaseEvent(int _x,int _y)
		{
			if (playButton->handleReleaseEvent(_x, _y)) 
			{
			}
			else if(researchButton->handleReleaseEvent(_x, _y))
			{
			}
			else if(achievementsButton->handleReleaseEvent(_x, _y))
			{
			}
			else if(leftButton->handleReleaseEvent(_x,_y))
			{
			}
			else if(rightButton->handleReleaseEvent(_x, _y))
			{
			}
		}
		
		void LevelSelectorScreen::draw()
		{
			levelSelectorBackground->apply();
			QuadHelper::getSingleton().drawQuad(0,0,800,480,levelSelectorBackground->getCoordinates());
			
			playButton->draw();
			researchButton->draw();
			achievementsButton->draw();
			
			leftButton->draw();
			rightButton->draw();
			
			drawLevelPoints(559,626-480,levelDigits);
			
			drawLevelPoints(542, 688-480,enemyDigits);
			
			drawLevelPoints(524, 718-480,moneyDigits);
			
			drawLevelPoints(482, 748-480,aiDigits);
			
			levelThumbs[currentLevel]->apply();
			
			QuadHelper::getSingleton().drawQuad(87,125,198,193,levelThumbs[currentLevel]->getCoordinates());
			
			levelLocals[currentLevel]->apply();
			
			QuadHelper::getSingleton().drawQuad(556,176,levelLocals[currentLevel]->width,levelLocals[currentLevel]->height,levelLocals[currentLevel]->getCoordinates());
		
		}
		
		void LevelSelectorScreen::refreshLevelDigits(std::deque<int> &digits, int value)
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
		
		void LevelSelectorScreen::drawLevelPoints(int x,int y,std::deque<int> &digits)
		{
			int currentx=x;
			int currenty=y;
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) {
				levelDigitsTexture->setAnimationStep(*iter);
				levelDigitsTexture->apply();
				
				QuadHelper::getSingleton().drawQuad(currentx,y,13,15,levelDigitsTexture->getCoordinates());
				
				currentx+=13;
			}
		}
		
		
	}
}