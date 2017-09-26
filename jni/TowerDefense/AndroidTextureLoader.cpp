/*
 *  TextureLoader.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "AndroidTextureLoader.h"
#include <cmath>
#include <string>

#include <android/log.h>
#define  LOG_TAG    "libtowerdefense"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		
		jobject TextureLoader::Android_textureLoaderObject=0;
		jmethodID TextureLoader::Android_createTextureFromPNG=0;
		jmethodID TextureLoader::Android_createTextureFromTiles=0;
		
		JavaVM *TextureLoader::jVM=0;
		
		
		jfieldID TextureLoader::Android_textureID=0;
		jfieldID TextureLoader::Android_textWidth=0;
		jfieldID TextureLoader::Android_textHeight=0;
		jfieldID TextureLoader::Android_width=0;
		jfieldID TextureLoader::Android_height=0;
		
		
		
		GLuint TextureLoader::CreateTextureFromString()
		{
			return 0;
		}
		
		GLuint TextureLoader::CreateTextureFromPNG(const char* filename,int &width,int &height)
		{
			
		/*	glEnable(GL_TEXTURE_2D);
			GLuint textureID=0;
			QImage t;
			QImage b;
			
			
			if ( !b.load( filename ) )
			{
				b = QImage( 16, 16, QImage::Format_RGB32 );
				b.fill( Qt::green );
			}
			
			t = QGLWidget::convertToGLFormat( b );
			glGenTextures( 1, &textureID);
			glBindTexture( GL_TEXTURE_2D, textureID );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width=t.width(), height=t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		
			glBindTexture(GL_TEXTURE_2D, 0);
			printf("error: %d",glGetError());
			
			return textureID;
*/
			LOGI("create texture from png 1");
			JNIEnv *env;
			
			LOGI("create texture from png 2");
			jVM->GetEnv( (void**) &env, JNI_VERSION_1_4);
			
			LOGI("create texture from png 3");
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, "TowerCommander_JNI", "writeAudio audioBuffer=%p offset=%d length=%d");
#endif
			
			jstring jtexturename = env->NewStringUTF(filename);
			
			LOGI("create texture from png 4");
			jobject returned = env->CallObjectMethod( Android_textureLoaderObject,Android_createTextureFromPNG,jtexturename,false);
			
			LOGI("create texture from png 5");
			width=env->GetIntField(returned,Android_width);
			
			LOGI("create texture from png 6");
			height=env->GetIntField(returned,Android_height);
			
			LOGI("create texture from png 7");
			int textureID=env->GetIntField(returned,Android_textureID);
			
			LOGI("create texture from png 8");
			env->DeleteLocalRef(jtexturename);
			
			LOGI("create texture from png 9");
			env->DeleteLocalRef(returned);
			
			LOGI("create texture from png 10");
			return textureID;
			
			//return 0;		
		}
		
		
		GLuint TextureLoader::CreateTextureFromTiles(std::vector<std::string> & tileList,int tileWidth,int tileHeight,int &width,int &height,int &sqr)
		{
					
			GLuint textureID=0;
			
			 sqr=(int)sqrt((double)tileList.size())+1;
			
			int twidth=sqr*tileWidth;
			int theight=sqr*tileHeight;
			
			width=1;
			height=1;
			
			while (width<twidth) 
			{
				width=width<<1;
			};
			
			while (height<theight) 
			{
				height=height<<1;
			};
			
		//	LOGI("create texture from png 1");
			JNIEnv *env;
			
		//	LOGI("create texture from png 2");
			jVM->GetEnv( (void**) &env, JNI_VERSION_1_4);
			
			LOGI("create texture from png 3");
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, "TowerCommander_JNI", "writeAudio audioBuffer=%p offset=%d length=%d");
#endif
			
			
			jclass stringClass=env->FindClass("java/lang/String");
			
			jobjectArray result=env->NewObjectArray(tileList.size(),stringClass,NULL);
			
			if (result==NULL) {
				return 0;
			}
			
			for (int i=0; i<tileList.size(); ++i) {
				jstring jtexturename = env->NewStringUTF(tileList[i].c_str());
				env->SetObjectArrayElement(result,i,jtexturename);
				env->DeleteLocalRef(jtexturename);
			}
			
			
			jobject returned = env->CallObjectMethod( Android_textureLoaderObject,Android_createTextureFromTiles,result,tileWidth,tileHeight,width,height,sqr);
			
			
		//	LOGI("create texture from png 7");
			 textureID=env->GetIntField(returned,Android_textureID);
			
			
		//	LOGI("create texture from png 9");
			env->DeleteLocalRef(returned);
			
		//	LOGI("create texture from png 10");
			return textureID;
			
		
		}
	}
}