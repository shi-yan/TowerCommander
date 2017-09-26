#pragma once

#include "GlobalConfig.h"
#include "GameButton.h"
#include "InGameMenu.h"
#include <vector>
#include "FastDelegate.h"
#include "Texture.h"
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{

		class LostDialog :	public InGameMenu
		{
		public:
			typedef fastdelegate::FastDelegate0<> onNextDelegate;
			typedef fastdelegate::FastDelegate0<> onRetryDelegate;
	
		private:
			GameButton *nextButton;
			GameButton *retryButton;
			Texture *lostTexture;
			std::vector<onNextDelegate> onNextDelegateList;
			std::vector<onRetryDelegate> onRetryDelegateList;

		public:
			LostDialog(void);
			virtual ~LostDialog(void);

			void draw()
			{
				if(isVisiable)
				{
					background->apply();
					QuadHelper::getSingleton().drawQuad(400-width*0.5f,240-height*0.5f,width,height,background->getCoordinates());
				
					lostTexture->apply();
					QuadHelper::getSingleton().drawQuad(400-200*0.5f,240-100*0.5f,200,100,lostTexture->getCoordinates());

					nextButton->draw();
					retryButton->draw();
				}
			};

			void addOnNextHandler(onNextDelegate ond)
			{
				onNextDelegateList.push_back(ond);
			}

			void addOnRetryHandler(onRetryDelegate ord)
			{
				onRetryDelegateList.push_back(ord);
			}

		private:
			void onNext()
			{
				for(std::vector<onNextDelegate>::iterator iter=onNextDelegateList.begin();iter!=onNextDelegateList.end();++iter)
				{
					(*iter)();
				}
			};

			void onRetry()
			{
				for(std::vector<onRetryDelegate>::iterator iter=onRetryDelegateList.begin();iter!=onRetryDelegateList.end();++iter)
				{
					(*iter)();
				}	
			};
		};
	}
}