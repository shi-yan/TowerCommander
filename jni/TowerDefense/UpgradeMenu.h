
#ifndef __UpgradeMenu__
#define __UpgradeMenu__

#include "GlobalConfig.h"
#include "GameButton.h"
#include "InGameMenu.h"
#include "Tower.h"
#include <vector>
#include <deque>

namespace AnimalCrackers
{
	namespace TowerDefense
	{

		class UpgradeMenu:public InGameMenu
		{
		public:
			typedef fastdelegate::FastDelegate3<int,int,int> onOkDelegate;
			typedef fastdelegate::FastDelegate0<> onCancelDelegate;
			
		private:
			GameButton *sellButton;
			GameButton *upgradeButtons[2];
			GameButton *cancelButton;
			
			int towerx;
			int towery;
			
			std::vector<onOkDelegate> onOkDelegateList;
			std::vector<onCancelDelegate> onCancelDelegateList;

			Texture *sellTowerTexture;
			Texture *upgradeTowerTextures[2];
			int upgradeMoney[2];
			int upgradeSpeed[2];
			int upgradePower[2];
			int upgradeRange[2];
			int upgradeChoices[2];
		
			int sellMoney;
			int sellSpeed;
			int sellPower;
			int sellRange;
			
			UpgradeMenu(void);
			
			virtual ~UpgradeMenu(void);

			Texture *towerTextures[22];
			
			TextureAnimation *bar;
			
			int currentChoice;
			
			std::deque<int> sellMoneyDigits;
			std::deque<int> moneyDigits[2];
			
			TextureAnimation *moneyDigitTexture;
			
		public:
			
			void addOnOkHandler(onOkDelegate d)
			{
				onOkDelegateList.push_back(d);
			}
			
			void addOnCancelHandler(onCancelDelegate d)
			{
				onCancelDelegateList.push_back(d);
			}
			
		//	void onOk();
			
			void onCancel()
			{
				for (std::vector<onCancelDelegate>::iterator iter=onCancelDelegateList.begin(); iter!=onCancelDelegateList.end(); ++iter) 
				{
					(*iter)();
				}
			}
			
			static UpgradeMenu & getSingleton()
			{
				static UpgradeMenu obj;
				return obj;
			};
			
			void init()
			{
#ifdef __ANDROID__
				int atlas=TextureAtlasManager::getSingleton().addNew("tower.png");
				int batlas=TextureAtlasManager::getSingleton().addNew("newdialogs.png");
#else
	
				int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/tower.png");
				int batlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/newdialogs.png");
#endif
				
				for(int i=0;i<16;++i)
				{
					towerTextures[i]=new Texture(atlas,TowerWidth,0+i*TowerHeight,TowerWidth,TowerHeight);
				}
				
				towerTextures[16]=new Texture(atlas,480+TowerWidth,780,TowerWidth,TowerHeight);
				
					towerTextures[17]=new Texture(atlas,480+TowerWidth,720,TowerWidth,TowerHeight);
					towerTextures[18]=new Texture(atlas,480+TowerWidth,660,TowerWidth,TowerHeight);
					towerTextures[19]=new Texture(atlas,480+TowerWidth,600,TowerWidth,TowerHeight);
					towerTextures[20]=new Texture(atlas,480+TowerWidth,540,TowerWidth,TowerHeight);
					towerTextures[21]=new Texture(atlas,480,540,TowerWidth,TowerHeight);
				currentChoice=-2;
				
				
				
				
				background=new Texture(batlas,1,1,598,438);
				
				sellButton=new GameButton();
				Texture *pt=new Texture(batlas,601,147,200,70);
				Texture *rt=new Texture(batlas,601,220,200,70);
				
				sellButton->setTexture(pt,rt);
				sellButton->setSize(167, 59);
				HotSpot::onReleaseDelegate osp;
				osp.bind(this,&UpgradeMenu::onSellReleased);
				sellButton->addOnReleaseHandler(osp);
				
				
			/*	okButton=new GameButton();
				pt=new Texture(batlas,480,106,149,37);
				rt=new Texture(batlas,480,180,149,37);
				
				okButton->setTexture(rt,pt);
				okButton->setSize(149, 37);
				HotSpot::onReleaseDelegate oor;
				oor.bind(this,&UpgradeMenu::onOkReleased);
				okButton->addOnReleaseHandler(oor);*/
				
				
				cancelButton=new GameButton();
				pt=new Texture(batlas,601,293,200,70);
				rt=new Texture(batlas,601,366,200,70);
				
				cancelButton->setTexture(pt,rt);
				cancelButton->setSize(167, 59);
				HotSpot::onReleaseDelegate ocr;
				ocr.bind(this,&UpgradeMenu::onCancelReleased);
				cancelButton->addOnReleaseHandler(ocr);
				
				upgradeButtons[0]=new GameButton();
				pt=new Texture(batlas,601,1,200,70);
				rt=new Texture(batlas,601,74,200,70);
				
				upgradeButtons[0]->setTexture(pt,rt);
				upgradeButtons[0]->setSize(167, 59);
				
				HotSpot::onReleaseDelegate ubap;
				ubap.bind(this,&UpgradeMenu::onTowerAReleased);
				upgradeButtons[0]->addOnReleaseHandler(ubap);
				
				
				upgradeButtons[1]=new GameButton();
				
				pt=new Texture(batlas,601,1,200,70);
				rt=new Texture(batlas,601,74,200,70);
				
				upgradeButtons[1]->setTexture(pt,rt);
				upgradeButtons[1]->setSize(167, 59);
				
				HotSpot::onReleaseDelegate ubbp;
				ubbp.bind(this,&UpgradeMenu::onTowerBReleased);
				upgradeButtons[1]->addOnReleaseHandler(ubbp);
				
				
			/*	upgradeButtons[2]=new GameButton();
				
				pt=new Texture(batlas,480,0,44,53);
				rt=new Texture(batlas,480,53,44,53);
				
				upgradeButtons[2]->setTexture(rt,pt);
				
				HotSpot::onReleaseDelegate ubcp;
				ubcp.bind(this,&UpgradeMenu::onTowerCReleased);
				upgradeButtons[2]->addOnReleaseHandler(ubcp);
*/
				bar=new TextureAnimation(batlas,328,554,96,218,96,218/12);
				
				int k[19]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
				bar->addAnimation(k,12);
				bar->setAnimation(0);
				
				
				moneyDigitTexture=new TextureAnimation(batlas,0,715,130,15,13,15);
				moneyDigitTexture->addAnimation(k,10);
				moneyDigitTexture->setAnimation(0);
				
			};
			
			void onTowerCReleased();
			void onTowerBReleased();
			void onTowerAReleased();
			
			void onSellReleased();
			void onOkReleased();
			
			void onCancelReleased();
			
			void setupUpgradeMenu(Tower *t,int _x,int _y);

			
			void draw();
			
			void handlePressEvent(int _x,int _y);
			void handleReleaseEvent(int _x,int _y);
			void handleMoveEvent(int _x,int _y);
			
		private:
			void prepareDigits(int value,std::deque<int> & digits);
			void drawMoney(int x,int y,std::deque<int> & digits);

		};
	}
}

#endif