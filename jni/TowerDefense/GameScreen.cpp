/*
 *  GameScreen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "GameScreen.h"
#include "SmallAnimationManager.h"
#include "FailedDialog.h"
#include "WinDialog.h"
#include <cstdlib>
#include "PlayerInfo.h"
#include "CurrentLevelStatistics.h"

#ifdef __ANDROID__

#include "AndroidSoundManager.h"

#else

#include "QtSoundManager.h"

#endif

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		GameScreen::~GameScreen()
		{
			SmallAnimationManager::getSingleton().release();
			
			if (buildingmenubutton) 
				delete buildingmenubutton;
			
			if(towerButtonA)
				delete towerButtonA;
			if(towerButtonB)
				delete towerButtonB;
			if (towerButtonC) 
				delete towerButtonC;				

			if (towerAAvatar) 
				delete towerAAvatar;
			if (towerBAvatar) 
				delete towerBAvatar;
			if (towerCAvatar) 
				delete towerCAvatar;
	
			Enemy::releaseBloodTexture();
			
		};
		
		void GameScreen::draw()
		{
			onGameLoop();
			GameMap::getSingleton().draw();
			
			SmallAnimationManager::getSingleton().draw();
			
			MoneyBar::getSingleton().draw();
			LifeBar::getSingleton().draw();
			
			NextWaveBar::getSingleton().draw();
			
			if(!isInBuilding)
			{
				buildingmenubutton->draw();
				
				if (isMenuOpen) 
				{
					towerButtonA->draw();
					towerButtonB->draw();
					towerButtonC->draw();
					//towerButtonD->draw();
				}
				
				if(isUpgrading)
				{
					UpgradeMenu::getSingleton().draw();
				}
				else if(isMissionFailed) {
					FailedDialog::getSingleton().draw();
				}
				else if(isVictory)
				{

					WinDialog::getSingleton().draw();
				}
				else if(isQuiting)
				{
					quitDialog->draw();
				}

			}
			else 
			{
				
			/*	cursorLarge->apply();
				QuadHelper::getSingleton().drawQuad(inBuildingX+20,inBuildingY+30,100,100,cursorLarge->getCoordinates());
				cursorLarge->animate();
			*/	
				switch (currentInBuildingType) 
				{
					case TowerA:
			
						
						towerAAvatar->apply();
						QuadHelper::getSingleton().drawQuad(inBuildingX,inBuildingY,TowerWidth,TowerHeight,towerAAvatar->getCoordinates());
				
						break;
						
					case TowerB:
		
						
						towerBAvatar->apply();
						QuadHelper::getSingleton().drawQuad(inBuildingX,inBuildingY,TowerWidth,TowerHeight,towerBAvatar->getCoordinates());	
		
						break;
						
					case TowerC:
						
						towerCAvatar->apply();
						QuadHelper::getSingleton().drawQuad(inBuildingX,inBuildingY,TowerWidth,TowerHeight,towerCAvatar->getCoordinates());
			
						break;

						
					default:
						break;
				}
		
			}
		};
		
		void GameScreen::onUpgradeMenuCancel()
		{
			isUpgrading=false;
		}
		
		void GameScreen::onUpgradeMenuOK(int _x,int _y,int id)
		{
			isUpgrading=false;
			switch (id) 
			{
				case -1:
					GameMap::getSingleton().sellTower(_x,_y);
					CurrentLevelStatistics::getSingleton().finishWithoutSellingFailed();
					break;
				default:
					int cost=Tower::getTowerCost(id);
					if (MoneyBar::getSingleton().getMoney()<cost) 
					{
						SmallAnimationManager::getSingleton().addNotification(0);
					}
					else
					{
						MoneyBar::getSingleton().decreaseMoney(cost);
						CurrentLevelStatistics::getSingleton().addMoneySpent(cost);
						CurrentLevelStatistics::getSingleton().addTowerBuilt(1);
						GameMap::getSingleton().upgradeATowerAt(_x,_y,id);
						
						if (id==0 || id==1 || id==2 || id==12 || id==17) {
							CurrentLevelStatistics::getSingleton().finishWithoutGunTowersFailed();
						}
						else if(id == 3 || id ==5 || id==4 )
						{
							CurrentLevelStatistics::getSingleton().finishWithoutCannonsFailed();
						}
						/*else if(id==9 || id==14 || id==15)
						{
							CurrentLevelStatistics::getSingleton().finishWithoutFlameTowersFailed();
						}*/
						
						else if(id== 11 || id== 13||id== 19 || id==21)
						{
							CurrentLevelStatistics::getSingleton().finishWithoutLasersFailed();
						}
					/*	else if(id==6 || id==7 ||id==8) {
						
							CurrentLevelStatistics::getSingleton().finishWithoutMis
						}
					*/	
						else if(id==10||id== 16 ||id==18||id== 20)
						
						{
							CurrentLevelStatistics::getSingleton().finishWithoutSlowTowersFailed();
						}
						
						CurrentLevelStatistics::getSingleton().finishWithoutUpgradingFailed();

					}
					break;
			}
		}
			
		void GameScreen::initLevel(int _mapid)
		{
			CurrentLevelStatistics::getSingleton().clearAll();
			
		
			
			mapid=_mapid;
			isQuiting=false;
	
		
			
#ifdef __ANDROID__
			switch (mapid) {
				case 0:
					GameMap::getSingleton().loadFromFile("/sdcard/TowerCommander/exportedmap.map",800,480);
					break;
				case 1:
					GameMap::getSingleton().loadFromFile("/sdcard/TowerCommander/exportedmap2.map",800,480);
					break;
				case 2:
					GameMap::getSingleton().loadFromFile("/sdcard/TowerCommander/exportedmap3.map",800,480);
					break;
				default:
					break;
			}
#else
			
			switch (mapid) {
				case 0:
					GameMap::getSingleton().loadFromFile("../../../../assets/exportedmap.map",800,480);
					break;
				case 1:
					GameMap::getSingleton().loadFromFile("../../../../assets/exportedmap2.map",800,480);
					break;
				case 2:
					GameMap::getSingleton().loadFromFile("../../../../assets/exportedmap3.map",800,480);
					break;
				default:
					break;
			}
#endif
			
			//GameMap::getSingleton().loadFromFile("Saved.map",800,480);
			FILE *fp=NULL;
#ifdef __ANDROID__
			switch (mapid) {
				case 0:
					 fp=fopen("/sdcard/TowerCommander/level1.lev", "rb");
					break;
				case 1:
					fp=fopen("/sdcard/TowerCommander/level2.lev", "rb");
					break;
				case 2:
					fp=fopen("/sdcard/TowerCommander/level3.lev", "rb");
				default:
					break;
			}
#else
			
			switch (mapid) {
				case 0:
					fp=fopen("../../../../assets/level1.lev", "rb");
					break;
				case 1:
					fp=fopen("../../../../assets/level2.lev", "rb");
					break;
				case 2:
					fp=fopen("../../../../assets/level3.lev", "rb");
				default:
					break;
			}
			
#endif
			if (fp!=NULL) {
				
				int money=0;
				fread(&money, sizeof(int), 1, fp);
				
				MoneyBar::getSingleton().setMoney(money);
				
				fread(&score, sizeof(int), 1, fp);
				
					EnemyFactory::getSingleton().initWavesFromFile(fp);
				fullHealth=score;
				LifeBar::getSingleton().setLife(score);
			
			
			GameTimeManager::getSingleton().refreshCurrentTime();
				EnemyFactory::getSingleton().beginWave();
			
				fclose(fp);
			}
					}
		
		void GameScreen::onVictoryDialogContinue()
		{
			PlayerInfo::getSingleton().save();
			onGameReturn();
		}
		
		void GameScreen::onFailedDialogContinue()
		{
			PlayerInfo::getSingleton().save();
			onGameReturn();
		}
		
		void GameScreen::onTowerButtonAPressed()
		{
			isInBuilding=true;
			currentInBuildingType=TowerA;
		}
		
		void GameScreen::onTowerButtonBPressed()
		{
			isInBuilding=true;
			currentInBuildingType=TowerB;
		}
		
		void GameScreen::onTowerButtonCPressed()
		{
			isInBuilding=true;
			currentInBuildingType=TowerC;
		}
		
		void GameScreen::onTowerButtonDPressed()
		{
			isInBuilding=true;
			currentInBuildingType=TowerD;
		}
		
		void GameScreen::onGameLoop() 
		{
			
		//	LOGI("begine game loop");
			srand((unsigned int)GameTimeManager::getSingleton().getCurrentTime());
	
			if(!isMissionFailed && !isVictory)
			{
				bool hasSomeoneDied=false;
		
				int nextTime=EnemyFactory::getSingleton().queryForNextWaveTime();
	
				
				Enemy *e=EnemyFactory::getSingleton().querryForAnEnemy();
	
				if(e!=NULL)
				{
					std::vector<PointI> & startPoints=GameMap::getSingleton().getStartPoints();
					e->setPosition( startPoints[rand()%startPoints.size()]);
				
					e->findPath();
					GameMap::getSingleton().insertAnEnemy(e);	
					e->beginMove();
				}
	
				std::vector<Enemy*> & enpool=GameMap::getSingleton().getEnemyPool();
				
				for(std::vector<Enemy *>::iterator iter=enpool.begin();iter!=enpool.end();++iter)
				{
					bool isend=(*iter)->move();
					if(isend && (*iter)->isDead==false)
					{
						(*iter)->setDeath();
						score--;
						LifeBar::getSingleton().setLife(score);
						hasSomeoneDied=true;
					}
					else if((*iter)->isDead==true) 
					{
		
						hasSomeoneDied=true;
					}
					
				}
				
				GameMap::getSingleton().shotAtEnemies();
			
				if(hasSomeoneDied)
				{
					GameMap::getSingleton().removeDeadEnemy();
				}
				
				if (score<=0 ) 
				{
					missionFailed();
				}
				else 
				{
					if (EnemyFactory::getSingleton().isWaveOver() && GameMap::getSingleton().getEnemyPool().size()==0) 
					{
						victory();
					}
				}
				
				
				SoundManager::getSingleton().nowListen();

			}
			
		
		}

		void GameScreen::handlePressEvent(int _x,int _y)
		{
			oldx=_x;
			oldy=_y;
			
			if (isUpgrading) 
			{
				UpgradeMenu::getSingleton().handlePressEvent(_x,_y);
			}
			else if(isMissionFailed)
			{
				FailedDialog::getSingleton().handlePressEvent(_x,_y);
			}
			else if(isVictory)
			{
				WinDialog::getSingleton().handlePressEvent(_x,_y);
			}
			else if(isQuiting)
			{
				quitDialog->handlePressEvent(_x, _y);
			}
			else
			if(!isInBuilding)
			{
				
				if(buildingmenubutton->handlePressEvent(_x, _y))
				{
				
				}
				
				else if(isMenuOpen)
				{
					if(towerButtonA->handlePressEvent(_x, _y))
					{
					}
					else if(towerButtonB->handlePressEvent(_x, _y))
					{
					}
					else if(towerButtonC->handlePressEvent(_x, _y))
					{
					}
					else 
					{
						hasMoved=false;
						pressedTime=GameTimeManager::getSingleton().getCurrentTime();
					}
				}
				else
				{
					hasMoved=false;
					pressedTime=GameTimeManager::getSingleton().getCurrentTime();
				}
			}
		}
		
		void GameScreen::handleReleaseEvent(int _x,int _y)
		{
			oldx=-1;
			oldy=-1;
			
			if (isUpgrading) 
			{
				UpgradeMenu::getSingleton().handleReleaseEvent(_x,_y);
			}
			else if(isMissionFailed) {
				FailedDialog::getSingleton().handleReleaseEvent(_x,_y);
			}
			else if(isVictory)
			{
				WinDialog::getSingleton().handleReleaseEvent(_x,_y);
			}
			else if(isQuiting)
			{
			
				quitDialog->handleReleaseEvent(_x, _y);
			}

			else if (!isInBuilding) 
			{
				if(buildingmenubutton->handleReleaseEvent(_x, _y))
				{
				}
				else if(isMenuOpen)
				{
					if(towerButtonA->handleReleaseEvent(_x, _y))
					{
					}
					else if(towerButtonB->handleReleaseEvent(_x, _y))
					{
					}
					else if(towerButtonC->handleReleaseEvent(_x, _y))
					{
					}
					/*else if(towerButtonD->handleReleaseEvent(_x, _y))
					{
					}*/
					else 
					{
						double time=GameTimeManager::getSingleton().getCurrentTime();
							
						double duration=time-pressedTime;
							
						if (duration<1.8 && hasMoved==false) 
						{
							upgradeATowerAt(_x,_y);
						}
					}

				}
				else
				{
					double time=GameTimeManager::getSingleton().getCurrentTime();
					double duration=time-pressedTime;
					
					if (duration<1.8 && hasMoved==false) 
					{
						upgradeATowerAt(_x,_y);
					}
				}
			}
			else 
			{
				PointI mapoffset=GameMap::getSingleton().getMapOffset();
				
				int actualx=_x+mapoffset.x-53;
				int actualy=_y+mapoffset.y-53;
				
				if (actualx<0 || actualy<0) {
					
				}
				else
				{
				
					actualx/=TileSize;
					actualy/=TileSize;
				
					buildATower(actualx, actualy);
				}
				
				if(towerButtonA->handleReleaseEvent(_x, _y))
				{
				}
				else if(towerButtonB->handleReleaseEvent(_x, _y))
				{
				}
				else if(towerButtonC->handleReleaseEvent(_x, _y))
				{
				}
					
				else if(buildingmenubutton->handleReleaseEvent(_x, _y)){
					
				}

			}
		}
		
		void GameScreen::buildATower(int x,int y)
		{
			Tower *tower=NULL;
			int cost=0;
			switch (currentInBuildingType) 
			{
				case TowerA:
					cost=Tower::getTowerCost(0);
					
					if (MoneyBar::getSingleton().getMoney()<cost) 
					{
						SmallAnimationManager::getSingleton().addNotification(0);
					}
					else
					{
					
						tower=TowerFactory::getSingleton().getTower(x, y, 0);
						if(GameMap::getSingleton().insertATower(tower, x, y))
						{
							CurrentLevelStatistics::getSingleton().addTowerBuilt(1);
							CurrentLevelStatistics::getSingleton().countOnlyBuild();
							MoneyBar::getSingleton().decreaseMoney(cost);
							CurrentLevelStatistics::getSingleton().addMoneySpent(cost);
							CurrentLevelStatistics::getSingleton().finishWithoutGunTowersFailed();
						};
					}
					break;
					
				case TowerB:
					cost=Tower::getTowerCost(3);
					
					if (MoneyBar::getSingleton().getMoney()<cost) 
					{
						SmallAnimationManager::getSingleton().addNotification(0);
					}
					else
					{
						tower=TowerFactory::getSingleton().getTower(x, y, 3);
						
						if(GameMap::getSingleton().insertATower(tower, x, y))
						{
							
							CurrentLevelStatistics::getSingleton().addTowerBuilt(1);
							CurrentLevelStatistics::getSingleton().countOnlyBuild();
							MoneyBar::getSingleton().decreaseMoney(cost);
							CurrentLevelStatistics::getSingleton().addMoneySpent(cost);
							CurrentLevelStatistics::getSingleton().finishWithoutCannonsFailed();
						};
					}
					break;
					
				case TowerC:
					cost=Tower::getTowerCost(10);
					
					if (MoneyBar::getSingleton().getMoney()<cost) 
					{
						SmallAnimationManager::getSingleton().addNotification(0);
					}
					else
					{
						//MoneyBar::getSingleton().decreaseMoney(cost);
						tower=TowerFactory::getSingleton().getTower(x, y, 10);
						if(GameMap::getSingleton().insertATower(tower, x, y))
						{
							
							CurrentLevelStatistics::getSingleton().addTowerBuilt(1);
							CurrentLevelStatistics::getSingleton().countOnlyBuild();
							MoneyBar::getSingleton().decreaseMoney(cost);
							CurrentLevelStatistics::getSingleton().addMoneySpent(cost);
							CurrentLevelStatistics::getSingleton().finishWithoutSlowTowersFailed();
						};
					}
					break;
					
			/*	case TowerD:
					cost=Tower::getTowerCost(11);
					
					if (MoneyBar::getSingleton().getMoney()<cost) 
					{
						SmallAnimationManager::getSingleton().addNotification(0);
					}
					else
					{
						MoneyBar::getSingleton().decreaseMoney(cost);
						tower=TowerFactory::getSingleton().getTower(x, y, 11);
						GameMap::getSingleton().insertATower(tower, x, y);
					}
					break;*/
					
				default:
					break;
			}
			
			isInBuilding=false;
			inBuildingX=0;
			inBuildingY=0;
			currentInBuildingType=NONE;
			
			towerButtonA->setStatus(0);
			towerButtonB->setStatus(0);
			towerButtonC->setStatus(0);
		//	towerButtonD->setStatus(0);
		}
		
		
		void GameScreen::handleMoveEvent(int _x,int _y)
		{
			if (isUpgrading) 
			{
				UpgradeMenu::getSingleton().handleMoveEvent(_x,_y);
			}
			else
			{
				int offsetx=_x-oldx;
				int offsety=_y-oldy;
			
				if (offsetx>5 || offsety>5) 
				{
					hasMoved=true;
				}
			
				oldx=_x;
				oldy=_y;
			
				if (!isInBuilding && !buildingmenubutton->getIsPressed()) 
				{
					if(offsetx!=0 || offsety!=0)
					{
						GameMap::getSingleton().pan(-offsetx,-offsety);
					}
				}
				else
				{
					PointI mapoffset=GameMap::getSingleton().getMapOffset();
				
				
					
					int actualx=_x+mapoffset.x-53;
					int actualy=_y+mapoffset.y-53;
					
					if (actualx<0) {
					
						actualx=0;
					}
					
					if (actualy<0) {
											actualy=0;
					}
					
				
					
					actualx/=TileSize;
					actualy/=TileSize;
				
					inBuildingX=actualx*TileSize-mapoffset.x;
					inBuildingY=actualy*TileSize-(TowerHeight-TowerWidth)-mapoffset.y;
				//	cursorX=inBuildingX;
				//	cursorY=inBuildingY;
				}
			}
		}
		
		void GameScreen::saveStatistics(LevelAchievements & level)
		{
			
			PlayerInfo::getSingleton().addMoneyEarned(CurrentLevelStatistics::getSingleton().getMoneyEarned());
			level.addMoneyEarned(CurrentLevelStatistics::getSingleton().getMoneyEarned());
			
			PlayerInfo::getSingleton().addMoneySpent(CurrentLevelStatistics::getSingleton().getMoneySpent());
			level.addMoneySpent(CurrentLevelStatistics::getSingleton().getMoneySpent());
			
			PlayerInfo::getSingleton().addTowerBuilt(CurrentLevelStatistics::getSingleton().getTowerBuilt());
			level.addTowerBuilt(CurrentLevelStatistics::getSingleton().getTowerBuilt());
			
			PlayerInfo::getSingleton().addEnemyKilled(CurrentLevelStatistics::getSingleton().getEnemiesKilled());
			level.addEnemiesKilled(CurrentLevelStatistics::getSingleton().getEnemiesKilled());
		}
		
		void GameScreen::missionFailed()
		{
			PlayerInfo::getSingleton().addGameTimes(1);
			
			LevelAchievements & level=PlayerInfo::getSingleton().getLevelAchievements(mapid);
			
			level.addGameTimes(1);
			
			saveStatistics(level);
			
			isMissionFailed=true;
			
			
			
			int currentPoint=PlayerInfo::getSingleton().getPoints();
			int penalty=2*(EnemyFactory::getSingleton().howManyLeft()+GameMap::getSingleton().getEnemyPool().size())-MoneyBar::getSingleton().getMoney()*0.5;
			
			PlayerInfo::getSingleton().decreasePoints(penalty);
			
			FailedDialog::getSingleton().setupFailedDialog(currentPoint,currentPoint-penalty>0?currentPoint-penalty:0);
			FailedDialog::getSingleton().beginScrollingDown(200);
		}
		
		
		int GameScreen::checkAchievements(LevelAchievements & level)
		{
			int achieved=0;
			switch (mapid) {
				case 0:
					if(PlayerInfo::getSingleton().getCompleteLevel1()==false)
					{
						achieved++;
						PlayerInfo::getSingleton().completeLevel1Achieved();
					}
					break;
					
				case 1:
					if (PlayerInfo::getSingleton().getCompleteLevel2()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel2Achieved();
					}
					break;
					
				case 2:
					if(PlayerInfo::getSingleton().getCompleteLevel3()==false)
					{
						achieved++;
						PlayerInfo::getSingleton().completeLevel3Achieved();
					}
					break;
					case 3:
					if (PlayerInfo::getSingleton().getCompleteLevel4()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel4Achieved();
						}
						break;

				case 4:
					if (PlayerInfo::getSingleton().getCompleteLevel5()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel5Achieved();
						
					}
					break;
					
				case 5:
					if (PlayerInfo::getSingleton().getCompleteLevel6()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel6Achieved();
					}
					break;
					
				case 6:
					if (PlayerInfo::getSingleton().getCompleteLevel7()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel7Achieved();
					}
					break;
					
				case 7:
					if (PlayerInfo::getSingleton().getCompleteLevel8()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel8Achieved();
					}
					break;
					
				case 8:
					if (PlayerInfo::getSingleton().getCompleteLevel9()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel9Achieved();
					}
					break;
					
				case 9:
					if (PlayerInfo::getSingleton().getCompleteLevel10()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel10Achieved();
					}
					break;
					
				case 10:
					if (PlayerInfo::getSingleton().getCompleteLevel11()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel11Achieved();
						
					}
					break;
					
				case 11:
					if (PlayerInfo::getSingleton().getCompleteLevel12()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel12Achieved();
					}
					break;
				case 12:
					if (PlayerInfo::getSingleton().getCompleteLevel13()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel13Achieved();
					}
					break;
					
				case 13:
					if (PlayerInfo::getSingleton().getCompleteLevel14()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel14Achieved();
					}
					break;
					
				case 14:
					if (PlayerInfo::getSingleton().getCompleteLevel15()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel15Achieved();
					}
					break;
					
				case 15:
					if (PlayerInfo::getSingleton().getCompleteLevel16()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel16Achieved();
					}
					break;
					
				case 16:
					if(PlayerInfo::getSingleton().getCompleteLevel17()==false)
					{
						achieved++;
						PlayerInfo::getSingleton().completeLevel17Achieved();
					}
					break;
					
				case 17:
					if (PlayerInfo::getSingleton().getCompleteLevel18()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel18Achieved();
					}
					break;
					
				case 18:
					if (PlayerInfo::getSingleton().getCompleteLevel19()==false) {
						achieved++;
						PlayerInfo::getSingleton().completeLevel19Achieved();
					}
					break;
					
				case 19:
					if(PlayerInfo::getSingleton().getCompleteLevel20()==false)
					{
						achieved++;
						PlayerInfo::getSingleton().completeLevel20Achieved();
					}
					break;
					
					
				default:
					break;
			}
			
			if (!PlayerInfo::getSingleton().getCollect100000() && PlayerInfo::getSingleton().getMoneyEarned()>100000) {
				achieved++;
				PlayerInfo::getSingleton().collect100000Achieved();
			}
			
			if(!PlayerInfo::getSingleton().getCollect300000() && PlayerInfo::getSingleton().getMoneyEarned()>300000)
			{
				achieved++;
				PlayerInfo::getSingleton().collect300000Achieved();
			}
			
			if(!PlayerInfo::getSingleton().getCollect500000() && PlayerInfo::getSingleton().getMoneyEarned()>500000)
			{
				achieved++;
				PlayerInfo::getSingleton().collect500000Achieved();
			}
			
			if (!PlayerInfo::getSingleton().getKill10000()&& PlayerInfo::getSingleton().getEnemyKilled()>10000) {
				achieved++;
				PlayerInfo::getSingleton().kill10000Achieved();
			}
			if (!PlayerInfo::getSingleton().getKill50000()&& PlayerInfo::getSingleton().getEnemyKilled()>50000) {
				achieved++;
				PlayerInfo::getSingleton().kill50000Achieved();
			}
			if (!PlayerInfo::getSingleton().getKill70000()&& PlayerInfo::getSingleton().getEnemyKilled()>70000) {
				achieved++;
				PlayerInfo::getSingleton().kill70000Achieved();
			}
			
			if (!PlayerInfo::getSingleton().getBuildMoreThan600Towers()&& PlayerInfo::getSingleton().getTowerBuilt()>600) {
				achieved++;
				PlayerInfo::getSingleton().buildMoreThan600TowersAchieved();
			}
			if (!PlayerInfo::getSingleton().getBuildMoreThan1000Towers()&& PlayerInfo::getSingleton().getTowerBuilt()>1000) {
				achieved++;
				PlayerInfo::getSingleton().buildMoreThan1000TowersAchieved();
			}
			if (!PlayerInfo::getSingleton().getBuildMoreThan1200Towers()&& PlayerInfo::getSingleton().getTowerBuilt()>1200) {
				achieved++;
				PlayerInfo::getSingleton().buildMoreThan1200TowersAchieved();
			}
	
			if (!PlayerInfo::getSingleton().getFinish100Games()&& PlayerInfo::getSingleton().getGameTimes()>100) {
				achieved++;
				PlayerInfo::getSingleton().finish100GamesAchieved();
			}
			
			if (!PlayerInfo::getSingleton().getFinish500Games()&& PlayerInfo::getSingleton().getGameTimes()>500) {
				achieved++;
				PlayerInfo::getSingleton().finish500GamesAchieved();
			}
			
			if (!PlayerInfo::getSingleton().getFinish1000Games()&& PlayerInfo::getSingleton().getGameTimes()>1000) {
				achieved++;
				PlayerInfo::getSingleton().finish1000GamesAchieved();
			}
	
			//levelachievements
			
			if (!level.getCollect1000 ()&&level.getMoneyEarned()>1000) {
				achieved++;
				level.collect1000Achieved();
			}
			
			if (!level.getCollect3000 ()&&level.getMoneyEarned()>3000) {
				achieved++;
				level.collect3000Achieved();
			}
			
			if (!level.getCollect5000 ()&&level.getMoneyEarned()>5000) {
				achieved++;
				level.collect5000Achieved();
			}
			
			if (!level.getKill1000()&& level.getEnemiesKilled()>1000) {
				achieved++;
				level.kill1000Achieved();
			}
			
			if (!level.getKill2000()&& level.getEnemiesKilled()>2000) {
				achieved++;
				level.kill2000Achieved();
			}
			
			if (!level.getKill3000()&& level.getEnemiesKilled()>3000) {
				achieved++;
				level.kill3000Achieved();
			}
			
			if (!level.getSave600WhenFinish ()&&MoneyBar::getSingleton().getMoney()>600) {
				achieved++;
				level.save600WhenFinishAchieved();
			}
			
			if (!level.getSave1000WhenFinish()&& MoneyBar::getSingleton().getMoney()>1000) {
				achieved++;
				level.save1000WhenFinishAchieved();
			}
			
			if (!level.getSave2000WhenFinish()&& MoneyBar::getSingleton().getMoney()>2000) {
				achieved++;
				level.save2000WhenFinishAchieved();
			}
			
			
			if (!level.getFinishWithFullHealth ()&&fullHealth==score) {
				achieved++;
				level.finishWithFullHealthAchieved();
			} 
			
			if(!level.getFinishWithSingleHealth ()&& score==1)
			{
				achieved++;
				level.finishWithSingleHealthAchieved();
			}
		
			/////////////// 有问题
			if (!level.getFinishWithLessThan40Towers()&& CurrentLevelStatistics::getSingleton().getOnlyBuilt()<40) {
				achieved++;
				level.finishWithLessThan40TowersAchieved();
			}
			
			if (!level.getFinishWithLessThan50Towers()&& CurrentLevelStatistics::getSingleton().getOnlyBuilt()<50) {
				achieved++;
				level.finishWithLessThan50TowersAchieved();
			}
			
			
			if (!level.getBuildMoreThan60Towers()&& CurrentLevelStatistics::getSingleton().getTowerBuilt()>60) {
				achieved++;
				level.buildMoreThan60TowersAchieved();
			}
			
			if (!level.getBuildMoreThan100Towers()&& CurrentLevelStatistics::getSingleton().getTowerBuilt()>100) {
				achieved++;
				level.buildMoreThan100TowersAchieved();
			}
			
			if (!level.getBuildMoreThan120Towers()&& CurrentLevelStatistics::getSingleton().getTowerBuilt()>120) {
				achieved++;
				level.buildMoreThan120TowersAchieved();
			}
			
			if (!level.getFinished10Times()&& level.getDefeatTimes()>=10) {
				achieved++;
				level.finished10TimesAchieved();
			}
			
			if (!level.getFinished20Times ()&&level.getDefeatTimes()>=20) {
				achieved++;
				level.finished20TimesAchieved();
			}
			
			if (!level.getFinished50Times()&& level.getDefeatTimes()>=50) {
				achieved++;
				level.finished50TimesAchieved();
			}
			
			
		////////////////////这些都还没弄
			
			if(!level.getFinishWithoutGunTowers()&& CurrentLevelStatistics::getSingleton().getFinishWithoutGunTowers())
			{
				achieved++;
				level.finishWithoutGunTowersAchieved();
			};
			
			if(!level.getFinishWithoutCannons()&& CurrentLevelStatistics::getSingleton().getFinishWithoutCannons())
			{
				achieved++;
				level.finishWithoutCannonsAchieved();
			};
			
			if(!level.getFinishWithoutLasers()&& CurrentLevelStatistics::getSingleton().getFinishWithoutLasers())
			{
				achieved++;
				level.finishWithoutLasersAchieved();
			};
			
			if(!level.getFinishWithoutSlowTowers()&& CurrentLevelStatistics::getSingleton().getFinishWithoutSlowTowers())
			{
				achieved++;
				level.finishWithoutSlowTowersAchieved();
			};
			
			if(!level.getFinishWithoutUpgrading()&& CurrentLevelStatistics::getSingleton().getFinishWithoutUpgrading())
			{
				achieved++;
				level.finishWithoutUpgradingAchieved();
			};
			
			if(!level.getFinishWithoutSelling()&& CurrentLevelStatistics::getSingleton().getFinishWithoutSelling())
			{
				achieved++;
				level.finishWithoutSellingAchieved();
			};
				
		
			
			
			
			return achieved;
			
		}
		
		void GameScreen::victory()
		{
			PlayerInfo::getSingleton().addGameTimes(1);
			PlayerInfo::getSingleton().addDefeatTimes(1);
			
			LevelAchievements & level=PlayerInfo::getSingleton().getLevelAchievements(mapid);
			
			level.addGameTimes(1);
			level.addDefeatTimes(1);
			
			saveStatistics(level);
	
			
			isVictory=true;
			
			int currentPoint=PlayerInfo::getSingleton().getPoints();
			int achievemesnts=checkAchievements(level);
			int bonus=MoneyBar::getSingleton().getMoney()*0.5+score*10+achievemesnts*20;
			
			PlayerInfo::getSingleton().addPoints(bonus);
			
			PlayerInfo::getSingleton().addPointsCollected(bonus);
			PlayerInfo::getSingleton().setCurrentLevel(mapid);
			
			
			
			WinDialog::getSingleton().setWinDialog(currentPoint,currentPoint+bonus,achievemesnts);
			WinDialog::getSingleton().beginScrollingDown(200);
			
			
			
		}
		
		
		void GameScreen::upgradeATowerAt(int _x,int _y)
		{
			PointI offset=GameMap::getSingleton().getMapOffset();
			
			int px=(int)((_x+offset.x)/((float)TileSize));
			int py=(int)((_y+offset.y)/((float)TileSize));
			
			Tower *toBeUpdated=GameMap::getSingleton().getTowerAt(px,py);
			
			if (toBeUpdated!=NULL) 
			{
				UpgradeMenu::getSingleton().setupUpgradeMenu(toBeUpdated,px,py);
				isUpgrading=true;
				UpgradeMenu::getSingleton().beginScrollingDown(400);
			}
		}
		
	
		 GameScreen::GameScreen()
		:Screen(),
		score(0),
		hasMoved(false), 
		pressedTime(0.0),
		isUpgrading(false),isMissionFailed(false),isVictory(false),
		oldx(0),
		oldy(0),
		buildingmenubutton(NULL),
		towerButtonA(NULL),
		towerButtonB(NULL),
		towerButtonC(NULL),
		//	towerButtonD(NULL),
		isMenuOpen(false),
		isInBuilding(false),
		towerAAvatar(NULL),
		towerBAvatar(NULL),
		towerCAvatar(NULL),
		//	towerDAvatar(NULL),
		// cursorX(0),
		// cursorY(0),
		currentInBuildingType(NONE),
		inBuildingX(0),
		inBuildingY(0),
		isQuiting(false),
		quitDialog(NULL)
		{
			
			Enemy::setBloodTexture();
			UpgradeMenu::getSingleton().init();
			
			UpgradeMenu::onCancelDelegate umcd;
			umcd.bind(this,&GameScreen::onUpgradeMenuCancel);
			UpgradeMenu::getSingleton().addOnCancelHandler(umcd);
			
			UpgradeMenu::onOkDelegate umod;
			umod.bind(this,&GameScreen::onUpgradeMenuOK);
			UpgradeMenu::getSingleton().addOnOkHandler(umod);
			
			SmallAnimationManager::getSingleton().init();
			
		
			
#ifdef	__ANDROID__
			
			int uiat=TextureAtlasManager::getSingleton().addNew("ui.png");
			int towerButtonAtlas=TextureAtlasManager::getSingleton().addNew("ui.png");
			int atlasAtlas=TextureAtlasManager::getSingleton().addNew("tower.png");
			//int cursorAtlas=TextureAtlasManager::getSingleton().addNew("cursor.png");
#else
			
			int uiat=TextureAtlasManager::getSingleton().addNew("../../../../assets/ui.png");
			int towerButtonAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/ui3.png");
			int atlasAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/tower.png");
			//int cursorAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/cursor.png");
#endif
			
			TowerFactory::getSingleton().init();
			MoneyBar::getSingleton().init(uiat);
			LifeBar::getSingleton().init(uiat);
			NextWaveBar::getSingleton().init(uiat);
			LifeBar::getSingleton().setLife(score);
			
	/*		cursorLarge=new TextureAnimation(cursorAtlas,0,0,400,300,100,100);
			int k[12]={0,1,2,3,4,5,6,7,8,9,10,11};
			cursorLarge->addAnimation(k,12);
			
			cursorSmall=new TextureAnimation(cursorAtlas,0,310,300,100,50,50);
			cursorSmall->addAnimation(k,12);
	*/		
			//	srand(GameTimeManager::getSingleton().getCurrentTime());
			/*	for (int i=0; i<60; ++i) 
			 {
			 
			 
			 Tower *tower=TowerFactory::getSingleton().getTower(rand()%20, rand()%10+2, 21);
			 GameMap::getSingleton().insertATower(tower, rand()%20, rand()%10+2);
			 }
			 */
			
			
			
			
			
			
		//	Texture *normal=new Texture(towerButtonAtlas,233,0,80,80);
		//	Texture *pressed=new Texture(towerButtonAtlas,233,0,80,80);
			
			Texture *pressed=new Texture(towerButtonAtlas,323,0,59,60);
			Texture *normal=new Texture(towerButtonAtlas,323+59,0,59,60);
			
			buildingmenubutton=new GameButton();
			buildingmenubutton->setTexture(normal,pressed);
			buildingmenubutton->setPosition(800-50,430);
			buildingmenubutton->setSize(59, 60);
			
			towerButtonA=new GameButton();
			towerButtonB=new GameButton();
			towerButtonC=new GameButton();
			//towerButtonD=new GameButton();
			
		//	normal=new Texture(towerButtonAtlas,386,174,80,80);
		//	pressed=new Texture(towerButtonAtlas,386,176,80,80);
			
			pressed=new Texture(towerButtonAtlas,323,60,59,60);
			normal=new Texture(towerButtonAtlas,323+59,60,59,60);
			towerButtonA->setTexture(normal,pressed);
			towerButtonA->setPosition(800-320, 430);
			towerButtonA->setSize(59, 60);
			
		//	normal=new Texture(towerButtonAtlas,313,0,80,80);
		//	pressed=new Texture	(towerButtonAtlas,313,0,80,80);
			 pressed=new Texture(towerButtonAtlas,323,120,59,60);
			 normal=new Texture(towerButtonAtlas,323+59,120,59,60);
			towerButtonB->setTexture(normal, pressed);
			towerButtonB->setPosition(800-230, 430);
			towerButtonB->setSize(59, 60);
			
		//	normal	=new Texture(towerButtonAtlas,393,0,80,80);
		//	pressed=new Texture	(towerButtonAtlas,393,0,80,80);
			 pressed=new Texture(towerButtonAtlas,323,180,59,60);
			 normal=new Texture(towerButtonAtlas,323+59,180,59,60);
			towerButtonC->setTexture(normal, pressed);
			towerButtonC->setPosition(800-140, 430);
			towerButtonC->setSize(59, 60);
			
			//normal =new Texture(towerButtonAtlas,368,120,46,53);
			//pressed=new Texture(towerButtonAtlas,414,120,46,53);
			//towerButtonD->setTexture(normal, pressed);
			//towerButtonD->setPosition(385, 420);
			
			HotSpot::onReleaseDelegate omd;
			omd.bind(this,&GameScreen::onMenuButtonRelease);
			buildingmenubutton->addOnReleaseHandler(omd);
			
			HotSpot::onPressDelegate tbap;
			tbap.bind(this,&GameScreen::onTowerButtonAPressed);
			towerButtonA->addOnPressHandler(tbap);
			
			HotSpot::onPressDelegate tbbp;
			tbbp.bind(this,&GameScreen::onTowerButtonBPressed);
			towerButtonB->addOnPressHandler(tbbp);
			
			HotSpot::onPressDelegate tbcp;
			tbcp.bind(this,&GameScreen::onTowerButtonCPressed);
			towerButtonC->addOnPressHandler(tbcp);
			
			/*	HotSpot::onPressDelegate tbdp;
			 tbdp.bind(this,&GameScreen::onTowerButtonDPressed);
			 towerButtonD->addOnPressHandler(tbdp);
			 */	
			
			
			towerAAvatar=new Texture(atlasAtlas,40,0,40,60);
			towerBAvatar=new Texture(atlasAtlas,40,180,40,60);
			towerCAvatar=new Texture(atlasAtlas,120,600,40,60);
			//	towerDAvatar=new Texture(atlasAtlas,40,660,40,60);
			
			
			
			FailedDialog::onContinueDelegate focd;
			focd.bind(this,&GameScreen::onFailedDialogContinue);
			FailedDialog::getSingleton().addOnContinueHandler(focd);
			
			
			WinDialog::onContinueDelegate vocd;
			vocd.bind(this,&GameScreen::onVictoryDialogContinue);
			WinDialog::getSingleton().addOnContinueHandler(vocd);
			
			quitDialog=new QuitDialog();
			
			QuitDialog::onYesDelegate qyd;
			qyd.bind(this,&GameScreen::onQuitYes);
			quitDialog->addOnYesHandler(qyd);
			
			QuitDialog::onNoDelegate qnd;
			qnd.bind(this,&GameScreen::onQuitNo);
			quitDialog->addOnNoHandler(qnd);
			
			
			
			
			Screen::onBackDelegate obd;
			obd.bind(this,&GameScreen::onBack);
			addBackEventHandler(obd);
			
		}
		
		void GameScreen::onBack()
		{
			
			if(isUpgrading==true)
				isUpgrading=false;
			else if(!isVictory && !isMissionFailed)
			{
				isQuiting=true;
				quitDialog->beginScrollingDown(200);
			}
		}
		
		void GameScreen::clearLevel()
		{
			if(!GameMap::getSingleton().isMapEmpty()){
				score=(0);
				hasMoved=(false); 
				pressedTime=(0.0);
				isUpgrading=(false);
				isMissionFailed=(false);
				isVictory=(false);
				oldx=(0);
				oldy=(0);
				isMenuOpen=(false);
				isInBuilding=(false);
				currentInBuildingType=(NONE);
				inBuildingX=(0);
				inBuildingY=(0);
				
				GameMap::getSingleton().clearMap();
				EnemyFactory::getSingleton().clear();
			}
		};
	}
}