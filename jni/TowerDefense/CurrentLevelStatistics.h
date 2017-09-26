/*
 *  CurrentLevelStatistics.h
 *  towerdefense
 *
 *  Created by Shi Yan on 12/4/10.
 *  Copyright 2010 Animal Crackers Games. All rights reserved.
 *
 */

namespace AnimalCrackers
{
	namespace TowerDefense {
		class CurrentLevelStatistics
		{
		private:
			int enemiesKilled;
			int moneyEarned;
			int moneySpent;
			int towerBuilt;
			
			bool finishWithoutGunTowers;
			bool finishWithoutCannons;
			bool finishWithoutLasers;
			bool finishWithoutSlowTowers;
			bool finishWithoutUpgrading;
			bool finishWithoutSelling;
			
			CurrentLevelStatistics():enemiesKilled(0),moneyEarned(0),moneySpent(0),towerBuilt(0){};
			~CurrentLevelStatistics(){};
			
			int onlyBuilt;
			
		public:
			static CurrentLevelStatistics & getSingleton()
			{
				static CurrentLevelStatistics obj;
				return obj;
			};
			
			void clearAll()
			{
				 enemiesKilled=0;
				 moneyEarned=0;
				 moneySpent=0;
				 towerBuilt=0;
				 onlyBuilt=0;
				
				 finishWithoutGunTowers=true;
				 finishWithoutCannons=true;
				 finishWithoutLasers=true;
				 finishWithoutSlowTowers=true;
				 finishWithoutUpgrading=true;
				 finishWithoutSelling=true;
			};
			
			void countOnlyBuild()
			{
				onlyBuilt++;
			};
			
			bool getOnlyBuilt()
			{
				return onlyBuilt;
			};
			
			void finishWithoutGunTowersFailed()
			{
				finishWithoutGunTowers=false;
			};
			
			void finishWithoutCannonsFailed()
			{
				finishWithoutCannons=false;
			};
				
			void finishWithoutLasersFailed()
			{
				finishWithoutLasers=false;
			};
			
			void finishWithoutSlowTowersFailed()
			{
				finishWithoutSlowTowers=false;
			};
			
			void finishWithoutUpgradingFailed()
			{
				finishWithoutUpgrading=false;
			};
			
			void finishWithoutSellingFailed()
			{
				finishWithoutSelling=false;
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
			
		
			
			void addMoneySpent(int value)
			{
				moneySpent+=value;
			};
			
			void addMoneyEarned(int value)
			{
				moneyEarned+=value;
			};
			
			int getMoneyEarned()
			{
				return moneyEarned;
			};
			
			int getMoneySpent()
			{
				return moneySpent;
			};
			
			void addEnemiesKilled(int value)
			{
				enemiesKilled+=value;
			};
			
			int getEnemiesKilled()
			{
				return enemiesKilled;
			};
			
			void addTowerBuilt(int value){
				towerBuilt+=value;
			};
			
			int getTowerBuilt()
			{
				return towerBuilt;
			};
			
		};
	}
}