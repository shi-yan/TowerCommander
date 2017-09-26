/*
 *  FlameTower.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 11/11/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "FlameTower.h"
#include "GameMap.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		void FlameTower::shotAtEnemy(int id,Enemy *e)
		{
			if (e->getEnemyType()!=Enemy::Ground) 
			{
				return;
			}
			
			if(shotAtEnemyID==-1)
			{
				float offsetx=e->fakePosition.x-(position.x*TileSize+(TileSize*0.5f));
				float offsety=e->fakePosition.y-(position.y*TileSize+(TileSize*0.5f));
				
				float distance=offsetx*offsetx+
				offsety*offsety;
				
				if(distance<range)
				{
					shotAtEnemyID=id;
					
					float realdis=(float) sqrt((float)distance)-10.0f;
					float angle=0;
					
					if(offsetx>0)
						angle=(float) acos((double)(offsety/sqrt(distance)));
					else
					{
						angle=(float) (2*PI-acos(offsety/sqrt(distance)));
					}
					
					rid=(int) (angle/(PI)*180+15)/30;
					
					if(rid<0)
						rid=0;
					if(rid>11)
						rid=11;
					
					towerTextures->setAnimation(rid);					
					
					
					if(oldshotAtEnemyID==shotAtEnemyID)
					{
						
						double currentTime=GameTimeManager::getSingleton().getCurrentTime();
						//double pastTime=currentTime-lastShotTime;
						
						//accumulatedShootingTime+=pastTime;
						
						while (/*accumulatedShootingTime*/currentTime-lastShotTime>interval) 
						{
							//accumulatedShootingTime-=interval;
							
							lastShotTime+=interval;
							
							accumulatedSpeed+=shotSpeed;
							
					
			
							
							bullet->setVisible(true);
							bulletpos+=bullet->getSpeed();
							
							if(bulletpos>realdis)
								bulletpos=0.0f;
							
							
							
						}
						
						while (accumulatedSpeed>2.0f) 
						{
							accumulatedSpeed-=2.0f;
							
							e->lastingDamage(damage);
						}
					}
					else
					{
					//	accumulatedShootingTime=0;
						accumulatedSpeed=0;
						lastShotTime=GameTimeManager::getSingleton().getCurrentTime();
					}
					
					PointI offset=GameMap::getSingleton().getMapOffset();
					bullet->setPositionOffsetRotation(bulletpos,accuratePosition,offset,angle,bulletOffset[rid]);
					
					oldshotAtEnemyID=shotAtEnemyID;
					
				}
			}
		}
		
	}
}