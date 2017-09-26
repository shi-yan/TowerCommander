/*
 *  TextureLoader.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

/*#include <OpenGL/gl.h>
#include <OpenGL/glext.h>*/

#include <jni.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <vector>
#include <string>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <map>

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		struct TextureInfo
		{
			TextureInfo(GLuint id, int width, int height) : m_tid(id), m_width(width), m_height(height), m_refcount(1) {}
			
			GLuint Reuse(int &width, int &height)	{ width = m_width; height = m_height; ++m_refcount; return m_tid; }
			
			GLuint m_tid;
			int m_refcount;
			int m_width;
			int m_height;
		};
		
		class TextureLoader  
		{
		public:
			static jobject Android_textureLoaderObject;
			static jmethodID Android_createTextureFromPNG;
			static jmethodID Android_createTextureFromTiles;
			
			static JavaVM *jVM;
			
			static jfieldID Android_textureID;
			static jfieldID Android_textWidth;
			static jfieldID Android_textHeight;
			static jfieldID Android_width;
			static jfieldID Android_height;
			
			
		public:
			static GLuint CreateTextureFromString();
			static GLuint CreateTextureFromPNG(const char* filename,int &width,int &height);
			static GLuint CreateTextureFromTiles(std::vector<std::string> & tileList,int tileWidth,int tileHeight ,int &width,int &height,int &sqr);
		
		private:
			
			std::map<std::string, TextureInfo *> m_textureids;
		};
	}
}