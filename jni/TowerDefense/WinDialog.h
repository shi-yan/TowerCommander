
#ifndef __WinDialog__
#define __WinDialog__

#include "GlobalConfig.h"
#include "GameButton.h"
#include "QuadHelper.h"
#include "FastDelegate.h"
#include <vector>
#include "Texture.h"
#include <string>
#include "InGameMenu.h"
#include <deque>
namespace AnimalCrackers
{
	namespace TowerDefense
	{
		class WinDialog :public InGameMenu
		{
		public:
			typedef fastdelegate::FastDelegate0<> onContinueDelegate;
			
		private:
			
			std::vector<onContinueDelegate> continueDelegateList;
			
			WinDialog();
			~WinDialog();
			
			Texture *background;
			Texture *label;
			
			Texture *achievementsLabel;
			
			GameButton *continueButton;
			
			TextureAnimation *pointDigitTexture;
			
			std::deque<int> pointDigits;
			std::deque<int> achievementDigits;
			
			void refreshDigits(int value,std::deque<int> & digits);
			void drawPoints(int x,int y,std::deque<int> & digits);
			
			int currentPoints;
			int goalPoints;
			int achievements;
			
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
			
			static WinDialog & getSingleton()
			{
				static WinDialog obj;
				return obj;
			};
			
			void draw();
			
			void setWinDialog(int from,int to,int _achievements);
			
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