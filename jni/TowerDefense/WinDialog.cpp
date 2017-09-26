#include "WinDialog.h"
#include "TextureAtlasManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{
		WinDialog::WinDialog():InGameMenu()
		{
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("newdialogs.png");
#else
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/newdialogs.png");
#endif
			
			background=new Texture(atlas,1,441,325,273);
			achievementsLabel=new Texture(atlas,452,441,199,19);
			
			Texture *normal=new Texture(atlas,803,1,200,70);
			Texture *pressed=new Texture(atlas,803,74,200,70);
			
			continueButton=new GameButton();
			continueButton->setSize(167, 59);
			continueButton->setTexture(normal, pressed);
			
			label=new Texture(atlas,328,441,122,31);
			
			int k[10]={0,1,2,3,4,5,6,7,8,9};
			
			pointDigitTexture=new TextureAnimation(atlas,0,715,130,15,13,15);
			pointDigitTexture->addAnimation(k,10);
			pointDigitTexture->setAnimation(0);
			
			HotSpot::onReleaseDelegate ocr;
			ocr.bind(this,&WinDialog::onContinue);
			continueButton->addOnReleaseHandler(ocr);
		};
		
		WinDialog::~WinDialog()
		{
			delete background;
			delete continueButton;
			delete label;
			delete achievementsLabel;
			//delete noLabel;
			delete pointDigitTexture;
		};
		
		
		void WinDialog::draw()
		{
			int offset=0;
			
			if (isScrollingDown) 
			{
				offset=scrollOffset;
				scrollDown();
				
			}
			
			background->apply();
			
			QuadHelper::getSingleton().drawQuad(400-325*0.5f,240-273*0.5f-offset,325,273,background->getCoordinates());
			
			continueButton->setPosition(400, 200+173-60-offset);
			continueButton->draw();
			
			label->apply();
			QuadHelper::getSingleton().drawQuad(400-61,140-offset,122,31,label->getCoordinates());
			
			double currentTime=GameTimeManager::getSingleton().getCurrentTime();
			
			if (currentTime>goalPoints) {
				
				
				while (currentTime-oldUpdatePointsTime>0.05)
				{
					oldUpdatePointsTime+=0.05;
					
					currentPoints+=1;
					
					if (currentPoints>goalPoints) {
						continue;
					}
					
					refreshDigits(currentPoints,pointDigits);
				}
			}
			
			drawPoints(400-pointDigits.size()*13*0.5,160+33-offset,pointDigits);
			
				drawPoints(400-120,200+53-offset,achievementDigits );
			
			achievementsLabel->apply();
			QuadHelper::getSingleton().drawQuad(400-90,200+53-offset,199,19,achievementsLabel->getCoordinates());
		}
		
		void WinDialog::drawPoints(int x,int y,std::deque<int> & digits)
		{
			int currentx=x;
			int currenty=y;
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) 
			{
				pointDigitTexture->setAnimationStep(*iter);
				pointDigitTexture->apply();
				
				QuadHelper::getSingleton().drawQuad(currentx,y,13,15,pointDigitTexture->getCoordinates());
				
				currentx+=13;
			}
		}
		
		void WinDialog::setWinDialog(int _from,int _to,int _achievements)
		{
			currentPoints=_from;
			goalPoints=_to;
			achievements=_achievements;
			//if (achievements) 
			//{
				refreshDigits(achievements,achievementDigits);
			//}
			oldUpdatePointsTime=GameTimeManager::getSingleton().getCurrentTime();
		}
		
		void WinDialog::refreshDigits(int value,std::deque<int> & digits)
		{
			digits.clear();
			while (value>9) 
			{
				int di=value%10;
				digits.push_front(di);
				value=(value-di)/10;
			}
			
			digits.push_front(value);
		}

	}
}