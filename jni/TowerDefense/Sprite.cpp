/*
 *  Sprite.cpp
 *  TowerDefense
 *
 *  Created by Shi Yan on 8/30/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "Sprite.h"
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		int Sprite::getX()
		{
			return x;
		}
		int Sprite::getY()
		{
			return y;
		}
		
	
		Sprite::Sprite(float _x,float _y,int bodyTag):currentAnimationID(0),x(_x),y(_y),width(100),height(100),offsetX(0),offsetY(0),
		isVisible(true),isRotate(false),angle(0)
		{
		}
		
		
		Sprite::Sprite(float _x, float _y,int _width,int _height, int bodyTag):currentAnimationID(0),x(_x),y(_y),width(_width),height(_height),offsetX(0),offsetY(0)
		,isVisible(true),isRotate(false),angle(0)
		{
		}
		
		
		
		void Sprite::addTexture(Texture * aTexture)
		{
			animationList.push_back(aTexture);
		}
		
		void Sprite::animate()
		{
			animationList[currentAnimationID]->animate();
		}
		
		void Sprite::setAnimation(int animationID)
		{
			currentAnimationID=animationID;
		}
		
		void Sprite::setOffsetXY(int _offsetX,int _offsetY)
		{
			offsetX=_offsetX;
			offsetY=_offsetY;
		}
		
		void Sprite::setSize(int _width,int _height)
		{
			width=_width;
			height=_height;
		}
		
		void Sprite::drawRotate()
		{
			
			if (isVisible) {
				
				
				animationList[currentAnimationID]->apply();
				
				if (isRotate) {
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					glTranslatef(x, y, 0);
					glRotatef(angle,0,0,1);
					glTranslatef(-width*0.5, offsetY-height, 0);
					
	
				}
				
				QuadHelper::getSingleton().drawQuad(0,0,width,height,animationList[currentAnimationID]->getCoordinates());
				
				if (isRotate) {
					glMatrixMode(GL_MODELVIEW);
					glPopMatrix();
				}
			}
				
		}
		
		void Sprite::draw()
		{
		//	printf("ani:%d\n",currentAnimationID);
					
			animationList[currentAnimationID]->apply();
				
						
			QuadHelper::getSingleton().drawQuad(x+offsetX,y+offsetY,width,height,animationList[currentAnimationID]->getCoordinates());

			
		}
	}
}