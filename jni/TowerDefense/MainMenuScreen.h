/*
 *  MainMenuScreen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __MainMenuScreen__
#define __MainMenuScreen__

#include "GlobalConfig.h"
#include "Screen.h"
#include "MainMenuButton.h"
#include "QuadHelper.h"
#include <vector>
#include "QuitDialog.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class MainMenuScreen : public Screen
		{
		public:
			typedef fastdelegate::FastDelegate0<> onGameDelegate;
			typedef fastdelegate::FastDelegate0<> onOptionDelegate;
			typedef fastdelegate::FastDelegate0<> onAboutDelegate;
			typedef fastdelegate::FastDelegate0<> onExitDelegate;
			
		private:
			MainMenuButton *gameButton;
			MainMenuButton *aboutButton;
			Texture *mainMenuBackground;
			QuitDialog *quitDialog;
			
			std::vector<onGameDelegate> gameButtonDelegateList;
			std::vector<onOptionDelegate> optionButtonDelegateList;
			std::vector<onAboutDelegate> aboutButtonDelegateList;
			std::vector<onExitDelegate> onExitDelegateList;
			MainMenuScreen();
			~MainMenuScreen();
			
			bool isQuiting;
		public:
			
			static MainMenuScreen & getSingleton()
			{
				static MainMenuScreen obj;
				return obj;
			};
			
			void gameButtonPressed()
			{
			};
			
			void renew();
			
			void gameButtonReleased();
			
			void onExit()
			{
				for (std::vector<onExitDelegate>::iterator iter=onExitDelegateList.begin(); iter!=onExitDelegateList.end(); ++iter) {
					(*iter)();
				}
			};
			
			void onHelpReleased();
			
			void addOnExitHandler(onExitDelegate d)
			{
				onExitDelegateList.push_back(d);
			};
			
			void addGameButtonHandler(onGameDelegate d)
			{
				gameButtonDelegateList.push_back(d);
			};
			
		
			void addOptionButtonHandler(onOptionDelegate d)
			{
				optionButtonDelegateList.push_back(d);
			};
			
			void addAboutButtonHandler(onAboutDelegate d)
			{
				aboutButtonDelegateList.push_back(d);
			};
			
			void draw();
			
			void handlePressEvent(int _x,int _y);
			
			void handleReleaseEvent(int _x,int _y);
			
			void onQuitYes();
			
			void onQuitNo();
			
			void onBack();
			
		};
		
	}
}

#endif