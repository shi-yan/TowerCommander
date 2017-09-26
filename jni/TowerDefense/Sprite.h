/*
 *  Sprite.h
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */
#ifndef __Sprite__
#define __Sprite__

#include "GlobalConfig.h"
#include <vector>
#include "Texture.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class Sprite  
		{
		protected:
			std::vector<Texture*> animationList;
			
			int currentAnimationID;
			int x;
			int y;
			int width;
			int height;
			
			int offsetX;
			int offsetY;
			bool isVisible;
			bool isRotate;
			float angle;
			
		public:
			int getX();
			int getY();
			void setVisible(bool _isV)
			{
				isVisible=_isV;
			};
			
			Sprite(float x,float y,int bodyTag);
			Sprite(float x, float y,int _width,int _height, int bodyTag);
			
			virtual ~Sprite()
			{
				for (int i=0; i<(int)animationList.size(); ++i) {
					delete animationList[i];
				}
			}
			
			void addTexture(Texture *aTexture);
			
			void animate();
			
			virtual void setAnimation(int animationID);
			
			void setOffsetXY(int _offsetX,int _offsetY);
			
			void setSize(int _width,int _height);
			
			void setXY(int _x,int _y)
			{
				x=_x;
				y=_y;
			};
			
			virtual void draw();
			
			virtual void drawRotate();
			
			void setRotation(float _angle)
			{
				isRotate=true;
				angle=_angle;
			};
		};
	}
}

#endif