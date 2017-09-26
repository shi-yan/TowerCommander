/*
 *  UIItem.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "UIItem.h"
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		UIItem::UIItem(int _width,int _height)
		:width(_width),height(_height),x(0),y(0),currentAnimationID(0)
		{
		}
		
		UIItem::~UIItem()
		{
			for (std::vector<Texture*>::iterator iter=animationList.begin(); iter!=animationList.end(); ++iter) 
			{
				delete (*iter);
				(*iter)=NULL;
			}
			
			animationList.clear();
		}
		
		
		void UIItem::addAnimation(Texture *_texture)
		{
			animationList.push_back(_texture);
		}
		
		bool UIItem::isInside(int _x,int _y)
		{
			float w=width*0.5f;
			float h=height*0.5f;
			
			if(_x>x-w && _x<x+w && _y>y-h && _y<y+h)
			{
				return true;
			}
			else 
			{
				return false;
			}

		}
		
		void UIItem::draw()
		{
			animationList[currentAnimationID]->apply();
			
			float rx=x-(float)(width*0.5f);
			float ry=y-(float)(height*0.5f);
			
			QuadHelper::getSingleton().drawQuad(rx,ry,width,height,animationList[currentAnimationID]->getCoordinates());
			
		}
		
	}
}