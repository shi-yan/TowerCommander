/*
 *  QuadHelper.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */


#ifndef __QuadHelper__
#define __QuadHelper__
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

#include "Texture.h"
#include <map>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class QuadHelper  
		{
		private:
			GLshort mVertexBuffer[8];
			GLfloat mTexBuffer[8];
			std::map<char,Texture*> charMap;
			
		public:
			void init();
			static QuadHelper & getSingleton()
			{
				static QuadHelper obj;
				return obj;
			};
			
			void drawQuad(int x,int y,int width,int height,float textureCoordinate[]);
			void drawQuad(int x,int y,int width,int height);
			void drawText(int x,int y,const char *text,int len,int wordwrap=0);
		};
	}
}

#endif