/*
 *  TextureAtlasManager.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "TextureAtlasManager.h"
#include <vector>
#include <string>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void TextureAtlasManager::init()
		{
			
		}
		
		int TextureAtlasManager::addNew(const char *filename)
		{
			if(filenameHash.find(filename)!=filenameHash.end())
			{
				return filenameHash[filename];
			}
			else
			{
				TextureAtlas atlas(filename);
				atlasList.push_back(atlas);
				int id= atlasList.size()-1;
				filenameHash[filename]=id;
				return id;
			}
		}
		
	//	void TextureAtlasManager::temporarilyRelease(int _id)
	//	{
			//TextureAtlas &atlas=atlasList[_id];
			
			
	//	}
		
		int TextureAtlasManager::addNew(std::vector<std::string> & filenameList,int width,int height,int &sqr)
		{
			TextureAtlas atlas(filenameList,width,height,sqr);
			atlasList.push_back(atlas);
			return atlasList.size()-1;
		}
		
		TextureAtlas& TextureAtlasManager::getAtlasAt(int ID)
		{
			return atlasList[ID];
		}
		
		void TextureAtlasManager::restoreOpenGLTextures()
		{
			lastTextureID=-1;
			
			for (std::vector<TextureAtlas>::iterator iter=atlasList.begin(); iter!=atlasList.end(); ++iter) {
				GLuint tid= (*iter).getTextureID();
				
				glDeleteTextures(1, &tid);
			}
			
			
			for (std::vector<TextureAtlas>::iterator iter=atlasList.begin(); iter!=atlasList.end(); ++iter) {
				GLuint tid= (*iter).getTextureID();
				
				(*iter).reloadTexture();
			}
		}
		
		int TextureAtlasManager::addEmptyNew(const char *filename)
		{
		/*	if(filenameHash.find(filename)!=filenameHash.end())
			{
				return filenameHash[filename];
			}
			else 
			{
				TextureAtlas atlas(filename)
			}
*/
return 0;
		}

	
		
		void TextureAtlasManager::releaseTextureAtlas(const char *filename)
		{
			if (filenameHash.find(filename)!=filenameHash.end()) 
			{
				
			
				int atlasID=filenameHash[filename];
				filenameHash.erase(filename);
			
				int k=0;
	
				for (std::vector<TextureAtlas>::iterator iter=atlasList.begin(); iter!=atlasList.end(); ++iter) 
				{
					if (k==atlasID) 
					{
						GLuint tid=(*iter).getTextureID();
						glDeleteTextures(1, &tid);
						atlasList.erase(iter);
					
						break;
					}
					k++;
				}
			}
		}
		
	}
}