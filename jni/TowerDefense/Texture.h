/*
 *  Texture.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __TEXTURE__
#define __TEXTURE__

#include "GlobalConfig.h"
namespace AnimalCrackers
{
	namespace TowerDefense
	{
		class Texture
		{
		public: 
			int textureAtlasID;
			int textureID;
			int startX;
			int startY;
			int width;
			int height;
			
		public:
			Texture(int _atlasID,int _startX,int _startY,int _width,int _height);
			void apply();
			void updateTextureCoordinates();
			virtual float* getCoordinates();
			virtual void setAnimationTime();
			virtual void setAnimationID();
			virtual void animate();
			virtual ~Texture(){}
			virtual bool checkFinaished()
			{
				return false;
			}
			
			Texture *clone()
			{
				return new Texture(textureAtlasID,startX,startY,width,height);
			};
			
		private:
			float textureCoordinates[8];
			
			
		};
	}
}

#endif