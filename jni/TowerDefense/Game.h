/*
 *  Game.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/20/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Game__
#define __Game__

#include "GlobalConfig.h"
#include "MainMenuScreen.h"
#include "LevelSelectorScreen.h"
#include "GameTimeManager.h"
#include "GameScreen.h"
#include "ResearchScreen.h"
#include "AchievementsScreen.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class Game  
		{
		private:
			bool isInTransition;
			double transitionOldTime;
			double transitionSpeed;
			double transitionElapsed;
			float transitionProgress;
			Screen *currentScreen;
			bool hasInitialized;
			
			bool exitFlag;

			Game():
			   isInTransition(false),
			   transitionOldTime(0.0),
			   transitionSpeed(0.0),
			   transitionElapsed(0.0),
			   transitionProgress(0.0f),
			   currentScreen(NULL),
			hasInitialized(false),exitFlag(false)
			{};

			~Game();
			
			void drawTransition();
			
			void drawMask(float v);
			
			void beginTransition(Screen *_future,double _speed);
			
			Screen *futureScreen;
			
		public:
			static Game & getSingleton()
			{
				static Game obj;
				return obj;
			};
			
			void init();
			
			bool getExitFlag()
			{
				return exitFlag;
			};
			
			void onExit()
			{
				exitFlag=true;
			};
			
			bool initializedBefore()
			{
				return hasInitialized;
			};
			
			void restoreOpenGLContext();
			
			
			void selectGameMenu()
			{
				LevelSelectorScreen::getSingleton().renew();
				beginTransition(&LevelSelectorScreen::getSingleton(),1.0f);
			};
			
			void selectOptionMenu()
			{
				currentScreen=NULL;
			};
			
			void selectAboutMenu()
			{
				currentScreen=NULL;
			};
			
			void selectLevel(int level)
			{
				GameScreen::getSingleton().clearLevel();
				GameScreen::getSingleton().initLevel(level);
				beginTransition(&GameScreen::getSingleton(), 1.0f);
			};
			
			void onLevelBack()
			{
				MainMenuScreen::getSingleton().renew();
				beginTransition(&MainMenuScreen::getSingleton(), 1.0f);
			};
			
			void onResearch()
			{
			//	ResearchScreen::getSingleton().renew();
			//	beginTransition(&ResearchScreen::getSingleton(), 1.0f);
			};
			
			void onResearchBack()
			{
				LevelSelectorScreen::getSingleton().renew();
				beginTransition(&LevelSelectorScreen::getSingleton(), 1.0f);
			};
			
			void onAchievements(int level)
			{
				AchievementsScreen::getSingleton().renew( level);
				beginTransition(&AchievementsScreen::getSingleton(), 1.0f);
			};
			
			void onAchievementsBack()
			{
				//AchievementsScreen::getSingleton().release();
				LevelSelectorScreen::getSingleton().renew();
				beginTransition(&LevelSelectorScreen::getSingleton(), 1.0f);
			};
			
			void onGameReturn()
			{
				LevelSelectorScreen::getSingleton().renew();
				beginTransition(&LevelSelectorScreen::getSingleton(), 1.0f);
			};
			
			void draw()
			{
				GameTimeManager::getSingleton().refreshCurrentTime();
				if(isInTransition)
					drawTransition();
				else
				if(currentScreen)
					currentScreen->draw();
			};
			
			void handlePressEvent(int x,int y)
			{
				
				if(currentScreen && !isInTransition)
					currentScreen->handlePressEvent( x, y);
			};
			
			void handleReleaseEvent(int x,int y)
			{
				
				if(currentScreen&& !isInTransition)
				currentScreen->handleReleaseEvent( x, y);
			};
			
			void handleMoveEvent(int x,int y)
			{
				if(currentScreen&& !isInTransition)
					currentScreen->handleMoveEvent(x,y);
			}
			
			void handleBackEvent()
			{
				if(currentScreen&& !isInTransition)
					currentScreen->handleBackEvent();
			}
		};
	}
}

#endif