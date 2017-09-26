/*
 *  PlayerInfo.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/23/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "PlayerInfo.h"
#include <string>
#include <cmath>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		void LevelAchievements::save(FILE *fp)
		{
			saveSingleRecord("collect1000",collect1000,fp);
			saveSingleRecord("collect3000",collect3000,fp);
			saveSingleRecord("collect5000",collect5000,fp);
			saveSingleRecord("kill1000",kill1000,fp);
			saveSingleRecord("kill2000",kill2000,fp);
			saveSingleRecord("kill3000",kill3000,fp);
			saveSingleRecord("finishWithoutGunTowers",finishWithoutGunTowers,fp);
			saveSingleRecord("finishWithoutCannons",finishWithoutCannons,fp);
			saveSingleRecord("finishWithoutLaser",finishWithoutLasers,fp);
			saveSingleRecord("finishWithoutSlowTowers",finishWithoutSlowTowers,fp);
			saveSingleRecord("finishWithoutUpgrading",finishWithoutUpgrading,fp);
			saveSingleRecord("finishWithoutSelling",finishWithoutSelling,fp);
			saveSingleRecord("save600WhenFinish",save600WhenFinish,fp);
			saveSingleRecord("save1000WhenFinish",save1000WhenFinish,fp);
			saveSingleRecord("save2000WhenFinish",save2000WhenFinish,fp);
			saveSingleRecord("finishWithFullHealth",finishWithFullHealth,fp);
			saveSingleRecord("finishWithSingleHealth",finishWithSingleHealth,fp);
			saveSingleRecord("finishWithLessThan40Towers",finishWithLessThan40Towers,fp);
			saveSingleRecord("finishWithLessThan50Towers",finishWithLessThan50Towers,fp);
			saveSingleRecord("buildMoreThan60Towers",buildMoreThan60Towers,fp);
			saveSingleRecord("buildMoreThan100Towers",buildMoreThan100Towers,fp);
			saveSingleRecord("buildMoreThan120Towers",buildMoreThan120Towers,fp);
			saveSingleRecord("finished10Times",finished10Times,fp);
			saveSingleRecord("finished20Times",finished20Times,fp);
			saveSingleRecord("finished50Times",finished50Times,fp);	
			saveSingleRecord("enemiesKilled",enemiesKilled,fp);
			saveSingleRecord("moneyEarned",moneyEarned,fp);
			saveSingleRecord("moneySpent",moneySpent,fp);
			saveSingleRecord("gameTimes",gameTimes,fp);
			saveSingleRecord("defeatTimes",defeatTimes,fp);
			saveSingleRecord("towerBuilt",towerBuilt,fp);
		}
		
		void LevelAchievements::loadFromFile(FILE *fp,int lasize,int lssize)
		{
			for(int i=0;i<lasize;++i)
			{
			
				int stringlen=0;
				fread(&stringlen, sizeof(int), 1, fp);
				char *name=new char[stringlen+1];
				fread(name, sizeof(char), stringlen, fp);
				name[stringlen]='\0';
				
				if (strcmp(name,"collect1000")==0) 
				{
					fread(&collect1000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "collect3000")==0) 
				{
					fread(&collect3000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "collect5000")==0) 
				{
					fread(&collect5000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "kill1000")==0) 
				{
					fread(&kill1000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "kill2000")==0) 
				{
					fread(&kill2000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "kill3000")==0) 
				{
					fread(&kill3000, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutGunTowers")==0) 
				{
					fread(&finishWithoutGunTowers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutCannons")==0) 
				{
					fread(&finishWithoutCannons, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutLasers")==0) 
				{
					fread(&finishWithoutLasers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutSlowTowers")==0) 
				{
					fread(&finishWithoutSlowTowers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutUpgrading")==0)
				{
					fread(&finishWithoutUpgrading, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithoutSelling")==0) 
				{
					fread(&finishWithoutSelling, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "save600WhenFinish")==0) 
				{
					fread(&save600WhenFinish, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "save1000WhenFinish")==0) 
				{
					fread(&save1000WhenFinish, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "save2000WhenFinish")==0) 
				{
					fread(&save2000WhenFinish, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithFullHealth")==0) 
				{
					fread(&finishWithFullHealth, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithSingleHealth")==0) 
				{
					fread(&finishWithSingleHealth, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithLessThan40Towers")==0)
				{
					fread(&finishWithLessThan40Towers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finishWithLessThan50Towers")==0) 
				{
					fread(&finishWithLessThan50Towers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "buildMoreThan60Towers")==0) 
				{
					fread(&buildMoreThan60Towers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "buildMoreThan100Towers")==0) 
				{
					fread(&buildMoreThan100Towers, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "buildMoreThan120Towers")==0) 
				{
					fread(&buildMoreThan120Towers,sizeof(bool),1,fp);
				}
				else if (strcmp(name, "finished10Times")==0) 
				{
					fread(&finished10Times, sizeof(bool), 1, fp);
				}
				else if (strcmp(name, "finished20Times")==0) 
				{
					fread(&finished20Times,sizeof(bool),1,fp);
				}
				else if (strcmp(name, "finished50Times")==0)
				{
					fread(&finished50Times, sizeof(bool), 1, fp);
				}
				else 
				{
					bool temp=false;
					fread(&temp, sizeof(bool), 1, fp);
				}

				delete [] name;
			}
			
			for (int i=0; i<lssize; ++i) {
				
				int stringlen=0;
				fread(&stringlen, sizeof(int), 1, fp);
				char *name=new char[stringlen+1];
				fread(name, sizeof(char), stringlen, fp);
				name[stringlen]='\0';
				 if (strcmp(name,  "enemiesKilled")==0)
				{
					fread(&enemiesKilled, sizeof(int), 1, fp);
				}
				else if (strcmp(name,  "moneyEarned")==0)
				{
					fread(&moneyEarned, sizeof(int), 1, fp);
				}
				else if (strcmp(name,  "moneySpent")==0)
				{
					fread(&moneySpent, sizeof(int), 1, fp);
				}
				else if (strcmp(name,  "gameTimes")==0)
				{
					fread(&gameTimes, sizeof(int), 1, fp);
				}
				else if (strcmp(name,  "defeatTimes")==0)
				{
					fread(&defeatTimes, sizeof(int), 1, fp);
				}
				else if (strcmp(name,  "towerBuilt")==0)
				{
					fread(&towerBuilt, sizeof(int), 1, fp);
				}
				else
				{
					int temp=0;
					fread(&temp,sizeof(int),1,fp);
				}
				
				delete [] name;
			}
			
		}
		
		void LevelAchievements::saveSingleRecord(const char* name,bool value,FILE *fp)
		{
			int stringlen=strlen(name);
			fwrite(&stringlen, sizeof(int), 1, fp);
			fwrite(name, strlen(name), sizeof(char), fp);
			fwrite(&value, sizeof(bool), 1, fp);
		}
		
		void LevelAchievements::saveSingleRecord(const char* name,int value,FILE *fp)
		{
			int stringlen=strlen(name);
			fwrite(&stringlen, sizeof(int), 1, fp);
			fwrite(name, strlen(name), sizeof(char), fp);
			fwrite(&value, sizeof(int), 1, fp);
		}
		
		void PlayerInfo::saveSingleRecord(const char* name,bool value,FILE *fp)
		{
			int stringlen=strlen(name);
			fwrite(&stringlen, sizeof(int), 1, fp);
			fwrite(name, strlen(name), sizeof(char), fp);
			fwrite(&value, sizeof(bool), 1, fp);
		}
		
		void PlayerInfo::saveSingleRecord(const char* name,int value,FILE *fp)
		{
			int stringlen=strlen(name);
			fwrite(&stringlen, sizeof(int), 1, fp);
			fwrite(name, strlen(name), sizeof(char), fp);
			fwrite(&value, sizeof(int), 1, fp);
		}
		
		void PlayerInfo::save()
		{
			
#ifdef __ANDROID__
			FILE *fp=fopen("/sdcard/TowerCommander/player.dsav", "wb");
#else
			FILE *fp=fopen("../../res/player.dsav","wb");
#endif
			fwrite(&version, sizeof(float), 1, fp);
			fwrite(&overallLevel, sizeof(int), 1, fp);
			fwrite(&currentLevel, sizeof(int),1 , fp);
			fwrite(&points, sizeof(int), 1, fp);
			fwrite(&levelAchievementSize, sizeof(int), 1, fp);
			fwrite(&levelStatisticsSize,sizeof(int),1,fp);
			fwrite(&gameAchievementSize, sizeof(int), 1, fp);
			fwrite(&gameStatisticsSize,sizeof(int),1,fp);
			fwrite(&gameTowerCount, sizeof(int), 1, fp);
			
			
			saveSingleRecord("tower0Available", tower0Available, fp);
			saveSingleRecord("tower1Available", tower1Available, fp);
			saveSingleRecord("tower2Available", tower2Available, fp);
			saveSingleRecord("tower3Available", tower3Available, fp);
			saveSingleRecord("tower4Available", tower4Available, fp);
			saveSingleRecord("tower5Available", tower5Available, fp);
			saveSingleRecord("tower6Available", tower6Available, fp);
			saveSingleRecord("tower7Available", tower7Available, fp);
			saveSingleRecord("tower8Available", tower8Available, fp);
			saveSingleRecord("tower9Available", tower9Available, fp);
			saveSingleRecord("tower10Available", tower10Available, fp);
			saveSingleRecord("tower11Available", tower11Available, fp);
			saveSingleRecord("tower12Available", tower12Available, fp);
			saveSingleRecord("tower13Available", tower13Available, fp);
			saveSingleRecord("tower14Available", tower14Available, fp);
			saveSingleRecord("tower15Available", tower15Available, fp);
			saveSingleRecord("tower16Available", tower16Available, fp);
			saveSingleRecord("tower17Available", tower17Available, fp);
			saveSingleRecord("tower18Available", tower18Available, fp);
			saveSingleRecord("tower19Available", tower19Available, fp);
			saveSingleRecord("tower20Available", tower20Available, fp);
			saveSingleRecord("tower21Available", tower21Available, fp);
			
			
			saveSingleRecord("enemyKilled", enemyKilled, fp);
			saveSingleRecord("moneyEarned", moneyEarned, fp);
			saveSingleRecord("moneySpent", moneySpent, fp);
			saveSingleRecord("pointsCollected", pointsCollected, fp);
			saveSingleRecord("pointsSpent",pointsSpent,fp);
			saveSingleRecord("towerBuilt", towerBuilt, fp);
			saveSingleRecord("gameTimes", gameTimes, fp);
			saveSingleRecord("defeatTimes", defeatTimes, fp);
			
			
	
			saveSingleRecord("collect100000", collect100000, fp);
			saveSingleRecord("collect300000", collect300000, fp);
			saveSingleRecord("collect500000", collect500000, fp);
			saveSingleRecord("kill10000", kill10000, fp);
			saveSingleRecord("kill50000", kill50000, fp);
			saveSingleRecord("kill70000",kill70000,fp);
			saveSingleRecord("buildMoreThan600Towers", buildMoreThan600Towers, fp);
			saveSingleRecord("buildMoreThan1000Towers", buildMoreThan1000Towers, fp);
			saveSingleRecord("buildMoreThan1200Towers", buildMoreThan1200Towers, fp);
			saveSingleRecord("finish100Games", finish100Games, fp);
			saveSingleRecord("finish500Games", finish500Games, fp);
			saveSingleRecord("finish1000Games", finish1000Games, fp);
			saveSingleRecord("completeLevel1", completeLevel1, fp);
			saveSingleRecord("completeLevel2", completeLevel2, fp);
			saveSingleRecord("completeLevel3", completeLevel3, fp);
			saveSingleRecord("completeLevel4", completeLevel4, fp);
			saveSingleRecord("completeLevel5", completeLevel5, fp);
			saveSingleRecord("completeLevel6", completeLevel6, fp);
			saveSingleRecord("completeLevel7", completeLevel7, fp);
			saveSingleRecord("completeLevel8", completeLevel8, fp);
			saveSingleRecord("completeLevel9", completeLevel9, fp);
			saveSingleRecord("completeLevel10", completeLevel10, fp);
			saveSingleRecord("completeLevel11", completeLevel11, fp);
			saveSingleRecord("completeLevel12", completeLevel12, fp);
			saveSingleRecord("completeLevel13", completeLevel13, fp);
			saveSingleRecord("completeLevel14", completeLevel14, fp);
			saveSingleRecord("completeLevel15", completeLevel15, fp);
			saveSingleRecord("completeLevel16", completeLevel16, fp	);	
			saveSingleRecord("completeLevel17", completeLevel17, fp);			
			saveSingleRecord("completeLevel18", completeLevel18, fp);			
			saveSingleRecord("completeLevel19",completeLevel19,fp);
			saveSingleRecord("completeLevel20", completeLevel20, fp);
			
			for (int i=0; i<overallLevel; ++i) 
			{
				levels[i].save(fp);
			}
			
			
			fclose(fp);
			
		};
		
		void PlayerInfo::loadFromFile()
		{
#ifdef __ANDROID__
			FILE *fp=fopen("/sdcard/TowerCommander/player.dsav", "rb");
#else
			FILE *fp=fopen("../../res/player.dsav","rb");
#endif
			if (fp==0) {
				save();
				return;
			}
			
			float fileVersion=0.0f;
			int fileOverallLevel=0;
			int fileLevelAchievementSize=0;
			int fileLevelStatisticsSize=0;
			int fileGameAchievementSize=0;
			int fileGameStatisticsSize=0;
			int fileGameTowerCount=0;
			
			fread(&fileVersion, sizeof(float), 1, fp);
			fread(&fileOverallLevel, sizeof(int), 1, fp);
			fread(&currentLevel, sizeof(int),1 , fp);
			fread(&points, sizeof(int), 1, fp);
			fread(&fileLevelAchievementSize, sizeof(int), 1, fp);
			fread(&fileLevelStatisticsSize,sizeof(int),1,fp);
			fread(&fileGameAchievementSize, sizeof(int), 1, fp);
			fread(&fileGameStatisticsSize,sizeof(int),1,fp);
			fread(&fileGameTowerCount, sizeof(int), 1, fp);
			
			
			for (int i=0; i<fileGameTowerCount; ++i) 
			{
				int stringlen=0;
				fread(&stringlen, sizeof(int), 1, fp);
				char *name=new char[stringlen+1];
				fread(name, sizeof(char), stringlen, fp);
				name[stringlen]='\0';
				
				if (strcmp(name, "tower0Available")) {
					fread(&tower0Available, sizeof(bool), 1, fp);
				}
				else
					if (strcmp(name, "tower1Available")) {
						fread(&tower1Available, sizeof(bool), 1, fp);
					}
					else
						if (strcmp(name, "tower2Available")) {
							fread(&tower2Available, sizeof(bool), 1, fp);
						}
						else
							if (strcmp(name, "tower3Available")) {
								fread(&tower3Available, sizeof(bool), 1, fp);
							}
							else
								if (strcmp(name, "tower4Available")) {
									fread(&tower4Available, sizeof(bool), 1, fp);
								}
								else
									if (strcmp(name, "tower5Available")) {
										fread(&tower5Available, sizeof(bool), 1, fp);
									}
									else
										if (strcmp(name, "tower6Available")) {
											fread(&tower6Available, sizeof(bool), 1, fp);
										}
										else
											if (strcmp(name, "tower7Available")) {
												fread(&tower7Available, sizeof(bool), 1, fp);
											}
											else
												if (strcmp(name, "tower8Available")) {
													fread(&tower8Available, sizeof(bool), 1, fp);
												}
												else
													if (strcmp(name, "tower9Available")) {
														fread(&tower9Available, sizeof(bool), 1, fp);
													}
													else
														if (strcmp(name, "tower10Available")) {
															fread(&tower10Available, sizeof(bool), 1, fp);
														}
														else
															if (strcmp(name, "tower11Available")) {
																fread(&tower11Available, sizeof(bool), 1, fp);
															}
															else
																if (strcmp(name, "tower12Available")) {
																	fread(&tower12Available, sizeof(bool), 1, fp);
																}
																else
																	if (strcmp(name, "tower13Available")) {
																		fread(&tower13Available, sizeof(bool), 1, fp);
																	}
																	else
																		if (strcmp(name, "tower14Available")) {
																			fread(&tower14Available, sizeof(bool), 1, fp);
																		}
																		else
																			if (strcmp(name, "tower15Available")) {
																				fread(&tower15Available, sizeof(bool), 1, fp);
																			}
																			else
																				if (strcmp(name, "tower16Available")) {
																					fread(&tower16Available, sizeof(bool), 1, fp);
																				}
																				else
																					if (strcmp(name, "tower17Available")) {
																						fread(&tower17Available, sizeof(bool), 1, fp);
																					}
																					else
																						if (strcmp(name, "tower18Available")) {
																							fread(&tower18Available, sizeof(bool), 1, fp);
																						}
																						else
																							if (strcmp(name, "tower19Available")) {
																								fread(&tower19Available, sizeof(bool), 1, fp);
																							}
																							else
																								if (strcmp(name, "tower20Available")) {
																									fread(&tower20Available, sizeof(bool), 1, fp);
																								}
																								else
																									if (strcmp(name, "tower21Available")) {
																										fread(&tower21Available, sizeof(bool), 1, fp);
																									}
																									
				delete [] name;
			}
			
			for (int i=0; i<fileGameStatisticsSize; ++i) {
				int stringlen=0;
				fread(&stringlen, sizeof(int), 1, fp);
				char *name=new char[stringlen+1];
				fread(name, sizeof(char), stringlen, fp);
				name[stringlen]='\0';
				
				
				
				if (strcmp(name, "enemyKilled")==0)
				{
					fread(&enemyKilled, sizeof(int), 1, fp);
				}else
					if (strcmp(name, "moneyEarned")==0)
					{
						
						fread(&moneyEarned, sizeof(int), 1, fp);
					}else
						if (strcmp(name, "moneySpent")==0)
						{
							
							fread(&moneySpent, sizeof(int), 1, fp);
						}else
							if (strcmp(name, "pointsCollected")==0)
							{
								
								fread(&pointsCollected, sizeof(int), 1, fp);
							}else
								if (strcmp(name, "pointsSpent")==0)
								{
									
									fread(&pointsSpent, sizeof(int), 1, fp);
								}else
									if (strcmp(name, "towerBuilt")==0)
									{
										
										fread(&towerBuilt, sizeof(int), 1, fp);
									}else
										if (strcmp(name, "gameTimes")==0)
										{
											fread(&gameTimes, sizeof(int), 1, fp);
										}else
											if (strcmp(name, "defeatTimes")==0)
											{
												fread(&defeatTimes, sizeof(int), 1, fp);
											}
											else {
												int temp=0;
												fread(&temp,sizeof(int),1,fp);
											}
				
				delete [] name;
			}
			
			for (int i=0; i<fileGameAchievementSize; ++i) 
			{
				int stringlen=0;
				fread(&stringlen, sizeof(int), 1, fp);
				char *name=new char[stringlen+1];
				fread(name, sizeof(char), stringlen, fp);
				name[stringlen]='\0';
				
				
							
				
				 if  (strcmp(name, "collect100000")==0)
				{
					fread(&collect100000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "collect300000")==0)
				{
					fread(&collect300000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "collect500000")==0)
				{
					fread(&collect500000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "kill10000")==0)
				{
					fread(&kill10000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "kill50000")==0)
				{
					fread(&kill50000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "kill70000")==0)
				{
					fread(&kill70000, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name, "buildMoreThan600Towers")==0)
				{
					fread(&buildMoreThan600Towers, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "buildMoreThan1000Towers")==0)
				{
					fread(&buildMoreThan1000Towers,sizeof(bool),1,fp);
				}
				else if  (strcmp(name,  "buildMoreThan1200Towers")==0)
				{
					fread(&buildMoreThan1200Towers, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "finish100Games")==0)
				{
					fread(&finish100Games, sizeof(bool), 1,fp );
				}
				else if  (strcmp(name,  "finish500Games")==0)
				{
					fread(&finish500Games, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "finish1000Games")==0)
				{
					fread(&finish1000Games, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel1")==0)
				{
					fread(&completeLevel1, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel2")==0)
				{
					fread(&completeLevel2, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel3")==0)
				{
					fread(&completeLevel3, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel4")==0)
				{
					fread(&completeLevel4, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel5")==0)
				{
					fread(&completeLevel5, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel6")==0)
				{
					fread(&completeLevel6, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel7")==0)
				{
					fread(&completeLevel7, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel8")==0)
				{
					fread(&completeLevel8, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel9")==0)
				{
					fread(&completeLevel9, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel10")==0)
				{
					fread(&completeLevel10, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel11")==0)
				{
					fread(&completeLevel11, sizeof(bool), 1 , fp);
				}
				else if  (strcmp(name,  "completeLevel12")==0)
				{
					fread(&completeLevel12, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel13")==0)
				{
					fread(&completeLevel13, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel14")==0)
				{
					fread(&completeLevel14, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel15")==0)
				{
					fread(&completeLevel15, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel16")==0)
				{
					fread(&completeLevel16, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel17")==0)
				{
					fread(&completeLevel17, sizeof(bool), 1, fp);
					
				}
				else if  (strcmp(name,  "completeLevel18")==0)
				{
					fread(&completeLevel18, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel19")==0)
				{
					fread(&completeLevel19, sizeof(bool), 1, fp);
				}
				else if  (strcmp(name,  "completeLevel20")==0)
				{
					fread(&completeLevel20, sizeof(bool), 1, fp);
				}
				else {
					bool temp=false;
					fread(&temp,sizeof(bool),1,fp);
				}

				delete [] name;
				
			}
			
			
			for (int i=0; i<std::min(overallLevel,fileOverallLevel); ++i) {
				levels[i].loadFromFile(fp,fileLevelAchievementSize,fileLevelStatisticsSize);
			}
			
			
			fclose(fp);
		}
	}
}