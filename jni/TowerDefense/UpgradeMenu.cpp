#include "UpgradeMenu.h"
#include "QuadHelper.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		UpgradeMenu::UpgradeMenu(void):InGameMenu(),sellButton(NULL),cancelButton(NULL),currentChoice(-1),towerx(0),towery(0)
		{
		}

		UpgradeMenu::~UpgradeMenu(void)
		{
			delete bar;
			
			//delete okButton;
			delete sellButton;
			delete cancelButton;
			delete upgradeButtons[0];
			delete upgradeButtons[1];
		//	delete upgradeButtons[2];
		}
		
		void UpgradeMenu::draw()
		{
			int offset=0;
			
			if (isScrollingDown) 
			{
				offset=scrollOffset;
				scrollDown();
				
			}
			
				background->apply();
				QuadHelper::getSingleton().drawQuad(101,21-offset,598,438,background->getCoordinates());
			
			sellButton->setPosition(325+101+125,305-offset+10);
			sellButton->draw();
			
		/*	okButton->setPosition(255, 345-offset);
			okButton->draw();
		*/	
			cancelButton->setPosition(325+101+125, 385-offset);
			cancelButton->draw();
				
				
				sellTowerTexture->apply();
				QuadHelper::getSingleton().drawQuad(85+153,290+21-offset,40,60,sellTowerTexture->getCoordinates());
			
			bar->setAnimationStep(sellPower);
			bar->apply();
			
			QuadHelper::getSingleton().drawQuad(199+153,303+21-offset,74,13,bar->getCoordinates());
			
			
			bar->setAnimationStep(sellRange);
			bar->apply();
			
			QuadHelper::getSingleton().drawQuad(199+153,303+39-offset,74,13,bar->getCoordinates());
			
			
			bar->setAnimationStep(sellSpeed);
			bar->apply();
			
			QuadHelper::getSingleton().drawQuad(199+153,303+57-offset,74,13,bar->getCoordinates());
			
			
			
			
			drawMoney(145+153,174+283-88+21-offset,sellMoneyDigits);
			
				if (upgradeChoices[0]!=-1) 
				{
					upgradeTowerTextures[0]->apply();
					QuadHelper::getSingleton().drawQuad(85+101,78+21-offset,40,60,upgradeTowerTextures[0]->getCoordinates());
					
					upgradeButtons[0]->setPosition(85+100+100, 230-offset);
					upgradeButtons[0]->draw();
					
					
					bar->setAnimationStep(upgradePower[0]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+101,88+21-offset,74,13,bar->getCoordinates());
					
					
					bar->setAnimationStep(upgradeRange[0]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+101,88+39-offset,74,13,bar->getCoordinates());
					
					
					bar->setAnimationStep(upgradeSpeed[0]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+101,88+57-offset,74,13,bar->getCoordinates());
					
					
					drawMoney(145+101,156+21-offset,moneyDigits[0]);
					
				}
				
				if(upgradeChoices[1]!=-1)
				{
					upgradeTowerTextures[1]->apply();
					QuadHelper::getSingleton().drawQuad(101+325,78+21-offset,40,60,upgradeTowerTextures[1]->getCoordinates());
				
					upgradeButtons[1]->setPosition(325+101+105, 230-offset);
					upgradeButtons[1]->draw();
					
					
					bar->setAnimationStep(upgradePower[1]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+244+101,88+21-offset,74,13,bar->getCoordinates());
					
					
					bar->setAnimationStep(upgradeRange[1]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+244+101,88+39-offset,74,13,bar->getCoordinates());
					
					
					bar->setAnimationStep(upgradeSpeed[1]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(199+244+101,88+57-offset,74,13,bar->getCoordinates());
					
					drawMoney(145+244+101,156+21-offset,moneyDigits[1]);
					
				}
				
			/*	if (upgradeTowerTextures[2]!=NULL) 
				{
					upgradeTowerTextures[2]->apply();
					QuadHelper::getSingleton().drawQuad(418,244-offset,40,60,upgradeTowerTextures[2]->getCoordinates());
					
					upgradeButtons[2]->setPosition(603, 280-offset+10);
					upgradeButtons[2]->draw();
					
					bar->setAnimationStep(upgradePower[2]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(331+160,195+80-offset,74,13,bar->getCoordinates());
					
					bar->setAnimationStep(upgradePower[2]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(331+160,175+80-offset,74,13,bar->getCoordinates());
					
					
					bar->setAnimationStep(upgradeRange[2]);
					bar->apply();
					
					QuadHelper::getSingleton().drawQuad(331+160,217+80-offset,74,13,bar->getCoordinates());
					
					
					drawMoney(430+160,165+80,moneyDigits[2]);
				}
				
			
				*/
				
			

			
			
			
		}
		
		void UpgradeMenu::drawMoney(int x,int y,std::deque<int> & digits)
		{
			int currentx=x;
			int currenty=y;
			
			for (std::deque<int>::iterator iter=digits.begin(); iter!=digits.end(); ++iter) {
				moneyDigitTexture->setAnimationStep(*iter);
				moneyDigitTexture->apply();
				
				QuadHelper::getSingleton().drawQuad(currentx,y,13,15,moneyDigitTexture->getCoordinates());
				
				currentx+=13;
			}
		}
		
		void UpgradeMenu::setupUpgradeMenu(Tower *t,int _x,int _y)
		{
			
			towerx=_x;
			towery=_y;
			
			int towerType=t->getTowerType();
			
			sellTowerTexture=towerTextures[towerType];
			sellMoney=Tower::getSellMoney(towerType);
			sellSpeed=11-Tower::getSpeed(towerType)/5.0*11;
			sellPower=11-Tower::getPower(towerType)/1000*11;
			sellRange=11-Tower::getRange(towerType)/40000*11;
			
			 
			
			Tower::getUpgradeChoices(t->getTowerType(),upgradeChoices);
			
			for (int i=0; i<2; ++i) 
			{
				if (upgradeChoices[i]!=-1) 
				{
					upgradeTowerTextures[i]=towerTextures[upgradeChoices[i]];
					upgradeMoney[i]=Tower::getSellMoney(upgradeChoices[i]);
					upgradeSpeed[i]=Tower::getSellMoney(upgradeChoices[i]);
					upgradePower[i]=Tower::getSellMoney(upgradeChoices[i]);
					
					upgradePower[i]=11-Tower::getPower(upgradeChoices[i])/1000*11;
					
					upgradeRange[i]=11-Tower::getRange(upgradeChoices[i])/40000*11;
					
					upgradeSpeed[i]=11-Tower::getSpeed(upgradeChoices[i])/5.0f*11;
					
					upgradeMoney[i]=Tower::getTowerCost(upgradeChoices[i]);
					
					prepareDigits(upgradeMoney[i],moneyDigits[i]);
				}
			}
			
			currentChoice=-1;
			sellButton->setStatus(0);
			upgradeButtons[1]->setStatus(0);
			upgradeButtons[0]->setStatus(0);
			
			
	
			
			prepareDigits(sellMoney,sellMoneyDigits);
		
			
			
		

			
		};
		
		void UpgradeMenu::prepareDigits(int value,std::deque<int> & digits)
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
		
		
	/*	void UpgradeMenu::onTowerCReleased()
		{
			//currentChoice=2;
			currentChoice=2;
			sellButton->setStatus(0);
			upgradeButtons[0]->setStatus(0);
			upgradeButtons[1]->setStatus(0);
			upgradeButtons[2]->setStatus(1);
		}
	*/	
		void UpgradeMenu::onTowerBReleased()
		{
			currentChoice=1;
			
			if (currentChoice>=0 && currentChoice<4) {
				switch (currentChoice) 
				{
					case 3:
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,-1);
						}
						break;
					default:
						//	printf("on ok 1.5\n");
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,upgradeChoices[currentChoice]);
						}
						break;
				}
			}
		}
		
		void UpgradeMenu::onTowerAReleased()
		{
			
		//	currentChoice=0;
			currentChoice=0;
			if (currentChoice>=0 && currentChoice<4) {
				switch (currentChoice) 
				{
					case 3:
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,-1);
						}
						break;
					default:
						//	printf("on ok 1.5\n");
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,upgradeChoices[currentChoice]);
						}
						break;
				}
			}
			
		}
		
		void UpgradeMenu::onSellReleased()
		{
			currentChoice=3;
			if (currentChoice>=0 && currentChoice<4) {
				switch (currentChoice) 
				{
					case 3:
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,-1);
						}
						break;
					default:
						//	printf("on ok 1.5\n");
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,upgradeChoices[currentChoice]);
						}
						break;
				}
			}
		}
		
		void UpgradeMenu::onOkReleased()
		{
			
		//	onOk();
		}
		
		void UpgradeMenu::onCancelReleased()
		{
			onCancel();
		}
		
	/*	void UpgradeMenu::onOk()
		{
			
		//	printf("on ok\n");
			if (currentChoice>=0 && currentChoice<4) {
				switch (currentChoice) 
				{
					case 3:
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,-1);
						}
						break;
					default:
					//	printf("on ok 1.5\n");
						for (std::vector<onOkDelegate>::iterator iter=onOkDelegateList.begin(); iter!=onOkDelegateList.end(); ++iter) 
						{
							(*iter)(towerx,towery,upgradeChoices[currentChoice]);
						}
						break;
				}
			}
		}*/
		
		void UpgradeMenu::handlePressEvent(int _x,int _y)
		{
			if (!isScrollingDown) 
			{
				if (sellButton->handlePressEvent(_x, _y)) {
					
				}
			/*	else if(okButton->handlePressEvent(_x, _y))
				{
					
				}
			*/	else if(cancelButton->handlePressEvent(_x, _y))
				{
				
				}
				else if(upgradeChoices[0] && upgradeButtons[0]->handlePressEvent(_x, _y)) {
						
					
				}
				else if(upgradeChoices[1] && upgradeButtons[1]->handlePressEvent(_x, _y)) {
						
					
				}
				
			


			}
		}
		
		
		void UpgradeMenu::handleReleaseEvent(int _x,int _y)
		{
			if (!isScrollingDown) 
			{
				if (sellButton->handleReleaseEvent(_x, _y)) {
					
				}
			/*	else if(okButton->handleReleaseEvent(_x, _y))
				{
					
				}
			*/	else if(cancelButton->handleReleaseEvent(_x, _y))
				{
					
				}
				else if(upgradeChoices[0] &&
					upgradeButtons[0]->handleReleaseEvent(_x, _y)) 
				{
						
					}
				
				else if(upgradeChoices[1] && upgradeButtons[1]->handleReleaseEvent(_x, _y)) {
						
					
				}
			
				
				
			}
		}
		
		void UpgradeMenu::handleMoveEvent(int _x,int _y){}
	}
}