/*
 *  CoinAnimation.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "CoinAnimation.h"
#include "GameMap.h"

namespace AnimalCrackers
{

	namespace TowerDefense 
	{
		TextureAnimation* CoinAnimation::digitTexture[10];

		TextureAnimation * CoinAnimation::coinTexture=NULL;
		
		void CoinAnimation::draw()
		{
			
			PointI mapOffset=GameMap::getSingleton().getMapOffset();
			
			coinTexture->setAnimationStep(currentTransparency);
			
			coinTexture->apply();
			
			QuadHelper::getSingleton().drawQuad(x-mapOffset.x,y-mapOffset.y,16,15,coinTexture->getCoordinates());
			
			int k=0;
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) {
				digitTexture[(*iter)]->setAnimationStep(currentTransparency);
				digitTexture[(*iter)]->apply();
				QuadHelper::getSingleton().drawQuad(x+17+k*9-mapOffset.x,y-mapOffset.y,8,11,digitTexture[(*iter)]->getCoordinates());
				k++;
			}
		}
		
		
		void CoinAnimation::setDigitTextures()
		{
			
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("ui.png");
#else
			
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/ui.png");
#endif
			coinTexture=new TextureAnimation(atlas,0,217,16,150,16,15);
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			coinTexture->addAnimation(k, 10);
			coinTexture->setAnimation(0);
			
			for (int i=0; i<10; ++i) 
			{
				digitTexture[i]=new TextureAnimation(atlas,25+i*8,218,8,110,8,11);
				digitTexture[i]->addAnimation(k, 10);
				digitTexture[i]->setAnimation(0);
			}
		}
		
		void CoinAnimation::releaseDigitTextures()
		{
			for (int i=0; i<10; ++i) 
			{
				delete  CoinAnimation::digitTexture[i];
			}
			
			delete CoinAnimation::coinTexture;
		}
		
		CoinAnimation::CoinAnimation(int mon):SmallAnimation(),currentTransparency(0)
		{
			digits.clear();
			while (mon>9) 
			{
				int di=mon%10;
				digits.push_front(di);
				mon=(mon-di)/10;
			}
			
			digits.push_front(mon);
		}
		
		void CoinAnimation::animate()
		{
			SmallAnimation::animate();
			
			currentTransparency=10.0f*elapsedTime/lastingTime;
			if (currentTransparency==10) 
			{
				currentTransparency=9;
			}
			
			setXY(x, y-1);
		}
		
	}
}