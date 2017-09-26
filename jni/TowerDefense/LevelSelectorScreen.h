/*
 *  LevelSelectorScreen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __LevelSelectorScreen__
#define __LevelSelectorScreen__

#include "GlobalConfig.h"
#include "Screen.h"
#include <vector>
#include "Texture.h"
#include "FastDelegate.h"
#include "MainMenuButton.h"
#include <deque>

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class LevelSelectorScreen : public Screen
		{
		public:
			typedef fastdelegate::FastDelegate1<int> onAchievementsDelegate;
			typedef fastdelegate::FastDelegate1<int> onPlayDelegate;
			typedef fastdelegate::FastDelegate0<> onResearchDelegate;
		
		
		private:
			LevelSelectorScreen();
			
			~LevelSelectorScreen();
			
			Texture* levelSelectorBackground;
			MainMenuButton *achievementsButton;
			MainMenuButton *playButton;
			MainMenuButton *researchButton;
			
			MainMenuButton *leftButton;
			MainMenuButton *rightButton;
			
			Texture *levelThumbs[overallLevel];
			Texture *levelLocals[overallLevel];
			TextureAnimation *levelDigitsTexture;
			
			
			std::vector<onAchievementsDelegate> achievementsDelegateList;
			std::vector<onPlayDelegate> playDelegateList;
			std::vector<onResearchDelegate>  researchDelegateList;
			
			int levelMoney[overallLevel];
			int levelEnemies[overallLevel];
			int levelAIs[overallLevel];
		
			int currentLevel;
			//const int maxLevel;
			void onAchievementsButtonReleased();
			void onResearchButtonReleased();
			void onPlayLevelSelected();
			
			void onLeft();
			void onRight();
			
			std::deque<int> levelDigits;
			std::deque<int> moneyDigits;
			std::deque<int> enemyDigits;
			std::deque<int> aiDigits;
			
			void refreshLevelDigits(std::deque<int> &digits, int value);
			void drawLevelPoints(int x,int y,std::deque<int> &digits);
			
		public:
			void addPlayButtonHandler(onPlayDelegate d);
			void addResearchButtonHandler(onResearchDelegate d);
			void addAchievementsButtonHandler(onAchievementsDelegate d);
			
			void handlePressEvent(int _x,int _y);
			void handleReleaseEvent(int _x,int _y);
			
			void fetchLevelInfoFromFile();
			
			void renew();
			
			void draw();
			
			static LevelSelectorScreen & getSingleton()
			{
				static LevelSelectorScreen obj;
				return obj;
			};
			
		};
	}
}

#endif