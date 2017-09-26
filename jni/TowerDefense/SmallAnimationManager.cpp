/*
 *  SmallAnimationManager.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "SmallAnimationManager.h"
#include "CoinAnimation.h"
#include "FlameAnimation.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		
		void SmallAnimationManager::init()
		{
			CoinAnimation::setDigitTextures();
			FlameAnimation::setFlameTextures();
			NotificationAnimation::setupNotificationAnimations();
			
		}
		
		void SmallAnimationManager::release()
		{
			CoinAnimation::releaseDigitTextures();
			FlameAnimation::releaseFlameTextures();
			NotificationAnimation::releaseNotificationAnimations();
		}
		
		void SmallAnimationManager::addExplosion(int _x,int _y,int type)
		{
			FlameAnimation *fa=new FlameAnimation(type);
			fa->setXY(_x,_y);
			fa->beginAnimation();
			
			while (flameAnimationList.size()>0 && (*(flameAnimationList.begin()))==NULL) {
				flameAnimationList.erase(flameAnimationList.begin());
			}
			
			flameAnimationList.push_back(fa);
		}
		
		void SmallAnimationManager::addNotification(int type)
		{
			NotificationAnimation *na=new NotificationAnimation(type);
			na->beginAnimation();
			while (notificationAnimationList.size()>0 && (*(notificationAnimationList.begin()))==NULL) {
				notificationAnimationList.erase(notificationAnimationList.begin());
			}
		
			notificationAnimationList.push_back(na);
		}
		
		void SmallAnimationManager::addCoin(int _x,int _y,int mon)
		{
			CoinAnimation *ca=new CoinAnimation(mon);
			ca->setXY(_x, _y);
			ca->beginAnimation();
			
			
			while (coinAnimationList.size()>0 && (*(coinAnimationList.begin()))==NULL) 
			{
				coinAnimationList.erase(coinAnimationList.begin());
			}
			
			coinAnimationList.push_back(ca);
		}
		
		SmallAnimationManager::~SmallAnimationManager()
		{
			for (std::vector<CoinAnimation*>::iterator iter=coinAnimationList.begin(); iter!=coinAnimationList.end();++iter ) 
			{
				if((*iter)!=NULL)
				{
					delete (*iter);
					(*iter)=NULL;
				}
			}
			
			for (std::vector<FlameAnimation*>::iterator iter=flameAnimationList.begin(); iter!=flameAnimationList.end(); ++iter) 
			{
				if((*iter)!=NULL)
				{
					delete (*iter);
					(*iter)=NULL;
				}
			}
			
			for (std::vector<NotificationAnimation*>::iterator iter=notificationAnimationList.begin(); iter!=notificationAnimationList.end(); ++iter) 
			{
				if ((*iter)!=NULL) {
					delete (*iter);
					(*iter)=NULL;
				}
			}
		}
		
		
		void SmallAnimationManager::draw()
		{
			for (std::vector<FlameAnimation*>::iterator iter=flameAnimationList.begin(); iter!=flameAnimationList.end(); ++iter) 
			{
				if((*iter)!=NULL)
				{
					if ((*iter)->isDead()) 
					{
						
						delete (*iter);
						(*iter)=NULL;
					}
					else
					{
						(*iter)->draw();
						(*iter)->animate();
						
					}
				}
			}
			
			for (std::vector<CoinAnimation*>::iterator iter=coinAnimationList.begin(); iter!=coinAnimationList.end();++iter ) 
			{
				if((*iter)!=NULL)
				{
					if ((*iter)->isDead()) 
					{
						
						delete (*iter);
						(*iter)=NULL;
					}
					else
					{
						(*iter)->draw();
						(*iter)->animate();
						
					}
				}
			}
			
			for (std::vector<NotificationAnimation*>::iterator iter=notificationAnimationList.begin(); iter!=notificationAnimationList.end(); ++iter) 
			{
				if ((*iter)!=NULL) 
				{
					if((*iter)->isDead())
					{
						delete (*iter);
						(*iter)=NULL;
					}
					else 
					{
						(*iter)->draw();
						(*iter)->animate();
					}
					
				}
			}
			
		}
	}
}

