/*
 *  EnemyFactory.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "EnemyFactory.h"
#include "Game.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		Enemy* EnemyFactory::querryForAnEnemy()
		{
			if (isBeginEnemy==false) 
			{
				countDown();
			}	
			else
			{
			
				double newTime=GameTimeManager::getSingleton().getCurrentTime();
			
				if(newTime-oldTime>0.5)
				{
					oldTime=oldTime+0.5;
				
					if(isBeginEnemy && currentWave!=NULL)
					{
						Enemy *e=currentWave->nextEnemy();
					
						if(e!=NULL)
						{
							printf("generate an enemy\n");
							return e;
						}
						else
						{
							beginWave();
						
						}
					
					}
				
					isBeginEnemy=false;
					currentWave=NULL;
				
					return NULL;
				}
			
			}
			
			return NULL;
		}
		
		
		void EnemyFactory::countDown()
		{
			if(isBeginEnemy==false && waveQueue.empty()==false)
			{
				countDownNewTime=GameTimeManager::getSingleton().getCurrentTime();
				waveQueue.front()->waitTime-=countDownNewTime-countDownOldTime;
				countDownOldTime=countDownNewTime;
				
				NextWaveBar::getSingleton().setVisible(true);
				NextWaveBar::getSingleton().setTime(waveQueue.front()->waitTime);
				
				if(waveQueue.front()->waitTime<=0)
				{
					if (currentWave) 
					{
						delete currentWave;
					}
					
					currentWave=waveQueue.front();
					isBeginEnemy=true;
					oldTime=GameTimeManager::getSingleton().getCurrentTime();
					
					NextWaveBar::getSingleton().setVisible(false);
					waveQueue.pop();
					
					NextWaveBar::getSingleton().setCurrentWave(overallWaveCount-waveQueue.size());
				}
			}
		}
		
		Enemy * EnemyFactory::getEnemyByType(int type)
		{
			
#ifdef __ANDROID__
			int walkableAtlas=TextureAtlasManager::getSingleton().addNew("walkable.png");
			int airAtlas=TextureAtlasManager::getSingleton().addNew("air.png");
			int atlas=TextureAtlasManager::getSingleton().addNew("ground.png");
			
#else
			int walkableAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/walkable.png");
			int airAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/air.png");
			int atlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/ground.png");
#endif
			switch (type) 
			{
					
				case 0:
				{
					WalkableEnemy *aTestEnemyn2=new WalkableEnemy();
					TextureAnimation *tan2=new TextureAnimation(walkableAtlas,0,120,480,80,40,40);
					
					int k1n2[4]={20,21,22,23}; //up
					int k2n2[4]={8,9,10,11}; //down 
					int k3n2[4]={12,13,14,15}; //left
					int k4n2[4]={16,17,18,19}; //right
					
					tan2->addAnimation(k1n2, 4);
					tan2->addAnimation(k2n2, 4);
					tan2->addAnimation(k3n2, 4);
					tan2->addAnimation(k4n2, 4);
					
					aTestEnemyn2->setTextureIndices(tan2);
					
					aTestEnemyn2->setSize(TileSize,TileSize);
					aTestEnemyn2->setAnimation(0);
					aTestEnemyn2->setFullHealth(100);
					aTestEnemyn2->setSpeed(0.04f);
					aTestEnemyn2->setExplosionType(14);
					aTestEnemyn2->setMoney(1);
					return aTestEnemyn2;
				}
				break;
					
				case 1:
				{
					WalkableEnemy *aTestEnemyn1=new WalkableEnemy();
					TextureAnimation *tan1=new TextureAnimation(walkableAtlas,0,40,480,80,40,40);
					
					int k1n1[4]={12,13,14,15}; //up
					int k2n1[4]={0,1,2,3}; //down 
					int k3n1[4]={4,5,6,7}; //left
					int k4n1[4]={8,9,10,11}; //right
					
					tan1->addAnimation(k1n1, 4);
					tan1->addAnimation(k2n1, 4);
					tan1->addAnimation(k3n1, 4);
					tan1->addAnimation(k4n1, 4);
					
					aTestEnemyn1->setTextureIndices(tan1);
					
					aTestEnemyn1->setSize(TileSize,TileSize);
					aTestEnemyn1->setAnimation(0);
					aTestEnemyn1->setFullHealth(130);
					aTestEnemyn1->setSpeed(0.04f);
					aTestEnemyn1->setMoney(2);
					aTestEnemyn1->setExplosionType(14);//13
					return aTestEnemyn1;
				}
				break;	
					
					
				case 2:
				{
					WalkableEnemy *aTestEnemyn3=new WalkableEnemy();
					TextureAnimation *tan3=new TextureAnimation(walkableAtlas,0,80,480,80,40,40);
					
					int k1n3[4]={16,17,18,19}; //up
					int k2n3[4]={4,5,6,7}; //down 
					int k3n3[4]={8,9,10,11}; //left
					int k4n3[4]={12,13,14,15}; //right
					
					tan3->addAnimation(k1n3, 4);
					tan3->addAnimation(k2n3, 4);
					tan3->addAnimation(k3n3, 4);
					tan3->addAnimation(k4n3, 4);
					
					aTestEnemyn3->setTextureIndices(tan3);
					
					aTestEnemyn3->setSize(TileSize,TileSize);
					aTestEnemyn3->setAnimation(0);
					
					aTestEnemyn3->setFullHealth(282);
					aTestEnemyn3->setSpeed(0.02f);
					aTestEnemyn3->setExplosionType(14);
					aTestEnemyn3->setMoney(6);
					
					return aTestEnemyn3;
				}
				break;

				case 3:
				{
					Enemy *aTestEnemy1=new Enemy();
					aTestEnemy1->setTextureIndices(getAEnemyTexture(atlas,1), getAEnemyTexture(atlas,0), getAEnemyTexture(atlas,2), getAEnemyTexture(atlas,3));
					aTestEnemy1->setAnimation(0);
					aTestEnemy1->setSize(TileSize,TileSize);
					aTestEnemy1->setFullHealth(200);
					aTestEnemy1->setSpeed(0.05f);
					aTestEnemy1->setExplosionType(0);
					aTestEnemy1->setMoney(4);
					return aTestEnemy1;
				}
				break;
					
				case 4:
				{
					Enemy *aTestEnemy2=new Enemy();
					aTestEnemy2->setTextureIndices(getAEnemyTexture(atlas,5), getAEnemyTexture(atlas, 4), getAEnemyTexture( atlas,  6), getAEnemyTexture(atlas, 7));
					aTestEnemy2->setAnimation(0);
					aTestEnemy2->setSize(TileSize,TileSize);
					aTestEnemy2->setFullHealth(240);
					aTestEnemy2->setSpeed(0.05f);
					aTestEnemy2->setExplosionType(2);
					aTestEnemy2->setMoney(4);
					return aTestEnemy2;
				}
				break;
					
				case 5:
				{
					Enemy *aTestEnemy3=new Enemy();
					aTestEnemy3->setTextureIndices( getAEnemyTexture(atlas,9), getAEnemyTexture(atlas,8), getAEnemyTexture(atlas,10),getAEnemyTexture(atlas,11));
					aTestEnemy3->setAnimation(0);
					aTestEnemy3->setSize(TileSize,TileSize);
					aTestEnemy3->setFullHealth(260);
					aTestEnemy3->setSpeed(0.06f);
					aTestEnemy3->setExplosionType(3);
					aTestEnemy3->setMoney(5);
					
					return aTestEnemy3;
				}
				break;
					
				case 6:
				{
					Enemy *aTestEnemy4=new Enemy();
					aTestEnemy4->setTextureIndices( getAEnemyTexture(atlas,13),getAEnemyTexture(atlas,12),getAEnemyTexture(atlas, 14), getAEnemyTexture(atlas,15));
					aTestEnemy4->setAnimation(0);
					aTestEnemy4->setSize(TileSize,TileSize);
					aTestEnemy4->setFullHealth(290);
					aTestEnemy4->setSpeed(0.065f);
					aTestEnemy4->setExplosionType(4);
					aTestEnemy4->setMoney(6);
					return aTestEnemy4;
				
				}
				break;
					
				case 7:
				{
					Enemy *aTestEnemy5=new Enemy();
					aTestEnemy5->setTextureIndices( getAEnemyTexture(atlas,17),getAEnemyTexture(atlas,16), getAEnemyTexture(atlas,18), getAEnemyTexture(atlas,19));
					aTestEnemy5->setAnimation(0);
					aTestEnemy5->setSize(TileSize,TileSize);
					
					aTestEnemy5->setFullHealth(300);
					aTestEnemy5->setSpeed(0.7f);
					aTestEnemy5->setExplosionType(5);
					aTestEnemy5->setMoney(7);
					return aTestEnemy5;
				}
				break;
					
				case 8:
				{
					Enemy *aTestEnemy6=new Enemy();
					aTestEnemy6->setTextureIndices( getAEnemyTexture(atlas, 21), getAEnemyTexture(atlas,20),getAEnemyTexture(atlas, 22), getAEnemyTexture(atlas,23));
					aTestEnemy6->setAnimation(0);
					aTestEnemy6->setSize(TileSize,TileSize);
					aTestEnemy6->setFullHealth(325);
					aTestEnemy6->setSpeed(0.07f);
					aTestEnemy6->setExplosionType(6);
					aTestEnemy6->setMoney(8);
					return aTestEnemy6;
				}
				break;
					
				case 9:
				{
					Enemy *aTestEnemy7=new Enemy();
					aTestEnemy7->setTextureIndices(getAEnemyTexture(atlas, 25), getAEnemyTexture(atlas, 24), getAEnemyTexture(atlas, 26), getAEnemyTexture(atlas, 26));
					aTestEnemy7->setAnimation(0);
					aTestEnemy7->setSize(TileSize,TileSize);
					aTestEnemy7->setFullHealth(350);
					aTestEnemy7->setSpeed(0.06f);
					aTestEnemy7->setExplosionType(7);
					aTestEnemy7->setMoney(8);
					return aTestEnemy7;
				}
				break;
					
				case 10:
				{
					Enemy *aTestEnemy8=new Enemy();
					aTestEnemy8->setTextureIndices(getAEnemyTexture(atlas, 29),getAEnemyTexture(atlas,  28), getAEnemyTexture(atlas, 30), getAEnemyTexture(atlas, 31));
					aTestEnemy8->setAnimation(0);
					aTestEnemy8->setSize(TileSize,TileSize);
					aTestEnemy8->setFullHealth(400);
					aTestEnemy8->setSpeed(0.06f);
					aTestEnemy8->setExplosionType(8);
					aTestEnemy8->setMoney(9);
					return aTestEnemy8;
				}
				break;
					
				case 11:
				{
					Enemy *aTestEnemy9=new Enemy();
					aTestEnemy9->setTextureIndices(getAEnemyTexture(atlas, 33), getAEnemyTexture(atlas, 32),getAEnemyTexture( atlas, 34), getAEnemyTexture(atlas, 35));
					aTestEnemy9->setAnimation(0);
					aTestEnemy9->setSize(TileSize,TileSize);
					aTestEnemy9->setExplosionType(9);
					aTestEnemy9->setFullHealth(420);
					aTestEnemy9->setSpeed(0.04f);
					aTestEnemy9->setMoney(10);
					return aTestEnemy9;
				}
				break;
					
				case 12:
				{
					Enemy *aTestEnemy10=new Enemy();
					aTestEnemy10->setTextureIndices(getAEnemyTexture(atlas, 37),getAEnemyTexture(atlas, 36), getAEnemyTexture(atlas, 38),getAEnemyTexture( atlas, 39));
					aTestEnemy10->setAnimation(0);
				aTestEnemy10->setSize(TileSize,TileSize);
					aTestEnemy10->setExplosionType(10);
					aTestEnemy10->setFullHealth(425);
					aTestEnemy10->setSpeed(0.08f);
					aTestEnemy10->setMoney(11);
					return aTestEnemy10;
				}
				break;
					
				case 13:
				{
					Enemy *aTestEnemy11=new Enemy();
					aTestEnemy11->setTextureIndices(getAEnemyTexture(atlas, 41),getAEnemyTexture(atlas, 40),getAEnemyTexture( atlas, 42), getAEnemyTexture(atlas, 43));
					aTestEnemy11->setAnimation(0);
					aTestEnemy11->setSize(TileSize,TileSize);
					aTestEnemy11->setExplosionType(11);
					aTestEnemy11->setFullHealth(450);
					aTestEnemy11->setSpeed(0.05f);
					aTestEnemy11->setMoney(15);
					return aTestEnemy11;
				}
				break;
					
				case 14:
				{
					AirEnemy *aTestEnemy12=new AirEnemy();
					aTestEnemy12->setTextureIndices(getAirEnemyTexture(airAtlas,1),getAirEnemyTexture(airAtlas, 0),getAirEnemyTexture(airAtlas, 2),getAirEnemyTexture(airAtlas, 3));
					
					aTestEnemy12->setAnimation(0);
					aTestEnemy12->setSize(TileSize,TileSize);
					aTestEnemy12->setExplosionType(12);
					aTestEnemy12->setFullHealth(200);
					aTestEnemy12->setSpeed(0.074f);
					aTestEnemy12->setMoney(7);
					return aTestEnemy12;
				}
				break;
					
				case 15:
				{
					AirEnemy *aTestEnemy13=new AirEnemy();
					aTestEnemy13->setTextureIndices(getAirEnemyTexture(airAtlas,5), getAirEnemyTexture(airAtlas,4), getAirEnemyTexture(airAtlas,6), getAirEnemyTexture(airAtlas,7));
					
					aTestEnemy13->setAnimation(0);
					aTestEnemy13->setSize(TileSize,TileSize);
					aTestEnemy13->setExplosionType(13);
					
					aTestEnemy13->setFullHealth(190);
					aTestEnemy13->setSpeed(0.09f);
					aTestEnemy13->setMoney(9);
					return aTestEnemy13;
				}
				break;
					
				case 16:
				{
					AirEnemy *aTestEnemy14=new AirEnemy();
					aTestEnemy14->setTextureIndices(getAirEnemyTexture(airAtlas,9),getAirEnemyTexture(airAtlas, 8), getAirEnemyTexture(airAtlas,10), getAirEnemyTexture(airAtlas,11));
					
					aTestEnemy14->setAnimation(0);
					aTestEnemy14->setSize(TileSize,TileSize);
					aTestEnemy14->setExplosionType(14);
					
					aTestEnemy14->setFullHealth(220);
					aTestEnemy14->setSpeed(0.1f);
					aTestEnemy14->setMoney(11);
					return aTestEnemy14;
				}
				break;
					
				case 17:
				{
					AirEnemy *aTestEnemy15=new AirEnemy();
					aTestEnemy15->setTextureIndices(getAirEnemyTexture(airAtlas,13), getAirEnemyTexture(airAtlas,12), getAirEnemyTexture(airAtlas,14), getAirEnemyTexture(airAtlas,15));
					
					aTestEnemy15->setAnimation(0);
					aTestEnemy15->setSize(TileSize,TileSize);
					aTestEnemy15->setExplosionType(15);
					
					aTestEnemy15->setFullHealth(300);
					aTestEnemy15->setSpeed(0.11f);
					aTestEnemy15->setMoney(13);
					return aTestEnemy15;
				}
				break;
					
				case 18:
				{
					AirEnemy *aTestEnemy16=new AirEnemy();
					aTestEnemy16->setTextureIndices(getAirEnemyTexture(airAtlas,17),getAirEnemyTexture(airAtlas, 16),getAirEnemyTexture(airAtlas, 18),getAirEnemyTexture(airAtlas, 19));
					
					aTestEnemy16->setAnimation(0);
					aTestEnemy16->setSize(TileSize,TileSize);
					aTestEnemy16->setExplosionType(16);
					
					aTestEnemy16->setFullHealth(1900);
					aTestEnemy16->setSpeed(0.28f);
					aTestEnemy16->setMoney(28);
					return aTestEnemy16;
				}
				break;
					
				case 19:
				{
					WalkableEnemy *aTestEnemy17=new WalkableEnemy();
					TextureAnimation *ta=new TextureAnimation(walkableAtlas,0,0,480,40,40,40);
					
					int k1[3]={3,4,5};
					int k2[3]={0,1,2};
					int k3[3]={6,7,8};
					int k4[3]={9,10,11};
					
					ta->addAnimation(k1, 3);
					ta->addAnimation(k2, 3);
					ta->addAnimation(k3, 3);
					ta->addAnimation(k4, 3);
					
					aTestEnemy17->setTextureIndices(ta);
					aTestEnemy17->setExplosionType(17);
					
					aTestEnemy17->setSize(TileSize,TileSize);
					aTestEnemy17->setAnimation(0);
					
					aTestEnemy17->setFullHealth(1000);
					aTestEnemy17->setSpeed(0.04f);
					aTestEnemy17->setMoney(20);
					return aTestEnemy17;
				}
				break;
								
				case 20:
				{
					WalkableEnemy *aTestEnemyn4=new WalkableEnemy();
					TextureAnimation *tan4=new TextureAnimation(walkableAtlas,0,200,480,80,40,40);
					
					int k1n4[4]={12,13,14,15}; //up
					int k2n4[4]={4,5,6,7}; //down 
					int k3n4[4]={8,9,10,11}; //left
					int k4n4[4]={0,1,2,3}; //right
					
					tan4->addAnimation(k1n4, 4);
					tan4->addAnimation(k2n4, 4);
					tan4->addAnimation(k3n4, 4);
					tan4->addAnimation(k4n4, 4);
					
					aTestEnemyn4->setTextureIndices(tan4);
					
					aTestEnemyn4->setSize(TileSize,TileSize);
					aTestEnemyn4->setAnimation(0);
					aTestEnemyn4->setFullHealth(750);
					aTestEnemyn4->setSpeed(0.08f);
					aTestEnemyn4->setExplosionType(13);
					aTestEnemyn4->setMoney(15);
					return aTestEnemyn4;
				}
				break;
					
					
				case 21:
				{
					WalkableEnemy *aTestEnemyn5=new WalkableEnemy();
					TextureAnimation *tan5=new TextureAnimation(walkableAtlas,0,240,480,200,40,40);
					
					int k1n5[12]={16,17,18,19,20,21,22,23,24,25,26,27}; //up
					int k2n5[12]={40,41,42,43,44,45,46,47,48,49,50,51}; //down 
					int k4n5[12]={4,5,6,7,8,9,10,11,12,13,14,15}; //left
					int k3n5[12]={28,29,30,31,32,33,34,35,36,37,38,39}; //right
					
					tan5->addAnimation(k1n5, 12);
					tan5->addAnimation(k2n5, 12);
					tan5->addAnimation(k3n5, 12);
					tan5->addAnimation(k4n5, 12);
					
					aTestEnemyn5->setTextureIndices(tan5);
					
					aTestEnemyn5->setSize(TileSize,TileSize);
					aTestEnemyn5->setAnimation(0);
					aTestEnemyn5->setFullHealth(2500);
					aTestEnemyn5->setSpeed(0.05f);
					aTestEnemyn5->setExplosionType(12);
					aTestEnemyn5->setMoney(25);
					return aTestEnemyn5;
				}
				break;
					
				default:
					break;
			}
		}
		
		void EnemyFactory::initWavesFromFile(FILE *fp)
		{
		/*	Wave *aTestWave=new Wave();
			
			aTestWave->setWaitTime(30);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave->insertAnEnemy(getEnemyByType(1));
			}
		*/
			
			/*	
			for (int i=0; i<5; ++i) 
			{
				aTestWave->insertAnEnemy(getEnemyByType(0));
			}
			
			Wave *aTestWave2=new Wave();
			aTestWave2->setWaitTime(10);
		
			
			for (int i=0; i<5; ++i) 
			{
				aTestWave2->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<3; ++i) 
			{
				aTestWave2->insertAnEnemy(getEnemyByType(0));
			}
			
			for (int i=0; i<2; ++i) 
			{
				aTestWave2->insertAnEnemy(getEnemyByType(2));
			}
			
			Wave *aTestWave3=new Wave();
			aTestWave3->setWaitTime(10);
			
			for (int i=0; i<5; ++i) 
			{
				aTestWave3->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave3->insertAnEnemy(getEnemyByType(3));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave3->insertAnEnemy(getEnemyByType(4));
			}
			
			Wave *aTestWave4=new Wave();
			aTestWave4->setWaitTime(10);
			
			for (int i=0; i<5; ++i) 
			{
				aTestWave4->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave4->insertAnEnemy(getEnemyByType(3));
			}
			
			for (int i=0; i<5; ++i) {
				aTestWave4->insertAnEnemy(getEnemyByType(4));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave4->insertAnEnemy(getEnemyByType(5));
			}
			
			
			Wave *aTestWave5=new Wave();
			aTestWave5->setWaitTime(10);
			
			for (int i=0; i<6; ++i) 
			{
				aTestWave5->insertAnEnemy(getEnemyByType(0));
			}
			
			for (int i=0; i<20; ++i) {
				aTestWave5->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave5->insertAnEnemy(getEnemyByType(4));
			}
			
			
			Wave *aTestWave6=new Wave();
			aTestWave6->setWaitTime(10);
			
			for (int i=0; i<15; ++i) 
			{
				aTestWave6->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<14; ++i) {
				aTestWave6->insertAnEnemy(getEnemyByType(0));
			}
			
			for (int i=0; i<7; ++i) {
				aTestWave6->insertAnEnemy(getEnemyByType(6));
			}
			
			
			
			Wave *aTestWave7=new Wave();
			aTestWave7->setWaitTime(10);
			
			for (int i=0; i<5; ++i) 
			{
				aTestWave7->insertAnEnemy(getEnemyByType(4));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave7->insertAnEnemy(getEnemyByType(5));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave7->insertAnEnemy(getEnemyByType(6));
			}
			
			
			Wave *aTestWave8=new Wave();
			aTestWave8->setWaitTime(10);
			
			for (int i=0; i<25; ++i) 
			{
				aTestWave8->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<25; ++i) {
				aTestWave8->insertAnEnemy(getEnemyByType(0));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave8->insertAnEnemy(getEnemyByType(7));
			}
			
			
			Wave *aTestWave9=new Wave();
			aTestWave9->setWaitTime(10);
			
			for (int i=0; i<15; ++i) 
			{
				aTestWave9->insertAnEnemy(getEnemyByType(1));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave9->insertAnEnemy(getEnemyByType(3));
			}
			
			for (int i=0; i<24; ++i) {
				aTestWave9->insertAnEnemy(getEnemyByType(6));
			}
			
			
			Wave *aTestWave10=new Wave();
			aTestWave10->setWaitTime(10);
			
			for (int i=0; i<5; ++i) 
			{
				aTestWave10->insertAnEnemy(getEnemyByType(7));
			}
			
			for (int i=0; i<4; ++i) {
				aTestWave10->insertAnEnemy(getEnemyByType(8));
			}
			
			for (int i=0; i<40; ++i) {
				aTestWave10->insertAnEnemy(getEnemyByType(0));
			}
			
			Wave *aTestWave11=new Wave();
			aTestWave11->setWaitTime(10);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave11->insertAnEnemy(getEnemyByType(9));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave11->insertAnEnemy(getEnemyByType(10));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave11->insertAnEnemy(getEnemyByType(11));
			}
			
			Wave *aTestWave12=new Wave();
			aTestWave12->setWaitTime(10);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave12->insertAnEnemy(getEnemyByType(12));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave12->insertAnEnemy(getEnemyByType(13));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave12->insertAnEnemy(getEnemyByType(14));
			}
			
			Wave *aTestWave13=new Wave();
			aTestWave13->setWaitTime(10);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave13->insertAnEnemy(getEnemyByType(15));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave13->insertAnEnemy(getEnemyByType(16));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave13->insertAnEnemy(getEnemyByType(17));
			}
			
			
			Wave *aTestWave14=new Wave();
			aTestWave14->setWaitTime(10);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave14->insertAnEnemy(getEnemyByType(18));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave14->insertAnEnemy(getEnemyByType(19));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave14->insertAnEnemy(getEnemyByType(20));
			}
			
			
			Wave *aTestWave15=new Wave();
			aTestWave15->setWaitTime(10);
			
			for (int i=0; i<10; ++i) 
			{
				aTestWave15->insertAnEnemy(getEnemyByType(21));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave15->insertAnEnemy(getEnemyByType(0));
			}
			
			for (int i=0; i<10; ++i) {
				aTestWave15->insertAnEnemy(getEnemyByType(1));
			}
			*/
			
		//	waveQueue.push(aTestWave);
		/*	waveQueue.push(aTestWave2);
			waveQueue.push(aTestWave3);
			waveQueue.push(aTestWave4);
			waveQueue.push(aTestWave5);
			waveQueue.push(aTestWave6);
			waveQueue.push(aTestWave7);
			waveQueue.push(aTestWave8);
			waveQueue.push(aTestWave9);
			waveQueue.push(aTestWave10);
			waveQueue.push(aTestWave11);
			waveQueue.push(aTestWave12);
			waveQueue.push(aTestWave13);
			waveQueue.push(aTestWave14);
			waveQueue.push(aTestWave15);*/
			
			
			int wavecount=0;
			fread(&wavecount, sizeof(int), 1, fp);
			
			//printf("wave count:%d\n",wavecount);
			
			for (int i=0; i<wavecount; ++i) 
			{
				Wave *atestwave=new Wave();
				
				int time=0;
				fread(&time, sizeof(int), 1, fp);
				int enemycount=0;
				fread(&enemycount, sizeof(int), 1,fp );
				atestwave->setWaitTime((double)time);
				
			//	printf("wait time:%d    enemy count: %d\n",time,enemycount);
				for (int e=0; e<enemycount; ++e) 
				{
					int etype=0;
					fread(&etype, sizeof(int), 1, fp);
					atestwave->insertAnEnemy(getEnemyByType(etype));
				}
				waveQueue.push(atestwave);
			}
			
			overallWaveCount=waveQueue.size();
			
			NextWaveBar::getSingleton().setCurrentWave(1);

			NextWaveBar::getSingleton().setOverallWave(overallWaveCount);
		}
		
		double EnemyFactory::queryForNextWaveTime()
		{
			if(!isBeginEnemy && waveQueue.size()>0)
				return (double) waveQueue.front()->waitTime;
			else
				return -1;
		}
		
		Texture * EnemyFactory::getAEnemyTexture(int atlas,int _id)
		{
			//get ground ...
			int h=_id%12;
			int v=_id/12;
			
			return new Texture(atlas,h*40,v*40,40,40);
		}
		
		Texture *EnemyFactory::getAirEnemyTexture(int atlas,int _id)
		{
			int h=_id%12;
			int v=_id/12;
			
			return new Texture(atlas,h*40,v*80,40,80);
		}
		
		void EnemyFactory::setStartingPositions(std::vector<PointI> & inputStartingPositions)
		{
			for(std::vector<PointI>::iterator iter=inputStartingPositions.begin();iter!=inputStartingPositions.end();++iter)
			{
				startingPositions.push_back(*iter);
			}
		}
		
		void EnemyFactory::clearStartingPositions()
		{
			startingPositions.clear();
		}
	
	}
}