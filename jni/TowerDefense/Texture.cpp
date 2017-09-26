/*
 *  Texture.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "Texture.h"
#include "TextureAtlas.h"
#include "TextureAtlasManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense {
		
		Texture::Texture(int _atlasID,int _startX,int _startY,int _width,int _height)
		:textureAtlasID(_atlasID),startX(_startX),startY(_startY),width(_width),height(_height)
		{
			textureID=TextureAtlasManager::getSingleton().getAtlasAt(_atlasID).getTextureID();
			updateTextureCoordinates();
		}
		
		void Texture::updateTextureCoordinates()
		{
			TextureAtlas atlas=TextureAtlasManager::getSingleton().getAtlasAt(textureAtlasID);
		
			textureID=atlas.getTextureID();
			
			textureCoordinates[4]=(float)startX/(float)atlas.getWidth();
			textureCoordinates[1]=(float)(atlas.getHeight()-startY)/(float)atlas.getHeight();
			
			textureCoordinates[6]=(float)(startX+width)/(float)atlas.getWidth();
			textureCoordinates[3]=(float)(atlas.getHeight()-startY)/(float)atlas.getHeight();
			
			textureCoordinates[0]=(float)(startX)/(float)atlas.getWidth();
			textureCoordinates[5]=(float)(atlas.getHeight()-startY-height)/(float)atlas.getHeight();
			
			textureCoordinates[2]=(float)(startX+width)/(float)atlas.getWidth();
			textureCoordinates[7]=(float)(atlas.getHeight()-startY-height)/(float)atlas.getHeight();
		}
		
		void Texture::apply()
		{
			if(textureID!=TextureAtlasManager::getSingleton().getLastTextureID())
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureID);
				TextureAtlasManager::getSingleton().setLastTextureID(textureID);
			}
		}
		
		float* Texture::getCoordinates()
		{
			return textureCoordinates;
		}
		
		void Texture::setAnimationTime()
		{
		}
		
		void Texture::setAnimationID()
		{
		}
		
		void Texture::animate()
		{
		}		
	}
}