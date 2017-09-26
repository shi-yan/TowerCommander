/*
 *  LifeBar.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/21/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "LifeBar.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		void LifeBar::draw()
		{
			heartTexture->animate();
			heartTexture->apply();
			
			QuadHelper::getSingleton().drawQuad(240,10,22,20,heartTexture->getCoordinates());
			
			
			int overallWidth=0;
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) 
			{
				if ((*iter)<0 || (*iter)>9) 
				{
					continue;
				}
				
				digitTextures[(*iter)]->apply();
				QuadHelper::getSingleton().drawQuad(272+overallWidth,5,digitTextures[(*iter)]->width,digitTextures[(*iter)]->height,digitTextures[(*iter)]->getCoordinates());
				overallWidth+=digitTextures[(*iter)]->width;
			}
		}
		
		void LifeBar::setLife(int lif)
		{
			life=(lif=lif>=0?lif:0);
			
			digits.clear();
			while (lif>9) 
			{
				int di=lif%10;
				digits.push_front(di);
				lif=(lif-di)/10;
			}
			
			digits.push_front(lif);
		}
		
		
		void LifeBar::init(int _atlas,int lif)
		{
			atlasID=_atlas;
			
			heartTexture=new TextureAnimation(atlasID,0,0,88,20,22,20);
			int k[4]={0,1,2,3};
			heartTexture->addAnimation(k,4);
			heartTexture->setAnimation(0);
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
			
			setLife(lif);
		}
	}
}