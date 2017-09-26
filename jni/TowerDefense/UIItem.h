/*
 *  UIItem.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __UIItem__
#define __UIItem__

#include "GlobalConfig.h"
#include "TextureAnimation.h"
#include <vector>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class UIItem  
		{
		protected:
			int width;
			int height;
			int x;
			int y;
			
			std::vector<Texture*> animationList;
			int currentAnimationID;
			
		public:
			
			UIItem(int _width,int _height);
			virtual ~UIItem();
			virtual bool isInside(int _x,int _y);
			virtual void draw();
			
			int getWidth(){return width;};
			int getHeight(){return height;};
			
			int getX(){return x;};
			int getY(){return y;};
			
			void setSize(int _width,int _height){width=_width;height=_height;};
			void setPosition(int _x,int _y){x=_x;y=_y;};
			
			void setCurrentAnimation(int _id)
			{
				currentAnimationID=_id;
			}
			
			void addAnimation(Texture *_texture);
		};
	}
}

#endif