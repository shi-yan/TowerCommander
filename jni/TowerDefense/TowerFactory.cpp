/*
 *  TowerFactory.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "TowerFactory.h"
#include "Bullet.h"
#include "FlameTower.h"
#include "SlowTower.h"
namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		
		
		Tower *TowerFactory::getTower(int x,int y,int type)
		{
			PointI mapOffset=GameMap::getSingleton().getMapOffset();
			
#ifdef __ANDROID__
			int nb=TextureAtlasManager::getSingleton().addNew("bullet.png");
			int	towerAtlas=TextureAtlasManager::getSingleton().addNew("tower.png");
#else
	
			int nb=TextureAtlasManager::getSingleton().addNew("../../../../assets/bullet.png");
			int	towerAtlas=TextureAtlasManager::getSingleton().addNew("../../../../assets/tower.png");
#endif
			switch(type)
			{
				case 0:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,0,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					
					Texture	*ba=new Texture(nb,164,70,1,10);
					
					bulletSprite->addTexture(ba );
					bulletSprite->setSize(3, 10);
					bulletSprite->setSpeed(6.5f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(1.0f);
					t->setDamage(1.5f);
					
					
					PointI bo[12]={PointI(21,32),PointI(32,33),PointI(37,29),PointI(39,21),PointI(36,13),PointI(32,9),PointI(22,8),PointI(11,9),PointI(5,12),PointI(2,20),PointI(5,29),PointI(11,33)};
					t->setBulletOffsets(bo);
					
					t->setTowerType(0);
					
					return t;
				}
					
				case 1:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,60,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,166,70,4,11));
					bulletSprite->setSize(4, 11);
					bulletSprite->setSpeed(2.5f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(21,34),PointI(32,33),PointI(37,28),PointI(41,20),PointI(39,12),PointI(31,8),PointI(21,6),PointI(11,7),PointI(5,12),PointI(3,20),PointI(5,29),PointI(9,33)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(1.0f);
					t->setDamage(2.0f);
					t->setTowerType(1);
					return t;			
				}
					
				case 2:
				{
					Tower *t=new Tower();
					
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,120,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					
					TextureAnimation *ba=new TextureAnimation(nb,197,135,32,16,16,16);
					int k[2]={0,1};
					ba->addAnimation(k, 2);
					ba->setAnimation(0);
					bulletSprite->addTexture(ba);
					bulletSprite->setSize(16, 16);
					bulletSprite->setSpeed(2.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(20,37),PointI(32,35),PointI(40,32),PointI(40,23),PointI(40,13),PointI(33,8),PointI(21,6),PointI(10,8),PointI(3,13),PointI(-1,22),PointI(3,31),PointI(8,36)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(0.7f);
					t->setDamage(2.5f);
					t->setTowerType(2);
					return t;				
				}
					
				case 3:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,180,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					
					TextureAnimation *ba=new TextureAnimation(nb,1,135,32,16,16,16);
					int k[2]={0,1};
					ba->addAnimation(k, 2);
					ba->setAnimation(0);
					bulletSprite->addTexture(ba);
					bulletSprite->setSpeed(2.5f);
					bulletSprite->setSize(16, 16);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(21,43),PointI(35,41),PointI(40,34),PointI(40,26),PointI(39,16),PointI(31,11),PointI(18,11),PointI(6,11),PointI(-1,17),PointI(-1,26),PointI(2,36),PointI(8,40)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(0.5f);
					t->setDamage(3.8f);
					t->setTowerType(3);
					t->setSoundEffect(SoundManager::LASER);
					return t;		
				}
					
				case 4:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,240,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,323,153,24,24));
					bulletSprite->setSpeed(1.5f);
					bulletSprite->setSize(24, 24);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(20,31),PointI(31,28),PointI(36,18),PointI(38,12),PointI(36,6),PointI(30,1),PointI(21,1),PointI(12,2),PointI(6,8),PointI(3,16),PointI(6,22),PointI(13,26)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(4);
					return t;
					
				}
					
				case 5:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,300,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,35,135,160,16,16,16);
					
					int k[10]={0,1,2,3,4,5,6,7,8,9};
					
					ba->addAnimation(k, 10);
					ba->setAnimation(0);
					
					
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->addTexture(ba);
					bulletSprite->setSize(16, 16);
					bulletSprite->setSpeed(2.0f);
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(22,34),PointI(34,31),PointI(41,23),PointI(42,16),PointI(38,10),PointI(29,6),PointI(19,4),PointI(9,8),PointI(2,13),PointI(2,21),PointI(7,27),PointI(14,32)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(5);
					return t;
				}
					
				case 6:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,360,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,340,102,7,32));
					bulletSprite->setSize(7, 32);
					bulletSprite->setSpeed(1.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,28),PointI(27,27),PointI(31,22),PointI(33,18),PointI(33,12),PointI(26,7),PointI(19,6),PointI(12,6),PointI(6,10),PointI(5,18),PointI(6,23),PointI(12,26)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(6);
					return t;								
				}
					
				case 7:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,420,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,348,109,14,25,7,25);
					int k[2]={0,1};
					ba->addAnimation(k, 2);
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(7, 25);
					bulletSprite->setSpeed(1.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,26),PointI(24,24),PointI(25,24),PointI(25,22),PointI(25,19),PointI(24,17),PointI(18,16),PointI(14,19),PointI(14,20),PointI(13,23),PointI(13,24),PointI(15,25)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(7);
					return t;
				}
					
				case 8:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,480,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,163,85,20,15));
					bulletSprite->setSize(20, 15);
					bulletSprite->setSpeed(1.2f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,33),PointI(26,32),PointI(31,28),PointI(33,23),PointI(33,16),PointI(27,10),PointI(20,8),PointI(13,9),PointI(10,12),PointI(7,21),PointI(8,26),PointI(13,31)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(8);
					return t;
				}
					
				case 9:
				{
					FlameTower *t=new FlameTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,540,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					
					TextureAnimation *ba=new TextureAnimation(nb,0,1,480,66,480/15,66);
					int k[15]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
					
					ba->addAnimation(k, 15);
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(480/15, 66);
					bulletSprite->setSpeed(0.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,28),PointI(30,24),PointI(32,24),PointI(37,20),PointI(33,12),PointI(28,5),PointI(19,3),PointI(9,5),PointI(6,9),PointI(4,19),PointI(8,26),PointI(15,26)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(9);
					return t;
				}
					
				case 10:
				{
					SlowTower *t=new SlowTower();
				//	t->setRange(29000);
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,600,480,60,40,60);
					//prepareDifferentAngel(ani);
					int k[12]={0,1,2,3,4,5,6,7,8,9,10,11};
					ani->addAnimation(k, 12);
					ani->setAnimation(0);
					
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture(new Texture(nb,0,0,1,10));
					bulletSprite->setSize(3, 10);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(0.8f);
					t->setTowerType(10);
					return t;
				}
					
				case 11:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,660,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					
					
					bulletSprite->addTexture( new Texture(nb,355,179,11,13));
					bulletSprite->setSize(11, 13);
					bulletSprite->setSpeed(2.0);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(13,49),PointI(28,45),PointI(30,38),PointI(32,31),PointI(30,23),PointI(23,19),PointI(14,17),PointI(5,18),PointI(2,24),PointI(-1,29),PointI(1,36),PointI(6,39)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(11);
					return t;
				}
					
				case 12:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,720,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture(new Texture(nb,355,179,3,13));
					bulletSprite->setSize(3, 13);
					bulletSprite->setSpeed(2.5);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(22,48),PointI(32,45),PointI(38,37),PointI(41,30),PointI(38,20),PointI(31,15),PointI(23,13),PointI(13,14),PointI(8,21),PointI(10,32),PointI(7,38),PointI(13,45)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(12);
					return t;
				}
					
				case 13:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,780,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,323,179,10,20));
					bulletSprite->setSize(10, 20);
					bulletSprite->setSpeed(1.5f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,36),PointI(29,33),PointI(34,30),PointI(34,23),PointI(30,18),PointI(27,14),PointI(19,14),PointI(13,15),PointI(7,20),PointI(5,24),PointI(6,32),PointI(10,36)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(13);
					return t;
				}
					
				case 14:
				{
					FlameTower *t=new FlameTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,840,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,1,101,320,32,32,32);
					int k[10]={0,1,2,3,4,5,6,7,8,9};
					ba->addAnimation(k, 10);
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(32, 32);
					bulletSprite->setSpeed(1.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(19,34),PointI(24,33),PointI(31,30),PointI(31,23),PointI(29,17),PointI(25,15),PointI(19,12),PointI(15,14),PointI(10,16),PointI(6,23),PointI(7,31),PointI(11,35)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(14);
					return t;
				}
					
				case 15:
				{
					FlameTower *t=new FlameTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,0,900,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,1,153,320,32,32,32);
					int k[10]={0,1,2,3,4,5,6,7,8,9};
					ba->addAnimation(k, 10);
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(32, 32);
					bulletSprite->setSpeed(0.8f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(21,46),PointI(30,42),PointI(36,35),PointI(39,27),PointI(35,18),PointI(29,10),PointI(19,10),PointI(10,12),PointI(4,18),PointI(1,28),PointI(3,34),PointI(11,41)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					t->setTowerType(15);
					return t;
				}
					
				case 16:
				{
					SlowTower *t=new SlowTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,780,480,60,40,60);
					int k[12]={0,1,2,3,4,5,6,7,8,9,10,11};
					ani->addAnimation(k, 12);
					
					ani->setAnimation(0);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,0,0,1,10));
					bulletSprite->setSize(3, 10);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					
					t->setPosition(PointI(x,y));
					t->setDamage(0.6f);
					t->setShotSpeed(2.0);
					
					t->setTowerType(16);
					return t;
				}
					
				case 17:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,720,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,1,187,320,32,32,32);
					int k[10]={0,1,2,3,4,5,6,7,8,9};
					ba->addAnimation(k, 10);
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(32, 32);
					bulletSprite->setSpeed(1.7f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(21,40),PointI(32,36),PointI(39,31),PointI(40,22),PointI(39,13),PointI(33,6),PointI(21,4),PointI(9,5),PointI(2,11),PointI(1,21),PointI(2,32),PointI(9,38)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(17);
					return t;
				}
					
				case 18:
				{
					SlowTower *t=new SlowTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,660,480,60,40,60);
					
					int k[12]={0,1,2,3,4,5,6,7,8,9,10,11};
					ani->addAnimation(k, 12);
					ani->setAnimation(0);
					
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,0,0,1,10));
					bulletSprite->setSize(3, 10);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					
					t->setPosition(PointI(x,y));
					t->setDamage(0.8f);
					t->setShotSpeed(2.0);
				
					t->setTowerType(18);
					return t;
				}
					
				case 19:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,600,480,60,40,60);
					prepareDifferentAngel(ani);
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,1,221,320,32,32,32);
					int k[10]={0,1,2,3,4,5,6,7,8,9};
					ba->addAnimation(k,10 );
					ba->setAnimation(0);
					bulletSprite->addTexture( ba);
					bulletSprite->setSize(32, 32);
					bulletSprite->setSpeed(1.5f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(20,40),PointI(32,37),PointI(39,30),PointI(40,21),PointI(37,12),PointI(30,7),PointI(18,7),PointI(7,8),PointI(2,14),PointI(0,23),PointI(2,31),PointI(9,36)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(19);
					return t;
				}
					
				case 20:
				{
					SlowTower *t=new SlowTower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,480,480,120,40,60);
					
					int k[15]={13,14,15,16,17,18,19,20,21,22,23,0,1,2,3};
					ani->addAnimation(k, 15);
					ani->setAnimation(0);
					
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					bulletSprite->addTexture( new Texture(nb,0,0,1,10));
					bulletSprite->setSize(3, 10);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					
					t->setPosition(PointI(x,y));
						t->setDamage(1.0f);
					t->setShotSpeed(2.0);
			
					t->setTowerType(20);
					return t;
				}
					
				case 21:
				{
					Tower *t=new Tower();
					
					TextureAnimation *ani=new TextureAnimation(towerAtlas,480,540,40,60,40,60);
					
					int k[15]={0,0,0,0,0,0,0,0,0,0,0,0,0};
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					ani->addAnimation(k, 1);
					
					t->setTextureIndices(ani);
					
					Bullet *bulletSprite=new Bullet();
					TextureAnimation *ba=new TextureAnimation(nb,1,255,330,89,55,89);
					int k2[6]={0,1,2,3,4,5};
					ba->addAnimation(k2, 6);
					
					ba->setAnimation(0);
					
					bulletSprite->addTexture(ba);
					bulletSprite->setSize(55, 89);
					bulletSprite->setSpeed(0.0f);
					t->setSize(TowerWidth, TowerHeight);
					
					bulletSprite->setVisible(false);
					t->setBullet(bulletSprite);
					PointI bo[12]={PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11),PointI(20,11)};
					t->setBulletOffsets(bo);
					t->setPosition(PointI(x,y));
					t->setShotSpeed(2.0);
					t->setDamage(2.0f);
					
					t->setTowerType(21);
					return t;
				}
			}
		}		
					
	}
}