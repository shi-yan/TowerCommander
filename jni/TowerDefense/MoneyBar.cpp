/*
 *  MoneyBar.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "MoneyBar.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
	
		void MoneyBar::init(int _atlas,int mon)
		{
			atlasID=_atlas;
		
			coinTexture=new TextureAnimation(atlasID,0,21,220,20,22,20);
			
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			coinTexture->addAnimation(k,10);
			coinTexture->setAnimation(0);
		
			digitTextures[1]=new Texture(atlasID,0,40,10,30);
			
			digitTextures[2]=new Texture(atlasID,10,40,17,30);
			
			digitTextures[3]=new Texture(atlasID,27,40,17,30);
			
			digitTextures[4]=new Texture(atlasID,44,40,16,30);
			
			digitTextures[5]=new Texture(atlasID,60,40,17,30);
			
			digitTextures[6]=new Texture(atlasID,77,40,18,30);
			
			digitTextures[7]=new Texture(atlasID,94,40,16,30);
			
			digitTextures[8]=new Texture(atlasID,110,40,17,30);
			
			digitTextures[9]=new Texture(atlasID,127,40,17,30);
			
			digitTextures[0]=new Texture(atlasID,144,40,21,30);		
		
			setMoney(mon);
		}
		
		void MoneyBar::setMoney(int mon)
		{
			money=(mon=mon>=0?mon:0);
			
			digits.clear();
			while (mon>9) 
			{
				int di=mon%10;
				digits.push_front(di);
				mon=(mon-di)/10;
			}
			
			digits.push_front(mon);
		}
		
		void MoneyBar::draw()
		{
			coinTexture->animate();
			coinTexture->apply();
			
			QuadHelper::getSingleton().drawQuad(10,10,22,20,coinTexture->getCoordinates());
			
			int overallWidth=0;
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) 
			{
				//overallWidth+=digitTextures[(*iter)]->width;
				
				digitTextures[(*iter)]->apply();
				
				QuadHelper::getSingleton().drawQuad(42+overallWidth,5,digitTextures[(*iter)]->width,digitTextures[(*iter)]->height,digitTextures[(*iter)]->getCoordinates());
				
				overallWidth+=digitTextures[(*iter)]->width;
				//break;
			};
			
			
		}
		
		
	}
}