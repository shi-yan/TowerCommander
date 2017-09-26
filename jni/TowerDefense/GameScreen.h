/*
 *  GameScreen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __GameScreen__
#define __GameScreen__

#include "GlobalConfig.h"
#include "Screen.h"
#include "GameMap.h"
#include "EnemyFactory.h"
#include "MoneyBar.h"
#include "LifeBar.h"
#include "NextWaveBar.h"
#include "Tower.h"
#include "TowerFactory.h"
#include "GameButton.h"
#include "SmallAnimationManager.h"
#include "UpgradeMenu.h"
#include "QuitDialog.h"
#include "PlayerInfo.h"
namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		
		class GameScreen : public Screen
		{
		public:
			typedef fastdelegate::FastDelegate0<> onGameReturnDelegate;
			
		private:
			void saveStatistics(LevelAchievements & level);
			
			int mapid;
			int checkAchievements(LevelAchievements & level);
			std::vector<onGameReturnDelegate> gameReturnDelegateList;
			
			void onGameReturn()
			{
				
				for (std::vector<onGameReturnDelegate>::iterator iter=gameReturnDelegateList.begin(); iter!=gameReturnDelegateList.end(); ++iter) {
					(*iter)();
				}
			}
			
			enum InBuildingTowerType
			{
				TowerA,
				TowerB,
				TowerC,
				TowerD,
				NONE
			};
			
			int score;
			bool hasMoved;
			double pressedTime;
			bool isUpgrading;
			bool isMissionFailed;
			bool isVictory;
			int oldx;
			int oldy;
			
			GameButton *buildingmenubutton;
			GameButton *towerButtonA;
			GameButton *towerButtonB;
			GameButton *towerButtonC;
		//	GameButton *towerButtonD;
			
			QuitDialog *quitDialog;
			
			bool isMenuOpen;
			bool isInBuilding;
			
			Texture *towerAAvatar;
			Texture *towerBAvatar;
			Texture *towerCAvatar;
		//	Texture *towerDAvatar;
			
		//	TextureAnimation *cursorLarge;
		//	TextureAnimation *cursorSmall;
			
			enum InBuildingTowerType currentInBuildingType;
			int inBuildingX;
			int inBuildingY;
			int fullHealth;
			
			//int cursorX;
			//int cursorY;
			
			bool isQuiting;
			
			GameScreen();
			
			~GameScreen();
		public:
			
			void clearLevel();
			
		public:
			
			void initLevel(int mapid);
			void handlePressEvent(int _x,int _y);
			void handleReleaseEvent(int _x,int _y);
			void handleMoveEvent(int _x,int _y);
			void draw();
			void onGameLoop();
			static GameScreen & getSingleton()
			{
				static GameScreen  obj;
				return obj;
			};
			
			void addGameReturnHandler(onGameReturnDelegate d)
			{
				gameReturnDelegateList.push_back(d);
			};
			
		private:

			void onMenuButtonRelease()
			{
				currentInBuildingType=NONE;
				isMenuOpen=!isMenuOpen;
				inBuildingX=0;
				inBuildingY=0;
			}
			void buildATower(int x,int y);
			void onUpgradeMenuCancel();
			void onUpgradeMenuOK(int _x,int _y,int id);
			void onTowerButtonAPressed();
			void onTowerButtonBPressed();
			void onTowerButtonCPressed();
			void onTowerButtonDPressed();
			
			void upgradeATowerAt(int _x,int _y);
			
			void missionFailed();
			void victory();
			
			void onFailedDialogContinue();
			void onVictoryDialogContinue();
			
			void onQuitYes()
			{
				isQuiting=false;
				onGameReturn();
			};
			
			void onQuitNo()
			{
				isQuiting=false;
			};
			
			void onBack();
		};
	}
}


#endif