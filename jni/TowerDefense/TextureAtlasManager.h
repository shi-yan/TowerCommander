/*
 *  TextureAtlasManager.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __TextureAtlasManager__
#define __TextureAtlasManager__

#include "GlobalConfig.h"
#include <vector>
#include <map>
#include "TextureAtlas.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class TextureAtlasManager
		{
		private:
			std::vector<TextureAtlas> atlasList;
			std::map<std::string,int> filenameHash;
			int lastTextureID;
			TextureAtlasManager():lastTextureID(-1)
			{};
			
		public:
			static TextureAtlasManager & getSingleton()
			{
				static TextureAtlasManager obj;
				return obj;
			};
			
			void setLastTextureID(int _id)
			{
				lastTextureID=_id;
			}
			
			 int getLastTextureID()
			{
				return lastTextureID;
			}
			
			void init();
			
			int addNew(const char *filename);
			int addNew(std::vector<std::string> & filenameList,int width,int height,int &sqr);
			int addEmptyNew(const char *filename);
			
		//	void openGLTextureRelease(int _id);
		//	void openGLTextureLoad(int _id);
		
			void releaseTextureAtlas(const char *filename);
			
			void restoreOpenGLTextures();
			
			TextureAtlas& getAtlasAt(int ID);
		};
	}
}

#endif