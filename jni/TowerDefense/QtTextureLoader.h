/*
 *  TextureLoader.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "GlobalConfig.h"

#ifdef WIN32
#include <QGLWidget>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#endif
#include <vector>
#include <string>

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		class TextureLoader  
		{
		public:
			static GLuint CreateTextureFromString();
			static GLuint CreateTextureFromPNG(const char* filename,int &width,int &height);
			static GLuint CreateTextureFromTiles(std::vector<std::string> & tileList,int tileWidth,int tileHeight ,int &width,int &height,int &sqr);
		};
	}
}