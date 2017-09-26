/*
 *  WalkableEnemy.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "WalkableEnemy.h"

namespace AnimalCrackers
{
	namespace TowerDefense {
		bool WalkableEnemy::move() 
		{
			double currentMoveTime=GameTimeManager::getSingleton().getCurrentTime();
			while (currentMoveTime-lastMoveTime>0.06) 
			{
					lastMoveTime+=0.06;
			walkAnimation->animate();
			if (pathStep==0 && moved==0.0f)
			{
				
				//you bu 原因是在场面上没有敌人的时候，没有保证有一条从起点通往终点的通路。
				if (path[(pathStep + 1)].y < path[(pathStep)].y)
				{
					direction = North;
					
					walkAnimation->setAnimation(0);
				}
				else if (path[(pathStep + 1)].y > path[(pathStep)].y){
					direction =South;
					
					walkAnimation->setAnimation(1);
				}
				else if (path[(pathStep + 1)].x > path[(pathStep)].x){
					direction = East;
					
					walkAnimation->setAnimation(3);
				}
				else if (path[(pathStep + 1)].x < path[(pathStep)].x){
					
					direction = West;
					
					walkAnimation->setAnimation(2);
				}
			}
			
			movestart.x = (float)path[(pathStep)].x*TileSize+TileSize*0.5f;
			movestart.y = (float)path[(pathStep)].y*TileSize + TileSize * 0.5f;
			
			if (pathStep >= path.size() - 1)
			{
				return true;
			}
			else
			{
				moveend.x = (float)path[(pathStep + 1)].x*TileSize+TileSize*0.5f;
				moveend.y = (float)path[(pathStep + 1)].y*TileSize + TileSize * 0.5f;
			}
			
			moved += speed*slowDownRate;
			
			if (slowDownRate<1.0f) {
				printf("fuck!!!!!!\n");
			}
			
			if (moved < 1.0f)
			{
				fakePosition.x = ((float)movestart.x) *(1.0f- moved) + ( moved) *(float) moveend.x;
				fakePosition.y = ((float)movestart.y) * (1.0f-moved) + ( moved) * (float)moveend.y;
			}
			else 
			{
				//change direction
				
				do
				{
					moved -= 1.0f;
					
					pathStep++;
					
					if (pathStep > path.size() - 1) 
					{
						moved = 0.0f;
						pathStep = 0;
					}
					
					position = path[(pathStep)];
					
					if (pathStep < path.size() - 1)
					{
						if (path[(pathStep + 1)].y < path[(pathStep)].y)
						{
							direction = North;
							walkAnimation->setAnimation(0);
						}
						else if (path[(pathStep + 1)].y > path[(pathStep)].y){
							direction = South;
							walkAnimation->setAnimation(1); 
						}
						else if (path[(pathStep + 1)].x > path[(pathStep)].x){
							direction = East;
							walkAnimation->setAnimation(3);
						}
						else if (path[(pathStep + 1)].x < path[(pathStep)].x){
							
							direction = West;
							walkAnimation->setAnimation(2);
						}
					}
					
					movestart.x = (float)path[(pathStep)].x*TileSize + TileSize * 0.5f;
					movestart.y = (float)path[(pathStep)].y*TileSize + TileSize * 0.5f;
					
					if (pathStep >= path.size() - 1)
						moveend = movestart;
					else
					{
						moveend.x = (float)path[(pathStep + 1)].x*TileSize + TileSize * 0.5f;
						moveend.y = (float)path[(pathStep + 1)].y*TileSize + TileSize * 0.5f;
					}
					
					fakePosition.x = ((float)movestart.x) *(1.0f- moved) + ( moved) * (float)moveend.x;
					fakePosition.y = ((float)movestart.y) * (1.0f-moved) + ( moved) * (float)moveend.y;
					
					
					
				}
				while(moved>=1.0f);
			}
			
				renewDisplayPosition();
			}
			return false;
		}
		
		void WalkableEnemy::draw()
		{
			walkAnimation->apply();
			
			
			QuadHelper::getSingleton().drawQuad(x+offsetX,y+offsetY,width,height,walkAnimation->getCoordinates());
			
			Enemy::bloodTexture->setAnimationStep(currentBloodAnimationID);
			Enemy::bloodTexture->apply();
			
			QuadHelper::getSingleton().drawQuad(x+offsetX+2,y+offsetY-10,35,4,Enemy::bloodTexture->getCoordinates());
		}
	}
}