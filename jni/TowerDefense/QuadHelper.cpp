/*
 *  QuadHelper.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "QuadHelper.h"

#include "TextureAtlasManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void QuadHelper::drawQuad(int x,int y,int width,int height,float textureCoordinate[])
		{
			mVertexBuffer[0]=x;
			mVertexBuffer[1]=y;
			mVertexBuffer[2]=x+width;
			mVertexBuffer[3]=y;
			mVertexBuffer[4]=x;
			mVertexBuffer[5]=y+height;
			mVertexBuffer[6]=x+width;
			mVertexBuffer[7]=y+height;
			
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertexPointer(2, GL_SHORT, 0, mVertexBuffer);
			glEnableClientState(GL_VERTEX_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinate);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
		
		void QuadHelper::drawQuad(int x,int y,int width,int height)
		{
			mVertexBuffer[0]=x;
			mVertexBuffer[1]=y;
			mVertexBuffer[2]=x+width;
			mVertexBuffer[3]=y;
			mVertexBuffer[4]=x;
			mVertexBuffer[5]=y+height;
			mVertexBuffer[6]=x+width;
			mVertexBuffer[7]=y+height;
			glBindTexture(GL_TEXTURE_2D, 0);
		//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertexPointer(2, GL_SHORT, 0, mVertexBuffer);
			glEnableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
		
		
		
		void QuadHelper::init()
		{
		//	int atlas=TextureAtlasManager::getSingleton().addNew("d");

		//	charMap['a']=new Texture(atlas,12,12,12,12);



		}

		void QuadHelper::drawText(int x,int y,const char *text,int len,int wordwrap)
		{
			if(wordwrap==0)
			{
				int tempx=x;
			
				for(int i=0;i<len;i++)
				{

					Texture *t=charMap[text[i]];
					t->apply();
					drawQuad(tempx,y,t->width,t->height,t->getCoordinates());
					tempx+=t->width;
				}
			}
			else
			{
				int overallwidth=0;
				int tempx=x;
				int tempy=y;

				for(int i=0; i<len; i++)
				{
					Texture *t=charMap[text[i]];
					if(overallwidth+t->width>wordwrap)
					{
						overallwidth=0;
						tempx=x;
						tempy+=t->height;
					}
					t->apply();
					drawQuad(tempx,y,t->width,t->height,t->getCoordinates());
					tempx+=t->width;
					overallwidth+=t->width;
				}
			}
		}
	}
}