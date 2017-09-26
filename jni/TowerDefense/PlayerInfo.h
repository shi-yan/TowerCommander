/*
 *  PlayerInfo.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/23/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __PlayerInfo__
#define __PlayerInfo__

#include "GlobalConfig.h"
#include <iostream>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class LevelAchievements
		{
		private:
			bool collect1000;
			bool collect3000;
			bool collect5000;
			bool kill1000;
			bool kill2000;
			bool kill3000;
			bool finishWithoutGunTowers;
			bool finishWithoutCannons;
			bool finishWithoutLasers;
			bool finishWithoutSlowTowers;
			bool finishWithoutUpgrading;
			bool finishWithoutSelling;
			bool save600WhenFinish;
			bool save1000WhenFinish;
			bool save2000WhenFinish;
			bool finishWithFullHealth;
			bool finishWithSingleHealth;
			bool finishWithLessThan40Towers;
			bool finishWithLessThan50Towers;
			bool buildMoreThan60Towers;
			bool buildMoreThan100Towers;
			bool buildMoreThan120Towers;
			bool finished10Times;
			bool finished20Times;
			bool finished50Times;
			
			int enemiesKilled;
			int moneyEarned;
			int moneySpent;
			int gameTimes;
			int defeatTimes;
			int towerBuilt;
			
		public:
			
			LevelAchievements()
			:collect1000(false) ,
			 collect3000(false),
			 collect5000(false),
			 kill1000(false),
			 kill2000(false),
			 kill3000(false),
			 finishWithoutGunTowers(false),
			 finishWithoutCannons(false),
			 finishWithoutLasers(false),
			 finishWithoutSlowTowers(false),
			 finishWithoutUpgrading(false),
			 finishWithoutSelling(false),
			 save600WhenFinish(false),
			 save1000WhenFinish(false),
			 save2000WhenFinish(false),
			 finishWithFullHealth(false),
			 finishWithSingleHealth(false),
			 finishWithLessThan40Towers(false),
			 finishWithLessThan50Towers(false),
			 buildMoreThan60Towers(false),
			 buildMoreThan100Towers(false),
			 buildMoreThan120Towers(false),
			 finished10Times(false),
			 finished20Times(false),
			 finished50Times(false),
			
			 enemiesKilled(0),
			 moneyEarned(0),
			 moneySpent(0),
			 gameTimes(0),
			 defeatTimes(0),
			 towerBuilt(0)
			{};
			~LevelAchievements(){};
		public:
			void save(FILE *fp);
			void loadFromFile(FILE *fp,int lasize,int lssize);
			
			void saveSingleRecord(const char* name,bool value,FILE *fp);
			void saveSingleRecord(const char* name,int value,FILE *fp);
			
			int getEnemiesKilled()
			{
				return enemiesKilled;
			};
			int getMoneyEarned()
			{
				return moneyEarned;
			};
			int getMoneySpent()
			{
				return moneySpent;
			};
			int getGameTimes()
			{
				return gameTimes;
			};
			int getDefeatTimes()
			{
				return defeatTimes;
			};
			int getTowerBuilt()
			{
				return towerBuilt;
			};
			
			bool getCollect1000()
			{
				return collect1000;
			};
			
			bool getCollect3000()
			{
				return collect3000;
			};
			
			bool getCollect5000()
			{
				return collect5000;
			};
			
			bool getKill1000()
			{
				return kill1000;
			};
			
			bool getKill2000()
			{
				return kill2000;
			};
			
			bool getKill3000()
			{
				return kill3000;
			};
			
			bool getFinishWithoutGunTowers()
			{
				return finishWithoutGunTowers;
			};
			
			bool getFinishWithoutCannons()
			{
				return finishWithoutCannons;
			};
			
			bool getFinishWithoutLasers()
			{
				return finishWithoutLasers;
			};
			
			bool getFinishWithoutSlowTowers()
			{
				return finishWithoutSlowTowers;
			};
			
			bool getFinishWithoutUpgrading()
			{
				return finishWithoutUpgrading;
			};
			
			bool getFinishWithoutSelling()
			{
				return finishWithoutSelling;
			};
			
			bool getSave600WhenFinish()
			{
				return save600WhenFinish;
			};
			
			bool getSave1000WhenFinish()
			{
				return save1000WhenFinish;
			};
			
			bool getSave2000WhenFinish()
			{
				return save2000WhenFinish;
			};
			
			bool getFinishWithFullHealth()
			{
				return finishWithFullHealth;
			};
			
			bool getFinishWithSingleHealth()
			{
				return finishWithSingleHealth;
			};
			
			bool getFinishWithLessThan40Towers()
			{
				return finishWithLessThan40Towers;
			};
			
			bool getFinishWithLessThan50Towers()
			{
				return finishWithLessThan50Towers;
			};
			
			bool getBuildMoreThan60Towers()
			{
				return buildMoreThan60Towers;
			};
			
			bool getBuildMoreThan100Towers()
			{
				return buildMoreThan100Towers;
			};
			
			bool getBuildMoreThan120Towers()
			{
				return buildMoreThan120Towers;
			};
			
			bool getFinished10Times()
			{
				return finished10Times;
			};
			
			bool getFinished20Times()
			{
				return finished20Times;
			};
			
			bool getFinished50Times()
			{
				return finished50Times;
			};
			
			
			
			
			void collect1000Achieved()
			{
				collect1000=true;
			};
			
			void collect3000Achieved()
			{
				collect3000=true;
			};
			
			void collect5000Achieved()
			{
				collect5000=true;
			};
		
			void kill1000Achieved()
			{
				kill1000=true;
			};
			
			void kill2000Achieved()
			{
				kill2000=true;
			};
			
			void kill3000Achieved()
			{
				kill3000=true;
			};
			
			void finishWithoutGunTowersAchieved()
			{
				finishWithoutGunTowers=true;
			};
			
			void finishWithoutCannonsAchieved()
			{
				finishWithoutCannons=true;
			};
			
			void finishWithoutLasersAchieved()
			{
				finishWithoutLasers=true;
			};
			
			void finishWithoutSlowTowersAchieved()
			{
				finishWithoutSlowTowers=true;
			};
			
			void finishWithoutUpgradingAchieved()
			{
				finishWithoutUpgrading=true;
			};
			
			void finishWithoutSellingAchieved()
			{
				finishWithoutSelling=true;
			};
			
			void save600WhenFinishAchieved()
			{
				save600WhenFinish=true;
			};
			
			void save1000WhenFinishAchieved()
			{
				save1000WhenFinish=true;
			};
			
			void save2000WhenFinishAchieved()
			{
				save2000WhenFinish=true;
			};
			
			void finishWithFullHealthAchieved()
			{
				finishWithFullHealth=true;
			};
			
			void finishWithSingleHealthAchieved()
			{
				finishWithSingleHealth=true;
			};
			
			void finishWithLessThan40TowersAchieved()
			{
				finishWithLessThan40Towers=true;
			};
			
			void finishWithLessThan50TowersAchieved()
			{
				finishWithLessThan50Towers=true;
			};
			
			void buildMoreThan60TowersAchieved()
			{
				buildMoreThan60Towers=true;
			};
			
			void buildMoreThan100TowersAchieved()
			{
				buildMoreThan100Towers=true;
			};
			
			void buildMoreThan120TowersAchieved()
			{
				buildMoreThan120Towers=true;
			};
			
			void finished10TimesAchieved()
			{
				finished10Times=true;
			};
			
			void finished20TimesAchieved()
			{
				finished20Times=true;
			};
			
			void finished50TimesAchieved()
			{
				finished50Times=true;
			};
			
			
			void addEnemiesKilled(int value)
			{
				enemiesKilled+=value;
			};
			
			void addMoneyEarned(int value)
			{
				moneyEarned+=value;
			};
			
			void addMoneySpent(int value)
			{
				moneySpent+=value;
			};
			
			void addGameTimes(int value)
			{
				gameTimes+=value;
			};
			
			void addDefeatTimes(int value)
			{
				defeatTimes+=value;
			};
			
			void addTowerBuilt(int value)
			{
				towerBuilt+=value;
			};
			
			
			
		};
		
		class PlayerInfo  
		{
		private:
			int currentLevel;
			int points;
			
			int enemyKilled;
			int moneyEarned;
			int moneySpent;
			int pointsCollected;
			int pointsSpent;
			int towerBuilt;
			int gameTimes;
			int defeatTimes;
			
			bool tower0Available;
			bool tower1Available;
			bool tower2Available;
			bool tower3Available;
			bool tower4Available;
			bool tower5Available;
			bool tower6Available;
			bool tower7Available;
			bool tower8Available;
			bool tower9Available;
			bool tower10Available;
			bool tower11Available;
			bool tower12Available;
			bool tower13Available;
			bool tower14Available;
			bool tower15Available;
			bool tower16Available;
			bool tower17Available;
			bool tower18Available;
			bool tower19Available;
			bool tower20Available;
			bool tower21Available;

			
		
			LevelAchievements levels[overallLevel];
			
			bool collect100000;
			bool collect300000;
			bool collect500000;
			bool kill10000;
			bool kill50000;
			bool kill70000;
			bool buildMoreThan600Towers;
			bool buildMoreThan1000Towers;
			bool buildMoreThan1200Towers;
			bool finish100Games;
			bool finish500Games;
			bool finish1000Games;
			bool completeLevel1;
			bool completeLevel2;
			bool completeLevel3;
			bool completeLevel4;
			bool completeLevel5;
			bool completeLevel6;
			bool completeLevel7;
			bool completeLevel8;
			bool completeLevel9;
			bool completeLevel10;
			bool completeLevel11;
			bool completeLevel12;
			bool completeLevel13;
			bool completeLevel14;
			bool completeLevel15;
			bool completeLevel16;
			bool completeLevel17;
			bool completeLevel18;
			bool completeLevel19;
			bool completeLevel20;
			
			
			
			
			PlayerInfo():
			 tower0Available(true),
			 tower1Available(true),
			 tower2Available(false),
			 tower3Available(true),
			 tower4Available(false),
			 tower5Available(true),
			 tower6Available(false),
			 tower7Available(false),
			 tower8Available(false),
			 tower9Available(false),
			 tower10Available(true),
			 tower11Available(false),
			 tower12Available(false),
			 tower13Available(false),
			 tower14Available(false),
			 tower15Available(false),
			 tower16Available(false),
			 tower17Available(false),
			 tower18Available(false),
			 tower19Available(false),
			 tower20Available(false),
			 tower21Available(false),
			 collect100000(false),
			 collect300000(false),
			 collect500000(false),
			 kill10000(false),
			 kill50000(false),
			 kill70000(false),
			 buildMoreThan600Towers(false),
			 buildMoreThan1000Towers(false),
			 buildMoreThan1200Towers(false),
			 finish100Games(false),
			 finish500Games(false),
			 finish1000Games(false),
			 completeLevel1(false),
			 completeLevel2(false),
			 completeLevel3(false),
			 completeLevel4(false),
			 completeLevel5(false),
			 completeLevel6(false),
			 completeLevel7(false),
			 completeLevel8(false),
			 completeLevel9(false),
			 completeLevel10(false),
			 completeLevel11(false),
			 completeLevel12(false),
			 completeLevel13(false),
			 completeLevel14(false),
			 completeLevel15(false),
			 completeLevel16(false),
			 completeLevel17(false),
			 completeLevel18(false),
			 completeLevel19(false),
			 completeLevel20(false),
			 currentLevel(0),
			 points(1000),
			 enemyKilled(0),
			 moneyEarned(0),
			 moneySpent(0),
			 pointsCollected(0),
			 pointsSpent(0),
			 towerBuilt(0),
			 gameTimes(0),
			 defeatTimes(0)
			{};
			
			~PlayerInfo(){};
			
			void saveSingleRecord(const char* name,bool value,FILE *fp);
			void saveSingleRecord(const char* name,int value,FILE *fp);
			
		public:
			static PlayerInfo & getSingleton()
			{
				static PlayerInfo obj;
				return obj;
			};
			
			LevelAchievements & getLevelAchievements(int id)
			{
				return levels[id];
			};
			
			void save();
			
			void loadFromFile();
		
			int getCurrentLevel()
			{
				return currentLevel;
			};
			
			void decreasePoints(int _point)
			{
				points-=_point;
				if (points<0) {
					points=0;
				}
			};
			
			int getPoints()
			{
				return points;
			};
			
			int getEnemyKilled()
			{
				return enemyKilled;
			};
			
			int getMoneyEarned()
			{
				return moneyEarned;
			};
			
			int getMoneySpent()
			{
				return moneySpent;
			};

			int getPointsCollected()
			{
				return pointsCollected;
			};

			int getPointsSpent()
			{
				return pointsSpent;
			};
			
			int getTowerBuilt()
			{
				return towerBuilt;
			};
			
			int getGameTimes()
			{
				return gameTimes;
			};
			
			int getDefeatTimes()
			{
				return defeatTimes;
			};
		
			bool getCollect100000()
			{
				return collect100000;
			};
			
			bool getCollect300000()
			{
				return collect300000;
			};
			
			bool getCollect500000()
			{
				return collect500000;
			};
			
			bool getKill10000()
			{
				return kill10000;
			};
			
			bool getKill50000()
			{
				return kill50000;
			};
			
			bool getKill70000()
			{
				return kill70000;
			};
			
			bool getBuildMoreThan600Towers()
			{
				return buildMoreThan600Towers;
			};
			
			bool getBuildMoreThan1000Towers()
			{
				return buildMoreThan1000Towers;
			};
			
			bool getBuildMoreThan1200Towers()
			{
				return buildMoreThan1200Towers;
			};
			
			bool getFinish100Games()
			{
				return finish100Games;
			};
			
			bool getFinish500Games()
			{
				return finish500Games;
			};
			
			bool getFinish1000Games()
			{
				return finish1000Games;
			};
			
			bool getCompleteLevel1()
			{
				return completeLevel1;
			};
			
			bool getCompleteLevel2()
			{
				return completeLevel2;
			};
			
			bool getCompleteLevel3()
			{
				return completeLevel3;
			};
			
			bool getCompleteLevel4()
			{
				return completeLevel5;
			};
			
			bool getCompleteLevel5()
			{
				return completeLevel6;
			};
			
			bool getCompleteLevel6()
			{
				return completeLevel6;
			};
			
			bool getCompleteLevel7()
			{
				return completeLevel7;
			};
			
			bool getCompleteLevel8()
			{
				return completeLevel8;
			};
			
			bool getCompleteLevel9()
			{
				return completeLevel9;
			};
			
			bool getCompleteLevel10()
			{
				return completeLevel10;
			};
			bool getCompleteLevel11()
			{
				return completeLevel11;
			};
			bool getCompleteLevel12()
			{
				return completeLevel12;
			};
			bool getCompleteLevel13()
			{
				return completeLevel13;
			};
			bool getCompleteLevel14()
			{
				return completeLevel14;
			};
			bool getCompleteLevel15()
			{
				return completeLevel15;
			};
			bool getCompleteLevel16()
			{
				return completeLevel16;
			};
			bool getCompleteLevel17()
			{
				return completeLevel17;
			};
			
			bool getCompleteLevel18()
			{
				return completeLevel18;
			};
			
			bool getCompleteLevel19()
			{
				return completeLevel19;
			};
			bool getCompleteLevel20()
			{
				return completeLevel20;
			};
		
			
			void setCurrentLevel(int value)
			{
				if (currentLevel<=value) 
				{
					currentLevel=value+1;
					if (currentLevel>overallLevel-1) 
					{
						currentLevel=overallLevel-1;
					}
				}
				
			};
			
			void addPoints(int value)
			{
				points+=value;
			};
			
			void addEnemyKilled(int value)
			{
				enemyKilled+=value;
			};
			void addMoneyEarned(int value)
			{
				moneyEarned+=value;
			};
			void addMoneySpent(int value)
			{
				moneySpent+=value;
			};
			void addPointsCollected(int value)
			{
				pointsCollected+=value;
			};
			void addPointsSpent(int value)
			{
				pointsSpent+=value;
			};
			void addTowerBuilt(int value)
			{
				towerBuilt+=value;
			};
			void addGameTimes(int value)
			{
				gameTimes+=value;
			};
			void addDefeatTimes(int value)
			{
				defeatTimes+=value;
			};
			
			void collect100000Achieved()
			{
				collect100000=true;
			};
			void collect300000Achieved()
			{
				collect300000=true;
			};
			void collect500000Achieved()
			{
				collect500000=true;
			};
			void kill10000Achieved()
			{
				kill10000=true;
			};
			void kill50000Achieved()
			{
				kill50000=true;
			};
			void kill70000Achieved()
			{
				kill70000=true;
			};
			void buildMoreThan600TowersAchieved()
			{
				buildMoreThan600Towers=true;
			};
			void buildMoreThan1000TowersAchieved()
			{
				buildMoreThan1000Towers=true;
			};
			void buildMoreThan1200TowersAchieved()
			{
				buildMoreThan1200Towers=true;
			};
			void finish100GamesAchieved()
			{
				finish100Games=true;
			};
			void finish500GamesAchieved()
			{
				finish500Games=true;
			};
			void finish1000GamesAchieved()
			{
				finish1000Games=true;
			};
			void completeLevel1Achieved()
			{
				completeLevel1=true;
			};
			void completeLevel2Achieved()
			{
				completeLevel2=true;
			};
			void completeLevel3Achieved()
			{
				completeLevel3=true;
			};
			void completeLevel4Achieved()
			{
				completeLevel4=true;
			};
			void completeLevel5Achieved()
			{
				completeLevel5=true;
			};
			void completeLevel6Achieved()
			{
				completeLevel6=true;
			};
			void completeLevel7Achieved()
			{
				completeLevel7=true;
			};
			void completeLevel8Achieved()
			{
				completeLevel8=true;
			};
			void completeLevel9Achieved()
			{
				completeLevel9=true;
			};
			void completeLevel10Achieved()
			
			{
				completeLevel10=true;
			};
			void completeLevel11Achieved()
			{
				completeLevel11=true;
			};
			void completeLevel12Achieved()
			{
				completeLevel12=true;
			};
			void completeLevel13Achieved()
			{
				completeLevel13=true;
			};
			void completeLevel14Achieved()
			{
				completeLevel14=true;
			};
			void completeLevel15Achieved()
			{
				completeLevel15=true;
			};
			void completeLevel16Achieved()
			{
				completeLevel16=true;
			};
			void completeLevel17Achieved()
			{
				completeLevel17=true;
			};
			void completeLevel18Achieved()
			{
				completeLevel18=true;
			};
			void completeLevel19Achieved()
			{
				completeLevel19=true;
			};
			void completeLevel20Achieved()
			{
				completeLevel20=true;
			};
			
			void setTowerPurchased(int id)
			{
				switch (id) {
					case 0:
						 tower0Available=true;
						break;
					case 1:
						 tower1Available=true;
						break;
					case 2:
						 tower2Available=true;
						break;
					case 3:
						 tower3Available=true;
						break;
					case 4:
						 tower4Available=true;
						break;
					case 5:
						 tower5Available=true;
						break;
					case 6:
						 tower6Available=true;
						break;
					case 7:
						 tower7Available=true;
						break;
					case 8:
						 tower8Available=true;
						break;
					case 9:
						 tower9Available=true;
						break;
					case 10:
						 tower10Available=true;
						break;
					case 11:
						 tower11Available=true;
						break;
					case 12:
						 tower12Available=true;
						break;
					case 13:
						 tower13Available=true;
						break;
					case 14:
						 tower14Available=true;
						break;
					case 15:
						 tower15Available=true;
						break;
					case 16:
						 tower16Available=true;
						break;
					case 17:
						 tower17Available=true;
						break;
					case 18:
						 tower18Available=true;
						break;
					case 19:
						 tower19Available=true;
						break;
					case 20:
						 tower20Available=true;
						break;
					case 21:
						 tower21Available=true;
						break;
					default:
						break;
				}
			};
			
			bool getTowerAvailable(int id)
			{
				switch (id) {
					case 0:
						return tower0Available;
						break;
					case 1:
						return tower1Available;
						break;
					case 2:
						return tower2Available;
						break;
					case 3:
						return tower3Available;
						break;
					case 4:
						return tower4Available;
						break;
					case 5:
						return tower5Available;
						break;
					case 6:
						return tower6Available;
						break;
					case 7:
						return tower7Available;
						break;
					case 8:
						return tower8Available;
						break;
					case 9:
						return tower9Available;
						break;
					case 10:
						return tower10Available;
						break;
					case 11:
						return tower11Available;
						break;
					case 12:
						return tower12Available;
						break;
					case 13:
						return tower13Available;
						break;
					case 14:
						return tower14Available;
						break;
					case 15:
						return tower15Available;
						break;
					case 16:
						return tower16Available;
						break;
					case 17:
						return tower17Available;
						break;
					case 18:
						return tower18Available;
						break;
					case 19:
						return tower19Available;
						break;
					case 20:
						return tower20Available;
						break;
					case 21:
						return tower21Available;
						break;
					default:
						break;
				}
			};			
			
		};
	}
}

#endif