#ifndef __QuitDialog__
#define __QuitDialog__

#include "GlobalConfig.h"
#include "InGameMenu.h"
#include "TextureAnimation.h"
#include <vector>
#include "FastDelegate.h"
#include "GameButton.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{

		class QuitDialog :public InGameMenu
		{
		public:
			typedef fastdelegate::FastDelegate0<> onYesDelegate;
			typedef fastdelegate::FastDelegate0<> onNoDelegate;
			
		private:
			std::vector<onYesDelegate> onYesDelegateList;
			std::vector<onNoDelegate> onNoDelegateList;
			
			
			
			Texture* background;
			GameButton * yesButton;
			GameButton * noButton;
			Texture * label;
			
			void onYes();
			void onNo();
		public:
			void addOnYesHandler(onYesDelegate d);
			void addOnNoHandler(onNoDelegate d);
			
			QuitDialog(void);
			~QuitDialog(void);
			void draw();
			
			void handlePressEvent(int _x,int _y)
			{
				if(yesButton->handlePressEvent(_x, _y))
				{
					
				}
				else if(noButton->handlePressEvent(_x, _y))
				{
				
				}
			};
			
			void handleReleaseEvent(int _x,int _y)
			{
				if(yesButton->handleReleaseEvent(_x, _y))
				{
				}
				else
				if(noButton->handleReleaseEvent(_x, _y))
				{
				
				}
			};
		};
	}
}

#endif