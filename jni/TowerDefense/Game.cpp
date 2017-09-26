/*
 *  Game.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/20/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "Game.h"
#include "PlayerInfo.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		Game::~Game()
		{
			currentScreen=NULL;
		};
		
		void Game::drawTransition()
		{
			double transitionCurrentTime=GameTimeManager::getSingleton().getCurrentTime();
			
			double interveral=transitionCurrentTime-transitionOldTime;
			
			transitionElapsed+=interveral;
			
			while (transitionElapsed>transitionSpeed) 
			{
				
				transitionProgress+=0.01;
				
				transitionElapsed-=transitionSpeed;
			}
			
			
			if(transitionProgress<0.5f)
			{
				
				currentScreen->draw();
				drawMask(transitionProgress*2.0f);
			}
			else if(transitionProgress>=0.5f && transitionProgress<1.0f)
			{
				
				futureScreen->draw();
				drawMask((1.0f-transitionProgress)*2.0f);
			}
			else if(transitionProgress>=1.0f) 
			{
				currentScreen=futureScreen;
				isInTransition=false;
				currentScreen->draw();
			}
			
			
		};
		
		
		void Game::drawMask(float v)
		{
			glEnable(GL_BLEND);
			glColor4f(0.0f, 0.0f, 0.0f, v);
			QuadHelper::getSingleton().drawQuad(0,0,800,480);
		};
		
		void Game::beginTransition(Screen *_future,double _speed)
		{
			isInTransition=true;
			futureScreen=_future;
			transitionOldTime=GameTimeManager::getSingleton().getCurrentTime();
			transitionSpeed=_speed;
			transitionProgress=0.0f;
			transitionElapsed=0.0f;
		};
		
		void Game::restoreOpenGLContext()
		{
			exitFlag=false;
			TextureAtlasManager::getSingleton().restoreOpenGLTextures();
		}
		
		void Game::init()
		{
		//	LOGI("newed player info file1");
			PlayerInfo::getSingleton().loadFromFile();
		//	LOGI("newed player info file2");
			
			exitFlag=false;
			
			hasInitialized=true;
			GameTimeManager::getSingleton().refreshCurrentTime();
			GameTimeManager::getSingleton().gameBegin();
	//	LOGI("newed player info file3");
			
			MainMenuScreen::onGameDelegate dgame;
			dgame.bind(this,&Game::selectGameMenu);
			MainMenuScreen::getSingleton().addGameButtonHandler(dgame);
		//	LOGI("newed player info file4");
			MainMenuScreen::onAboutDelegate dabout;
			dabout.bind(this,&Game::selectAboutMenu);
			MainMenuScreen::getSingleton().addAboutButtonHandler(dabout);
		//	LOGI("newed player info file5");
			
			LevelSelectorScreen::onPlayDelegate dlevel;
			dlevel.bind(this,&Game::selectLevel);
			LevelSelectorScreen::getSingleton().addPlayButtonHandler(dlevel);
		//	LOGI("newed player info file6");
			Screen::onBackDelegate dlback;
			dlback.bind(this,&Game::onLevelBack);
			LevelSelectorScreen::getSingleton().addBackEventHandler(dlback);
			
		//	LOGI("newed player info file7");
			LevelSelectorScreen::onResearchDelegate dresearch;
			dresearch.bind(this,&Game::onResearch);
			LevelSelectorScreen::getSingleton().addResearchButtonHandler(dresearch);
		//	LOGI("newed player info file8");
			Screen::onBackDelegate drback;
			drback.bind(this,&Game::onResearchBack);
			ResearchScreen::getSingleton().addBackEventHandler(drback);
		//	LOGI("newed player info file9");
			
			LevelSelectorScreen::onAchievementsDelegate dachievements;
			dachievements.bind(this,&Game::onAchievements);
			LevelSelectorScreen::getSingleton().addAchievementsButtonHandler(dachievements);
		//	LOGI("newed player info file10");
			Screen::onBackDelegate daback;
			daback.bind(this,&Game::onAchievementsBack);
			AchievementsScreen::getSingleton().addBackEventHandler(daback);
		//	LOGI("newed player info file11");
			
			GameScreen::onGameReturnDelegate ogr;
			ogr.bind(this,&Game::onGameReturn);
			GameScreen::getSingleton().addGameReturnHandler(ogr);
		//	LOGI("newed player info file12");
			MainMenuScreen::onExitDelegate med;
			med.bind(this,&Game::onExit);
			MainMenuScreen::getSingleton().addOnExitHandler(med);
		//	LOGI("newed player info file13");
			currentScreen=&MainMenuScreen::getSingleton();
		};
		
		
	}
}