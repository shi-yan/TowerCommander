/*
 *  TextureAtlas.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "TextureAtlas.h"

#ifdef __ANDROID__
#include "AndroidTextureLoader.h"
#else
#include "QtTextureLoader.h"
#endif 

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		TextureAtlas::TextureAtlas(const char *_filename,bool isEmpty)
		{
			if (isEmpty) 
			{
				
			}
			else
			{
			filenames.clear();
			
			textureID=TextureLoader::CreateTextureFromPNG(_filename, width, height);
			filenames.push_back(_filename);
			}
		}
		
		void TextureAtlas::reloadTexture()
		{
			if (filenames.size()==1) {
				textureID=TextureLoader::CreateTextureFromPNG(filenames[0].c_str(), width, height);
			}
			else if(filenames.size()>1)
			{
				int sqr=0;
				textureID=TextureLoader::CreateTextureFromTiles(filenames,tileWidth,tileHeight,width,height,sqr);
			}
		}
		
		TextureAtlas::TextureAtlas(std::vector<std::string> & filenameList,int _width,int _height,int & sqr,bool isEmpty)
		{
			textureID=TextureLoader::CreateTextureFromTiles(filenameList,tileWidth=_width,tileHeight=_height,width,height,sqr);

			filenames.clear();
			
			filenames.resize(filenameList.size());

			std::copy(filenameList.begin(),filenameList.end(),filenames.begin());
		}
		
		GLuint TextureAtlas::getTextureID()
		{
			return textureID;
		}
		
		int TextureAtlas::getHeight()
		{
			return height;
		}
		
		int TextureAtlas::getWidth()
		{
			return width;
		}
		
		TextureAtlas::~TextureAtlas()
		{
			
		}

		void TextureAtlas::releaseResource()
		{
			glDeleteTextures(1, &textureID);
		}
	}
}