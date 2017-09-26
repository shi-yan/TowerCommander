#include "QuitDialog.h"

#ifdef	__ANDROID__

#include "AndroidSoundManager.h"
#else
#include "QtSoundManager.h"
#endif

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		QuitDialog::QuitDialog():InGameMenu(),background(NULL)
		{
#ifdef __ANDROID__
			int atlas=TextureAtlasManager::getSingleton().addNew("newdialogs.png");
#else
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/newdialogs.png");
#endif
			
			background=new Texture(atlas,1,441,325,273);
			
			Texture *normal=new Texture(atlas,803,147,200,70);
			Texture *pressed=new Texture(atlas,803,220,200,70);
			
			yesButton=new GameButton();
			yesButton->setSize(167, 59);
			yesButton->setTexture(normal, pressed);
			
			
			normal=new Texture(atlas,803,293,200,70);
			pressed=new Texture(atlas,803,366,200,70);
			
			noButton=new GameButton();
			noButton->setSize(167,59);
			noButton->setTexture(normal,pressed);
			
			label=new Texture(atlas,328,501,207,25);
			
			HotSpot::onReleaseDelegate oyr;
			oyr.bind(this,&QuitDialog::onYes);
			yesButton->addOnReleaseHandler(oyr);
			
			HotSpot::onReleaseDelegate onr;
			onr.bind(this,&QuitDialog::onNo);
			noButton->addOnReleaseHandler(onr);
		}
		
		QuitDialog::~QuitDialog()
		{
			delete background;
			delete yesButton;
			delete label;
			delete noButton;
		}
		
		void QuitDialog::draw()
		{
			int offset=0;
			
			if (isScrollingDown) 
			{
				offset=scrollOffset;
				scrollDown();
			}
			
			background->apply();
			
			QuadHelper::getSingleton().drawQuad(400-325*0.5f,240-273*0.5f-offset,325,273,background->getCoordinates());
			
			yesButton->setPosition(400, 200+173-60-59-offset);
			yesButton->draw();
			noButton->setPosition(400,200+173-60-offset);
			noButton->draw();
			
			label->apply();
			QuadHelper::getSingleton().drawQuad(400-103,140-offset,207,25,label->getCoordinates());
		}
	
		void QuitDialog::onYes()
		{
			SoundManager::getSingleton().playImmediately(SoundManager::BUTTON);
			for (std::vector<onYesDelegate>::iterator iter=onYesDelegateList.begin(); iter!=onYesDelegateList.end(); ++iter) 
			{
				(*iter)();
			}
		}
		
		void QuitDialog::onNo()
		{
			SoundManager::getSingleton().playImmediately(SoundManager::BUTTON);
			for (std::vector<onNoDelegate>::iterator iter=onNoDelegateList.begin(); iter!=onNoDelegateList.end(); ++iter) 
			{
				(*iter)();
			}
		}
	
		void QuitDialog::addOnYesHandler(onYesDelegate d)
		{
			onYesDelegateList.push_back(d);
		}
		
		void QuitDialog::addOnNoHandler(onNoDelegate d)
		{
			onNoDelegateList.push_back(d);
		}
	}
}