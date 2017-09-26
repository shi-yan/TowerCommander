/*
 *  AchievementsScreen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "AchievementsScreen.h"
#include "TextureAtlasManager.h"

#include "QuadHelper.h"
#include "GameTimeManager.h"
#include "PlayerInfo.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		AchievementsScreen::AchievementsScreen():Screen(),acceleration(0),currentLevelID(0)
		{
			
			
			
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("achieve.png");
			int listAtlas=TextureAtlasManager::getSingleton().addNew("achievementlists.png");
			int listAtlas2=TextureAtlasManager::getSingleton().addNew("achievementlists2.png");
			
			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("levelthumbs.png");
#else
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/achieve.png");
			int listAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/achievementlists.png");
			
			int listAtlas2=TextureAtlasManager::getSingleton().addNew("../../../../assets/achievementlists2.png");
			
			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/levelthumbs.png");
#endif
			
			statistics=new Texture(listAtlas,1,1,419,544);
			levelAchievements=new Texture(listAtlas,422,1,419,813);
			gameAchievements=new Texture(listAtlas2,1,1,419,1018);
			rightmark=new Texture(atlas,800,0,19,20);
			background=new Texture(atlas,0,0,800,480);
			cover=new Texture(atlas,0,480,800,480);
			digitsTexture=new TextureAnimation(atlas,800,27,130,15,13,15);
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			digitsTexture->addAnimation(k,10);
			
			overallLength=statistics->height+levelAchievements->height+gameAchievements->height;
			offset=0;
			
			
			
			switch (currentLevelID) {
				case 0:
					levelThumb=new Texture(levelThumbsAtlas,1,1,198,193);
					
					break;
				case 1:
					levelThumb=new Texture(levelThumbsAtlas,201,1,198,193);
					
					break;
				case 2:
					levelThumb=new Texture(levelThumbsAtlas,401,1,198,193);
					break;
				default:
					break;
			}
		}
		
		AchievementsScreen::~AchievementsScreen()		
		{
			release();
		}
		
		void AchievementsScreen::release()
		{
			if (background) 
			{
				delete background;
				background=NULL;
			}
			if (cover) {
				delete cover;
				cover=NULL;
			}
			if (levelAchievements) {
				delete levelAchievements;
				levelAchievements=NULL;
			}
			if (gameAchievements) {
				delete gameAchievements;
				gameAchievements=NULL;
			}
			if (statistics) {
				delete statistics;
				statistics=NULL;
			}
			if (rightmark) {
				delete rightmark;
				rightmark=NULL;
			}
			if (digitsTexture) {
				delete digitsTexture;
				digitsTexture=NULL;
			}
			if (levelThumb) {
				delete levelThumb;
				levelThumb=NULL;
			}
		}
		
		void AchievementsScreen::drawDigits(std::deque<int> & digits,int y)
		{
			int digitx=560-digits.size()*13;
			
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) 
			{
				digitsTexture->setAnimationStep(*iter);
				digitsTexture->apply();
				
				QuadHelper::getSingleton().drawQuad(digitx,y,13,15,digitsTexture->getCoordinates());
				
				digitx+=13;
		
			};
			
			
		}
		
		void AchievementsScreen::prepareDigits(int value,std::deque<int> & digits)
		{
			(value=value>=0?value:0);
			
			digits.clear();
			while (value>9) 
			{
				int di=value%10;
				digits.push_front(di);
				value=(value-di)/10;
			}
			
			digits.push_front(value);
			
		}
		
		void AchievementsScreen::renew(int levelid)
		{
#ifdef __ANDROID__

			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("levelthumbs.png");
#else
		
			int levelThumbsAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/levelthumbs.png");
#endif
		
			currentLevelID=levelid;
			oldtime=GameTimeManager::getSingleton().getCurrentTime();
			

			
			
			prepareDigits(PlayerInfo::getSingleton().getEnemyKilled(),gameEnemyKilled);
			prepareDigits(PlayerInfo::getSingleton().getMoneyEarned(),gameMoneyEarned);
			prepareDigits(PlayerInfo::getSingleton().getMoneySpent(),gameMoneySpent);
			prepareDigits(PlayerInfo::getSingleton().getPointsCollected(),gamePointsCollected);
			prepareDigits(PlayerInfo::getSingleton().getPointsSpent(),gamePointsSpent);
			prepareDigits(PlayerInfo::getSingleton().getTowerBuilt(),gameTowerBuilt);
			prepareDigits(PlayerInfo::getSingleton().getGameTimes(),gameGameTimes);
			prepareDigits(PlayerInfo::getSingleton().getDefeatTimes(),gameDefeatTimes);
			
			//printf("game times:%d\n",PlayerInfo::getSingleton().getGameTimes());
			
			LevelAchievements & level=PlayerInfo::getSingleton().getLevelAchievements(levelid);
		//	int enemies1=level.getEnemiesKilled();
		//	level.addEnemiesKilled(100);
	
			prepareDigits(level.getEnemiesKilled(),levelEnemiesKilled);
			prepareDigits(level.getMoneyEarned(),levelMoneyEarned);
			prepareDigits(level.getMoneySpent(),levelMoneySpent);
			prepareDigits(level.getGameTimes(),levelGameTimes);
			prepareDigits(level.getDefeatTimes(),levelDefeatTimes);
			prepareDigits(level.getTowerBuilt(),levelTowerBuilt);
			
			
		//	int enemies2=PlayerInfo::getSingleton().getLevelAchievements(levelid).getEnemiesKilled();
		//	int enemies3=level.getEnemiesKilled();
			
			if (levelThumb) {
				delete levelThumb;
				levelThumb=NULL;
			}
			
			switch (currentLevelID) {
				case 0:
					levelThumb=new Texture(levelThumbsAtlas,1,1,198,193);
					
					break;
				case 1:
					levelThumb=new Texture(levelThumbsAtlas,201,1,198,193);
					
					break;
				case 2:
					levelThumb=new Texture(levelThumbsAtlas,401,1,198,193);
					break;
				default:
					break;
			}
		}
		
		void AchievementsScreen::draw()
		{
		
			double currentTime=GameTimeManager::getSingleton().getCurrentTime();
				
			while (currentTime-oldtime>0.05) 
			{
				offset+=acceleration;
					
				acceleration*=0.9f;
					
					
				if (offset<0) 
				{
					offset+=overallLength;
				}
				else
					if (offset>overallLength) 
					{
						offset-=overallLength;
					}
				oldtime+=0.05;
				
			}
			
			background->apply();
			QuadHelper::getSingleton().drawQuad(0,0,800,480,background->getCoordinates());
			LevelAchievements & level=PlayerInfo::getSingleton().getLevelAchievements(currentLevelID);
			
			int tempoffset=offset;
			if (!(tempoffset>480) && !(overallLength<0) ) 
			{
				
				levelAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144,levelAchievements->width,levelAchievements->height,levelAchievements->getCoordinates());
				
				gameAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height,gameAchievements->width,gameAchievements->height,gameAchievements->getCoordinates());
				
				statistics->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height+gameAchievements->height,statistics->width,statistics->height,statistics->getCoordinates());
			
			
				rightmark->apply();
				if(level.getCollect1000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect3000())
				{
					int i=1;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect5000())
				{
					int i=2;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill1000())
				{
					int i=3;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill2000())
				{
					int i=4;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill3000())
				{
					int i=5;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutGunTowers())
				{
					int i=6;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutCannons())
				{
					int i=7;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutLasers())
				{
					int i=8;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutSlowTowers())
				{
					int i=9;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutUpgrading())
				{
					int i=10;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithoutSelling())
				{
					int i=11;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave600WhenFinish())
				{
					int i=12;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave1000WhenFinish())
				{
					int i=13;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getSave2000WhenFinish())
				{
					int i=14;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithFullHealth())
				{
					int i=15;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithSingleHealth())
				{
					int i=16;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan40Towers())
				{
					int i=17;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan50Towers())
				{
					int i=18;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan60Towers())
				{
					int i=19;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan100Towers())
				{
					int i=20;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan120Towers())
				{
					int i=21;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished10Times())
				{
					int i=22;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished20Times())
				{
					int i=23;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished50Times())
				{
					int i=24;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
	
				
				if( PlayerInfo::getSingleton(). getCollect100000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect300000())
				{
					int i=1;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect500000())
				{
					int i=2;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill10000())
				{
					int i=3;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill50000())
				{
					int i=4;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill70000())
				{
					int i=5;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan600Towers())
				{
					int i=6;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1000Towers())
				{
					int i=7;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1200Towers())
				{
					int i=8;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish100Games())
				{
					int i=9;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish500Games())
				{
					int i=10;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish1000Games())
				{
					int i=11;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel1())
				{
					int i=12;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel2())
				{
					int i=13;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel3())
				{
					int i=14;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel4())
				{
					int i=15;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel5())
				{
					int i=16;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel6())
				{
					int i=17;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel7())
				{
					int i=18;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel8())
				{
					int i=19;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel9())
				{
					int i=20;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel10())
				{
					int i=21;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel11())
				{
					int i=22;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel12())
				{
					int i=23;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel13())
				{
					int i=24;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel14())
				{
					int i=25;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel15())
				{
					int i=26;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel16())
				{
					int i=27;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel17())
				{
					int i=28;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel18())
				{
					int i=29;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel19())
				{
					int i=30;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel20())
				{
					int i=31;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				
				
				int i=0;
				
				
				drawDigits(	levelEnemiesKilled,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits(	levelMoneyEarned,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits(	levelMoneySpent,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(	 levelGameTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(	 levelDefeatTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits(	levelTowerBuilt,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				
				i=0;
				drawDigits( gameEnemyKilled,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits( gameMoneyEarned,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits( gameMoneySpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(gamePointsCollected,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(gamePointsSpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits( gameTowerBuilt,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=6;
				drawDigits( gameGameTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=7;
				drawDigits( gameDefeatTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
			}
			
			
			tempoffset=offset-overallLength;
			
			if (!(tempoffset>480) && !(overallLength<0) ) 
			{
				
				levelAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144,levelAchievements->width,levelAchievements->height,levelAchievements->getCoordinates());
				
				gameAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height,gameAchievements->width,gameAchievements->height,gameAchievements->getCoordinates());
				
				statistics->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height+gameAchievements->height,statistics->width,statistics->height,statistics->getCoordinates());
			
			
				rightmark->apply();
				if(level.getCollect1000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect3000())
				{
					int i=1;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect5000())
				{
					int i=2;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill1000())
				{
					int i=3;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill2000())
				{
					int i=4;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill3000())
				{
					int i=5;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutGunTowers())
				{
					int i=6;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutCannons())
				{
					int i=7;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutLasers())
				{
					int i=8;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutSlowTowers())
				{
					int i=9;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutUpgrading())
				{
					int i=10;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithoutSelling())
				{
					int i=11;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave600WhenFinish())
				{
					int i=12;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave1000WhenFinish())
				{
					int i=13;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getSave2000WhenFinish())
				{
					int i=14;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithFullHealth())
				{
					int i=15;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithSingleHealth())
				{
					int i=16;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan40Towers())
				{
					int i=17;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan50Towers())
				{
					int i=18;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan60Towers())
				{
					int i=19;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan100Towers())
				{
					int i=20;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan120Towers())
				{
					int i=21;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished10Times())
				{
					int i=22;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished20Times())
				{
					int i=23;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished50Times())
				{
					int i=24;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				
				
				if( PlayerInfo::getSingleton(). getCollect100000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect300000())
				{
					int i=1;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect500000())
				{
					int i=2;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill10000())
				{
					int i=3;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
					
				if( PlayerInfo::getSingleton(). getKill50000())
				{
					int i=4;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill70000())
				{
					int i=5;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan600Towers())
				{
					int i=6;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1000Towers())
				{
					int i=7;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1200Towers())
				{
					int i=8;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish100Games())
				{
					int i=9;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish500Games())
				{
					int i=10;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish1000Games())
				{
					int i=11;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel1())
				{
					int i=12;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel2())
				{
					int i=13;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel3())
				{
					int i=14;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel4())
				{
					int i=15;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel5())
				{
					int i=16;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel6())
				{
					int i=17;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel7())
				{
					int i=18;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel8())
				{
					int i=19;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel9())
				{
					int i=20;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel10())
				{
					int i=21;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel11())
				{
					int i=22;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel12())
				{
					int i=23;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel13())
				{
					int i=24;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel14())
				{
					int i=25;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel15())
				{
					int i=26;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel16())
				{
					int i=27;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel17())
				{
					int i=28;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel18())
				{
					int i=29;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel19())
				{
					int i=30;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel20())
				{
					int i=31;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185+levelAchievements->height,19,20,rightmark->getCoordinates());
				};			
				
				int i=0;
				
				
				drawDigits(	levelEnemiesKilled,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits(	levelMoneyEarned,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits(	levelMoneySpent,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(	 levelGameTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(	 levelDefeatTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits(	levelTowerBuilt,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				
				i=0;
				drawDigits( gameEnemyKilled,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits( gameMoneyEarned,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits( gameMoneySpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(gamePointsCollected,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(gamePointsSpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits( gameTowerBuilt,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=6;
				drawDigits( gameGameTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=7;
				drawDigits( gameDefeatTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
			}
			
			tempoffset=offset+overallLength;
			
			if (!(tempoffset>480) && !(overallLength<0) ) 
			{
				
				levelAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144,levelAchievements->width,levelAchievements->height,levelAchievements->getCoordinates());
				
				gameAchievements->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height,gameAchievements->width,gameAchievements->height,gameAchievements->getCoordinates());
				
				statistics->apply();
				QuadHelper::getSingleton().drawQuad(172,tempoffset+144+levelAchievements->height+gameAchievements->height,statistics->width,statistics->height,statistics->getCoordinates());
			
				rightmark->apply();
				if(level.getCollect1000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect3000())
				{
					int i=1;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getCollect5000())
				{
					int i=2;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill1000())
				{
					int i=3;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill2000())
				{
					int i=4;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getKill3000())
				{
					int i=5;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutGunTowers())
				{
					int i=6;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutCannons())
				{
					int i=7;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutLasers())
				{
					int i=8;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutSlowTowers())
				{
					int i=9;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithoutUpgrading())
				{
					int i=10;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithoutSelling())
				{
					int i=11;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave600WhenFinish())
				{
					int i=12;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getSave1000WhenFinish())
				{
					int i=13;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getSave2000WhenFinish())
				{
					int i=14;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithFullHealth())
				{
					int i=15;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());				};
				
				if(level. getFinishWithSingleHealth())
				{
					int i=16;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan40Towers())
				{
					int i=17;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinishWithLessThan50Towers())
				{
					int i=18;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan60Towers())
				{
					int i=19;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan100Towers())
				{
					int i=20;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getBuildMoreThan120Towers())
				{
					int i=21;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished10Times())
				{
					int i=22;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished20Times())
				{
					int i=23;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if(level. getFinished50Times())
				{
					int i=24;
					
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect100000())
				{
					int i=0;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect300000())
				{
					int i=1;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCollect500000())
				{
					int i=2;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill10000())
				{
					int i=3;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill50000())
				{
					int i=4;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getKill70000())
				{
					int i=5;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan600Towers())
				{
					int i=6;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1000Towers())
				{
					int i=7;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getBuildMoreThan1200Towers())
				{
					int i=8;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish100Games())
				{
					int i=9;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish500Games())
				{
					int i=10;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getFinish1000Games())
				{
					int i=11;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel1())
				{
					int i=12;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel2())
				{
					int i=13;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel3())
				{
					int i=14;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel4())
				{
					int i=15;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel5())
				{
					int i=16;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel6())
				{
					int i=17;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel7())
				{
					int i=18;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel8())
				{
					int i=19;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel9())
				{
					int i=20;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel10())
				{
					int i=21;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel11())
				{
					int i=22;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel12())
				{
					int i=23;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel13())
				{
					int i=24;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel14())
				{
					int i=25;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel15())
				{
					int i=26;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel16())
				{
					int i=27;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel17())
				{
					int i=28;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel18())
				{
					int i=29;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				if( PlayerInfo::getSingleton(). getCompleteLevel19())
				{
					int i=30;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				if( PlayerInfo::getSingleton(). getCompleteLevel20())
				{
					int i=31;
					QuadHelper::getSingleton().drawQuad(540,30*i+tempoffset+185,19,20,rightmark->getCoordinates());
				};
				
				int i=0;
		
				
				drawDigits(	levelEnemiesKilled,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits(	levelMoneyEarned,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits(	levelMoneySpent,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(	 levelGameTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(	 levelDefeatTimes,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits(	levelTowerBuilt,30*i+tempoffset+185+levelAchievements->height+gameAchievements->height);
				
				i=0;
				drawDigits( gameEnemyKilled,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=1;
				drawDigits( gameMoneyEarned,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=2;
				drawDigits( gameMoneySpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=3;
				drawDigits(gamePointsCollected,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=4;
				drawDigits(gamePointsSpent,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=5;
				drawDigits( gameTowerBuilt,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=6;
				drawDigits( gameGameTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
				i=7;
				drawDigits( gameDefeatTimes,30*i+tempoffset+430+levelAchievements->height+gameAchievements->height);
			
			}
			
			cover->apply();
			QuadHelper::getSingleton().drawQuad(0,0,800,480,cover->getCoordinates());
			
			
			levelThumb->apply();
			QuadHelper::getSingleton().drawQuad(603,605-480,157,154,levelThumb->getCoordinates());
			
		}
		
		
		void AchievementsScreen::handleMoveEvent(int x,int y)
		{
			int xoffset=x-oldx;
			int yoffset=y-oldy;
			
			offset+=yoffset;
			
			if (offset<0) 
			{
				offset+=overallLength;
			}
			else
				if (offset>overallLength) 
				{
					offset-=overallLength;
				}
			
			
			acceleration+=yoffset*0.1f;
			
			oldx=x;
			oldy=y;
		}
	}
}