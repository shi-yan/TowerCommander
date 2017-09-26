/*
 *  TextureAtlas.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __TextureAtlas__
#define __TextureAtlas__

#include "GlobalConfig.h"

#ifdef __ANDROID__
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#ifdef WIN32
#include <QGLWidget>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#endif
#endif

#include <vector>
#include <string>

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		class TextureAtlas {
		private:
			std::vector<std::string> filenames;
			GLuint textureID;
			int width;
			int height;
			int tileWidth;
			int tileHeight;
			
		public:
			TextureAtlas(const char *_filename,bool isEmpty=false);
			TextureAtlas(std::vector<std::string> & filenameList,int _width,int _height,int &sqr,bool isEmpty=false);
			
			GLuint getTextureID();
			void reloadTexture();
			int getHeight();
			int getWidth();
			~TextureAtlas();
			void releaseResource();
			
			bool operator==(const TextureAtlas &in)
			{
				if (textureID!=in.textureID) {
					return false;
				}
				
				if(width!=in.width)
					return false;
				
				if (height!=in.height) {
					return false;
				}
				
				if (tileWidth!=in.tileWidth) {
					return false;
				}
				
				if (tileHeight!=in.tileHeight) {
					return false;
				}
				
				if (filenames.size()==in.filenames.size()) 
				{
					for (int i=0; i<filenames.size(); ++i) 
					{
						if (filenames[i]!=(in.filenames[i])) {
							return false;
						}
					}
				}
				
				
				
				
			}
		};
		
	}
}

#endif