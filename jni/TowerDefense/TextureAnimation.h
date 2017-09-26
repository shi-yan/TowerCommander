/*
 *  TextureAnimation.h
 *  JumpNRun
 *
 *  Created by Shi Yan on 8/31/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __TextureAnimation__
#define __TextureAnimation__

#include "GlobalConfig.h"
#include "Texture.h"
#include <vector>
#include "TextureAtlasManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		class TextureAnimation : public Texture 
		{
		private:
			std::vector<float *> coordinateArray;
			std::vector<std::vector<int> > animations;
			
			double timeOfLastAnimationStep;
			
			int tileWidth;
			int tileHeight;
			
			int currentStep;
			
			int currentAnimationID;
			bool isFinished;
			bool isRepeat;
			
			double speed;
			
			void updateAnimationCoordinates()
			{
				TextureAtlas atlas=TextureAtlasManager::getSingleton().getAtlasAt(textureAtlasID);
				
				for(int v=0;v<height/tileHeight;++v)
					for(int u=0;u<width/tileWidth;++u)
					{
						int currentX=startX+u*tileWidth;
						int currentY=startY+v*tileHeight;
						
						float *subTextureCoordinate=new float[8];
						
									
																		
						subTextureCoordinate[4]=(float)currentX/(float)atlas.getWidth();
						subTextureCoordinate[1]=(float)(atlas.getHeight()-currentY)/(float)atlas.getHeight();
						
						subTextureCoordinate[6]=(float)(currentX+tileWidth)/(float)atlas.getWidth();
						subTextureCoordinate[3]=(float)(atlas.getHeight()-currentY)/(float)atlas.getHeight();
						
						subTextureCoordinate[0]=(float)currentX/(float)atlas.getWidth();
						subTextureCoordinate[5]=(float)(atlas.getHeight()-currentY-tileHeight)/(float)atlas.getHeight();
						
						
						subTextureCoordinate[2]=(float)(currentX+tileWidth)/(float)atlas.getWidth();
						subTextureCoordinate[7]=(float)(atlas.getHeight()-currentY-tileHeight)/(float)atlas.getHeight();
						
						
										
						coordinateArray.push_back(subTextureCoordinate);
					}
				
				//printf("fa");
			}
			
		public:
			
			void resetTime()
			{
				timeOfLastAnimationStep=-1;
			}
			
			void addAnimation(int k[],int num)
			{
				std::vector<int> anAnimation;
				
				for(int i=0;i<num;++i)
				{
					anAnimation.push_back(k[i]);
				}
				
				animations.push_back(anAnimation);
			}
			
			void setAnimation(int _id)
			{
				currentAnimationID=_id;
				currentStep=0;
			}
			
			int getCurrentAnimationFrames()
			{
				return animations[currentAnimationID].size();
			};

			TextureAnimation(int _atlasID,int _startX,int _startY,int _width,int _height,int _tileWidth,int _tileHeight)
			:Texture(_atlasID,_startX,_startY,_width,_height),currentStep(0),currentAnimationID(0),isFinished(false),isRepeat(true)
			{
				tileWidth=_tileWidth;
				tileHeight=_tileHeight;
				
				speed=0.08;
				
				timeOfLastAnimationStep=-1.0;

				updateAnimationCoordinates();
			}
			
			~TextureAnimation()
			{
				for(int i=0;i<(int)coordinateArray.size();++i)
				{
					delete coordinateArray[i];
				}
				
				coordinateArray.clear();
			}
			
			int getTileWidth()
			{
				return tileWidth;
			}
			
			int getTileHeight()
			{
				return tileHeight;
			}
			
			float * getCoordinates()
			{
				/*printf("coord\n");
				
				printf("%f,%f\n",coordinateArray[(animations[currentAnimationID])[currentStep]][0],coordinateArray[(animations[currentAnimationID])[currentStep]][1]);
				
				printf("%f,%f\n",coordinateArray[(animations[currentAnimationID])[currentStep]][2],coordinateArray[(animations[currentAnimationID])[currentStep]][3]);
				
				printf("%f,%f\n",coordinateArray[(animations[currentAnimationID])[currentStep]][4],coordinateArray[(animations[currentAnimationID])[currentStep]][5]);
				
				printf("%f,%f\n",coordinateArray[(animations[currentAnimationID])[currentStep]][6],coordinateArray[(animations[currentAnimationID])[currentStep]][7]);
				*/
				return coordinateArray[(animations[currentAnimationID])[currentStep]];
			}
			
			void setAnimationStep(int i)
			{
				currentStep=i;
			}
			
			void animate();
			
			bool checkFinished()
			{
				return isFinished;
			}
		};
	}
}

#endif