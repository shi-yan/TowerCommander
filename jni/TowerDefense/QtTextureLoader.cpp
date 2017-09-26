/*
 *  TextureLoader.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "QtTextureLoader.h"

#include <QtGui/QImage>
#include <QtGui/QBitmap>
#include <QtOpengl/QGLWidget>
#include <cmath>
#include <string>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		GLuint TextureLoader::CreateTextureFromString()
		{
			return 0;
		}
		
		GLuint TextureLoader::CreateTextureFromPNG(const char* filename,int &width,int &height)
		{
			
			glEnable(GL_TEXTURE_2D);
			GLuint textureID=0;
			QImage t;
			QImage b;
			
			/*QMatrix m_qMetrix;
			
				
			m_qMetrix = m_qMetrix.scale(1, -1);
			*/
			if ( !b.load( filename ) )
			{
				b = QImage( 16, 16, QImage::Format_RGB32 );
				b.fill( Qt::green );
			}
			
			t = QGLWidget::convertToGLFormat( b )/*.transformed(m_qMetrix )*/;
			glGenTextures( 1, &textureID);
			glBindTexture( GL_TEXTURE_2D, textureID );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width=t.width(), height=t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		
			glBindTexture(GL_TEXTURE_2D, 0);
			printf("error: %d",glGetError());
			
			return textureID;
		}
		
		
		GLuint TextureLoader::CreateTextureFromTiles(std::vector<std::string> & tileList,int tileWidth,int tileHeight,int &width,int &height,int &sqr)
		{
			glEnable(GL_TEXTURE_2D);
			
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
			
			int h=0;
			int v=0;
			
			QImage resultImage(width,height,QImage::Format_ARGB32);
			resultImage.fill(0);
					QPainter painter(&resultImage);
			painter.begin(&resultImage);
			
			for (std::vector<std::string>::iterator iter=tileList.begin(); iter!=tileList.end(); ++iter) 
			{
				int positionx=h*tileWidth;
				int positiony=v*tileHeight;
				//printf("filename:%s\n",(*iter).c_str());
				QImage b;
				
				if(!b.load( (*iter).c_str() ))
				{
					b=QImage (tileWidth,tileHeight,QImage::Format_ARGB32);
					b.fill(Qt::green);
				}
				
				
				painter.drawImage(positionx,positiony,b);
				
				h++;
				
				if (h>=sqr) 
				{
					h=0;
					v++;
				}
			}
			
		//	painter.end();
			
			//printf("tile size: %d\n",tileList.size());
			//printf("width:%d\n",width);
		//	printf("height:%d\n",height);
			resultImage.save(QString("../../res/tiled%1.png").arg(tileHeight));
			
			QImage t=QGLWidget::convertToGLFormat(resultImage);
			
			glGenTextures( 1, &textureID);
			glBindTexture( GL_TEXTURE_2D, textureID );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		
			glBindTexture(GL_TEXTURE_2D, 0);
			printf("error: %d",glGetError());
			
			return textureID;
		}
	}
}