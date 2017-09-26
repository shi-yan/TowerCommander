/*
 *  ResearchScreen.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/18/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __ResearchScreen__
#define __ResearchScreen__

#include "Screen.h"
#include "Texture.h"

#include "MainMenuButton.h"
#include "TowerIconButton.h"

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class ResearchScreen : public Screen
		{
		private:
			Texture *background;
			ResearchScreen();
			~ResearchScreen();
			
			MainMenuButton *researchButton;
			
			
			TowerIconButton *towerButtons[22];
			
			Texture *circle;
			int circlex;
			int circley;
			
			void onIconPressed(int i);
			bool isShowResearchButton;
				bool isShowLock;
			
		public:
			static ResearchScreen & getSingleton()
			{
				static ResearchScreen obj;
				return obj;
			};
			
			void renew();
			void draw();
			
			
			void handlePressEvent(int x,int y);
			
			void handleReleaseEvent(int x,int y);

			void onResearch();
			
		};
	}
}

#endif