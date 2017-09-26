/*
 *  NextWaveBar.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 10/10/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "NextWaveBar.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void NextWaveBar::init(int _atlas,int time)
		{
			atlasID=_atlas;
			
			nextWaveTexture=new TextureAnimation(atlasID,0,70,88,20,22,20);
			int k[4]={0,1,2,3};
			nextWaveTexture->addAnimation(k,4);
			nextWaveTexture->setAnimation(0);
			
			waveCounterBar=new Texture(atlasID,177,92,130,22);
			
			digitTextures[1]=new Texture(atlasID,0,90,10,30);
			
			digitTextures[2]=new Texture(atlasID,10,90,17,30);
			
			digitTextures[3]=new Texture(atlasID,27,90,17,30);
			
			digitTextures[4]=new Texture(atlasID,44,90,16,30);
			
			digitTextures[5]=new Texture(atlasID,60,90,17,30);
			
			digitTextures[6]=new Texture(atlasID,77,90,18,30);
			
			digitTextures[7]=new Texture(atlasID,94,90,16,30);
			
			digitTextures[8]=new Texture(atlasID,110,90,17,30);
			
			digitTextures[9]=new Texture(atlasID,127,90,17,30);
			
			digitTextures[0]=new Texture(atlasID,144,90,21,30);
			
			
			setTime(time);
		}
		
		void NextWaveBar::draw()
		{
			
			if (isVisable) 
			{
				nextWaveTexture->animate();
				nextWaveTexture->apply();
				QuadHelper::getSingleton().drawQuad(500,10,22,20,nextWaveTexture->getCoordinates());
				
				int overallWidth=0;
				for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) 
				{
					//overallWidth+=digitTextures[(*iter)]->width;
					
					digitTextures[(*iter)]->apply();
					
					QuadHelper::getSingleton().drawQuad(532+overallWidth,5,digitTextures[(*iter)]->width,digitTextures[(*iter)]->height,digitTextures[(*iter)]->getCoordinates());
					
					overallWidth+=digitTextures[(*iter)]->width;
					//break;
				};
				
				waveCounterBar->apply();
				
				QuadHelper::getSingleton().drawQuad(600,8,130,22,waveCounterBar->getCoordinates());
				
				int x=670;
				for (std::deque<int>::iterator iter=currentWave.begin(); iter!=currentWave.end(); ++iter) 
				{
					
					digitTextures[(*iter)]->apply();
					
					QuadHelper::getSingleton().drawQuad(x,5,digitTextures[(*iter)]->width,digitTextures[(*iter)]->height,digitTextures[(*iter)]->getCoordinates());
					
					x+=digitTextures[(*iter)]->width;
					
				};
				
				x=740;
				for (std::deque<int>::iterator iter=overallWave.begin(); iter!=overallWave.end(); ++iter) 
				{
					
					digitTextures[(*iter)]->apply();
					
					QuadHelper::getSingleton().drawQuad(x,5,digitTextures[(*iter)]->width,digitTextures[(*iter)]->height,digitTextures[(*iter)]->getCoordinates());
					
					x+=digitTextures[(*iter)]->width;
					
				};
			}
		}
		
		
		
	}
}