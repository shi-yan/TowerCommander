/*
 *  FlameAnimation.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 10/28/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "FlameAnimation.h"
#include "TextureAtlasManager.h"
#include "GameMap.h"

namespace AnimalCrackers
{

	namespace TowerDefense 
	{
		TextureAnimation *FlameAnimation::flameTextures[18];
		
		void FlameAnimation::setFlameTextures()
		{
			
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("flame.png");
#else
			
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/flame.png");
#endif
			flameTextures[0]=new TextureAnimation(atlas,0,0,480,48,48,48);
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			flameTextures[0]->addAnimation(k,10);
			flameTextures[0]->setAnimation(0);
			
			flameTextures[1]=new TextureAnimation(atlas,0,49,1008,144,84,72);
			int k2[21]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			flameTextures[1]->addAnimation(k2, 15);
			flameTextures[1]->setAnimation(0);
			
			flameTextures[2]=new TextureAnimation(atlas,283,132,640,64,64,64);
			flameTextures[2]->addAnimation(k, 10);
			flameTextures[2]->setAnimation(0);
			
			flameTextures[3]=new TextureAnimation(atlas,1,206,1022,53,68,53);
			flameTextures[3]->addAnimation(k2, 14);
			flameTextures[3]->setAnimation(0);
			
			flameTextures[4]=new TextureAnimation(atlas,1,258,1022,48,48,48);
			flameTextures[4]->addAnimation(k2, 21);
			flameTextures[4]->setAnimation(0);
			
			flameTextures[5]=new TextureAnimation(atlas,1,307,1022,52,68,52);
			flameTextures[5]->addAnimation(k2, 15);
			flameTextures[5]->setAnimation(0);
			
			flameTextures[6]=new TextureAnimation(atlas,1,362,58*13,58,58,58);///
			flameTextures[6]->addAnimation(k2, 13);
			flameTextures[6]->setAnimation(0);
			
			flameTextures[7]=new TextureAnimation(atlas,1,438,640,64,64,64);
			flameTextures[7]->addAnimation(k2, 10);
			flameTextures[7]->setAnimation(0);
			
			flameTextures[8]=new TextureAnimation(atlas,1,504,320,32,32,32);
			flameTextures[8]->addAnimation(k2, 10);
			flameTextures[8]->setAnimation(0);
			
			flameTextures[9]=new TextureAnimation(atlas,1,538,640,64,64,64);
			flameTextures[9]->addAnimation(k2, 10);
			flameTextures[9]->setAnimation(0);
			
			
			flameTextures[10]=new TextureAnimation(atlas,1,604,640,64,64,64);
			flameTextures[10]->addAnimation(k2, 10);
			flameTextures[10]->setAnimation(0);
			
			flameTextures[11]=new TextureAnimation(atlas,1,670,480,48,48,48);
			flameTextures[11]->addAnimation(k, 10);
			flameTextures[11]->setAnimation(0);
			
			flameTextures[12]=new TextureAnimation(atlas,1,720,480,48,48,48);
			flameTextures[12]->addAnimation(k, 10);
			flameTextures[12]->setAnimation(0);
			
			flameTextures[13]=new TextureAnimation(atlas,1,770,640,64,64,64);
			flameTextures[13]->addAnimation(k, 10);
			flameTextures[13]->setAnimation(0);
			
			flameTextures[14]=new TextureAnimation(atlas,0,836,432,25,27,25);
			flameTextures[14]->addAnimation(k2, 15);
			flameTextures[14]->setAnimation(0);
			
			flameTextures[15]=new TextureAnimation(atlas,1,862,960,60,960/15,60);
			flameTextures[15]->addAnimation(k2, 15);
			flameTextures[15]->setAnimation(0);
			
			flameTextures[16]=new TextureAnimation(atlas,1,925,660,62,66,62);
			flameTextures[16]->addAnimation(k2, 10);
			flameTextures[16]->setAnimation(0);
		
			flameTextures[17]=new TextureAnimation(atlas,1,988,731,34,731/19,34);
			flameTextures[17]->addAnimation(k2, 19);
			flameTextures[17]->setAnimation(0);
			
		}
		
		void FlameAnimation::releaseFlameTextures()
		{
			for(int i=0;i<18;++i)
			{
				if(flameTextures[i])
				delete flameTextures[i];
			}
		}
		
		void FlameAnimation::draw()
		{
			PointI mapOffset=GameMap::getSingleton().getMapOffset();
			flameTextures[animeType]->setAnimationStep(currentAnimationStep);
			
			flameTextures[animeType]->apply();
			
			QuadHelper::getSingleton().drawQuad(x-mapOffset.x-flameTextures[animeType]->getTileWidth()*0.5f,y-mapOffset.y-flameTextures[animeType]->getTileHeight()*0.5f,flameTextures[animeType]->getTileWidth(),flameTextures[animeType]->getTileHeight(),flameTextures[animeType]->getCoordinates());
			
		}
		
		void FlameAnimation::animate()
		{
			SmallAnimation::animate();
			int aniSize=flameTextures[animeType]->getCurrentAnimationFrames();
			currentAnimationStep=(float)aniSize*elapsedTime/lastingTime;
			if (currentAnimationStep==aniSize) {
				currentAnimationStep=aniSize-1;
			}
		}
	}

}