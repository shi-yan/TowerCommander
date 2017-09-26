/*
 *  Tower.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "Tower.h"

#include "GameMap.h"



namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void Tower::setPosition(PointI _pos)
		{
			PointI mapOffset=GameMap::getSingleton().getMapOffset();
			position=_pos;
			accuratePosition.x=_pos.x*TowerWidth;
			accuratePosition.y=_pos.y*TowerWidth-(TowerHeight-TowerWidth);
			setXY(accuratePosition.x-mapOffset.x, accuratePosition.y-mapOffset.y);
		}
		
		
		
		void Tower::afterShootingAtEnemy()
		{
			if (shotAtEnemyID!=-1) 
			{
				SoundManager::getSingleton().play(soundEffect);
				shotAtEnemy(-1);
			}
			else
			{
				bullet->setVisible(false);
			}
		}
		
		void Tower::shotAtEnemy(int id,Enemy *e)
		{
			if(shotAtEnemyID==-1)
			{
				float offsetx=e->fakePosition.x-(position.x*TowerWidth+(TowerWidth*0.5f));
				float offsety=e->fakePosition.y-(position.y*TowerWidth+(TowerWidth*0.5f));
				
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
							
							e->immediateDamage(damage);
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