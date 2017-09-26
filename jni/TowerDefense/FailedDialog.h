/*
 *  FailedDialog.h
 *  towerdefense
 *
 *  Created by Shi Yan on 11/19/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __FailedDialog__
#define __FailedDialog__

#include "InGameMenu.h"
#include "Texture.h"
#include "GameButton.h"
#include <deque>
#include <vector>

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class FailedDialog: public InGameMenu
		{
		public:
			typedef fastdelegate::FastDelegate0<> onContinueDelegate;
			
		private:
			
			std::vector<onContinueDelegate> continueDelegateList;
			
			FailedDialog();
			~FailedDialog();
			
			Texture *background;
			Texture *label;
			GameButton *continueButton;
			TextureAnimation *pointDigitTexture;
			
			std::deque<int> digits;
			
			void refreshDigits(int value);
			void drawPoints(int x,int y);
			
			int currentPoints;
			int goalPoints;
			double oldUpdatePointsTime;
			
			void onContinue()
			{
				for (std::vector<onContinueDelegate>::iterator iter=continueDelegateList.begin(); iter!=continueDelegateList.end(); ++iter) {
					(*iter)();
				}
			};
			
		public:
			
			void addOnContinueHandler(onContinueDelegate d)
			{
				continueDelegateList.push_back(d);
			};
			
			static FailedDialog & getSingleton()
			{
				static FailedDialog obj;
				return obj;
			};
			
			void draw();
			
			void setupFailedDialog(int from,int to);
			
			void handlePressEvent(int _x,int _y)
			{
				if(continueButton->handlePressEvent(_x, _y))
				{
					
				}
			};
			
			void handleReleaseEvent(int _x,int _y)
			{
				if(continueButton->handleReleaseEvent(_x, _y)){}
			};
		};
	}
}

#endif