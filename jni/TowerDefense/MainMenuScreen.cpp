/*
 *  MainMenuScreen.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/16/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "MainMenuScreen.h"

#ifdef __ANDROID__
#include "AndroidControlManager.h"
#endif

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void MainMenuScreen::draw()
		{
			mainMenuBackground->apply();
			QuadHelper::getSingleton().drawQuad(0,0,800,480,mainMenuBackground->getCoordinates());
			gameButton->draw();
			aboutButton->draw();
			
			if(isQuiting)
			{
				quitDialog->draw();
			}
		};
		
		void MainMenuScreen::handlePressEvent(int _x,int _y)
		{
			if (isQuiting) {
				(quitDialog->handlePressEvent(_x, _y));
			}
			else
			if (gameButton->handlePressEvent(_x, _y)) 
			{
				return;
			}
			
			else if(aboutButton->handlePressEvent(_x, _y))
			{
				return;
			}
		}
		
		void MainMenuScreen::handleReleaseEvent(int _x,int _y)
		{
			if (isQuiting) {
				(quitDialog->handleReleaseEvent(_x, _y)) ;
			}else
			if(gameButton->handleReleaseEvent(_x, _y))
			{
				return;
			}
			
			else if(aboutButton->handleReleaseEvent(_x, _y))
			{
				return;
			}
		}
		
		MainMenuScreen::~MainMenuScreen()
		{
			delete gameButton;
			delete aboutButton;
			delete quitDialog;
			delete mainMenuBackground;
		}
		
		void MainMenuScreen::renew()
		{
			gameButton->beginLoadingAnimation(1.0f, 0.05f);
			aboutButton->beginLoadingAnimation(6.0f, 0.05f);
		}
		
		MainMenuScreen::MainMenuScreen():Screen(),mainMenuBackground(0),isQuiting(false)
		{
			//LOGI("main menu 0");
			
#ifdef __ANDROID__
			int mainMenuScreenAtlas=TextureAtlasManager::getSingleton().addNew("mainmenu.png");
#else 
			
			int mainMenuScreenAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/mainmenu.png");
#endif
		//	LOGI("main menu 1");
			mainMenuBackground=new Texture(mainMenuScreenAtlas,0,0,800,480);
			
		//	LOGI("main menu 2");
			gameButton=new MainMenuButton(200,71);
			aboutButton=new MainMenuButton(200,71);
			
		//	LOGI("main menu 3");
			Texture *gameButtonTexture=new Texture(mainMenuScreenAtlas,801,1,200,71);
			Texture *aboutButtonTexture=new Texture(mainMenuScreenAtlas,801,147,200,71);
			
		//	LOGI("main menu 4");
			Texture *gameButtonPressedTexture=new Texture(mainMenuScreenAtlas,801,74,200,71);
			Texture *aboutButtonPressedTexture=new Texture(mainMenuScreenAtlas,801,220,200,71);
			
		//	LOGI("main menu 5");
			gameButton->addAnimation(gameButtonTexture);
			gameButton->addAnimation(gameButtonPressedTexture);
			aboutButton->addAnimation(aboutButtonTexture);
			aboutButton->addAnimation(aboutButtonPressedTexture);
			
		//	LOGI("main menu 6");
			gameButton->setPosition(570, 300);
			gameButton->beginLoadingAnimation(1.0f, 0.05f);
			aboutButton->setPosition(570, 373);
			aboutButton->beginLoadingAnimation(6.0f, 0.05f);
			
		//	LOGI("main menu 7");
			
			HotSpot::onPressDelegate mPressed;
			mPressed.bind(this,&MainMenuScreen::gameButtonPressed);
			gameButton->addOnPressHandler(mPressed);
			
		//	LOGI("main menu 8");
			HotSpot::onReleaseDelegate mReleased;
			mReleased.bind(this,&MainMenuScreen::gameButtonReleased);
			gameButton->addOnReleaseHandler(mReleased);
			
			HotSpot::onReleaseDelegate ard;
			ard.bind(this,&MainMenuScreen::onHelpReleased);
			aboutButton->addOnReleaseHandler(ard);
			
		//	LOGI("main menu 9");
			
			quitDialog=new QuitDialog();
			
		//	LOGI("main menu 10");
			Screen::onBackDelegate obd;
			obd.bind(this,&MainMenuScreen::onBack);
			addBackEventHandler(obd);
			
		//	LOGI("main menu 11");
			
			QuitDialog::onYesDelegate oyd;
			oyd.bind(this,&MainMenuScreen::onQuitYes);
			quitDialog->addOnYesHandler(oyd);
			
		//	LOGI("main menu 12");
			QuitDialog::onNoDelegate ond;
			ond.bind(this,&MainMenuScreen::onQuitNo);
			quitDialog->addOnNoHandler(ond);
			
		//	LOGI("main menu 13");
		}
		
		void MainMenuScreen::onHelpReleased()
		{
#ifdef __ANDROID__
			AndroidControlManager::getSingleton().showHelpDialog();
#endif
		}

		
		void MainMenuScreen::onQuitYes()
		{
			isQuiting=false;
			onExit();
		}
		
		void MainMenuScreen::onQuitNo()
		{
			isQuiting=false;
		}
		
		void MainMenuScreen::onBack()
		{
			isQuiting=true;
			quitDialog->beginScrollingDown(200);
		}
		
		void MainMenuScreen::gameButtonReleased()
		{
			for (std::vector<onGameDelegate>::iterator iter=gameButtonDelegateList.begin(); iter!=gameButtonDelegateList.end(); iter++) 
			{
				(*iter)();
			}
		}
	}
}