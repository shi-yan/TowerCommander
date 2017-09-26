/*
 *  AchievementsScreen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __AchievementsScreen__
#define __AchievementsScreen__

#include "Screen.h"
#include "TextureAnimation.h"
#include <deque>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class AchievementsScreen : public Screen 
		{
		private:
			int currentLevelID;
			
			Texture *background;
			Texture *cover;
			Texture *levelAchievements;
			Texture *gameAchievements;
			Texture *statistics;
			Texture *rightmark;
			TextureAnimation *digitsTexture;
			Texture *levelThumb;
			
			int offset;
			int overallLength;
			int oldx;
			int oldy;
			float acceleration;
			double oldtime;
			
			std::deque<int> gameEnemyKilled;
			std::deque<int> gameMoneyEarned;
			std::deque<int> gameMoneySpent;
			std::deque<int> gamePointsCollected;
			std::deque<int> gamePointsSpent;
			std::deque<int> gameTowerBuilt;
			std::deque<int> gameGameTimes;
			std::deque<int> gameDefeatTimes;
			
			std::deque<int> levelEnemiesKilled;
			std::deque<int> levelMoneyEarned;
			std::deque<int> levelMoneySpent;
			std::deque<int> levelGameTimes;
			std::deque<int> levelDefeatTimes;
			std::deque<int> levelTowerBuilt;
			
			void prepareDigits(int value,std::deque<int> & digits);
			void drawDigits(std::deque<int> & digits,int y);
			
		public:
			AchievementsScreen();
			~AchievementsScreen();
			
			static AchievementsScreen & getSingleton()
			{
				static AchievementsScreen obj;
				return obj;
			};
			
			void draw();
			
			void handlePressEvent(int x,int y)
			{
				oldx=x;
				oldy=y;
			};
			
			void renew(int levelid);
			void release();
			void handleMoveEvent(int x,int y);
		};
	}
}

#endif