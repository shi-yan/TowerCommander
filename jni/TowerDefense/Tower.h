/*
 *  Tower.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Tower__
#define __Tower__

#include "GlobalConfig.h"
#include <cmath>
#include "Point.h"
#include "Texture.h"
#include "Bullet.h"
#include "Enemy.h"
#include "QuadHelper.h"
#include "TextureAnimation.h"


#ifdef	__ANDROID__

#include "AndroidSoundManager.h"
#else
#include "QtSoundManager.h"
#endif

namespace AnimalCrackers
{
	namespace TowerDefense 
	{

		
		class Tower:public Sprite
		{	
		public:
			
			enum TowerType
			{
				Gun_A,
				Gun_B,
				Gun_C,
				Canon_A,
				Canon_B,
				Canon_C,
				Flame_A,
				Flame_B,
				Flame_C,
				Air_A,
				Air_B,
				Air_C,
				Slow_A,
				Slow_B,
				Slow_C,
				Laser_A,
				Laser_B,
				Laser_C,
			};
			
			enum TargetType 
			{
				GroundOnly,
				All,
				AirOnly,
			};
			
			int getTowerType()
			{
				return towerType;
			};
			
			static int getPoints(int _type)
			{
				switch (_type) {
					case 0:
						return 10000;
						break;
					case 1:
						
						return 10000;
						break;
					case 2:
						
						return 10000;
						break;
					case 3:
						
						return 10000;
						break;
					case 4:
						
						return 10000;
						break;
					case 5:
						
						return 10000;
						break;
					case 6:
						
						return 10000;
						break;
					case 7:
						
						return 10000;
						break;
					case 8:
						
						return 10000;
						break;
					case 9:
						
						return 10000;
						break;
					case 10:
						
						return 10000;
						break;
					case 11:
						
						return 10000;
						break;
					case 12:
						
						return 10000;
						break;
					case 13:
						
						return 10000;
						break;
					case 14:
						
						return 10000;
						break;
					case 15:
						
						return 10000;
						break;
					case 16:
						
						return 10000;
						break;
					case 17:
						
						return 10000;
						break;
					case 18:
						
						return 10000;
						break;
					case 19:
						
						return 10000;
						break;
					case 20:
						
						return 10000;
						break;
					case 21:
						
						return 10000;
						break;
					default:
						break;
				}
			}
			
			static int getLevel(int _type)
			{
				switch (_type) {
					case 0:
						return 0;
						break;
					case 1:
						return 0;
						break;
					case 2:
						return 1;
						break;
					case 3:
						return 0;
						break;
					case 4:
						return 2;
						break;
					case 5:
						return 0;
						break;
					case 6:
						return 3;
						break;
					case 7:
						return 3;
						break;
					case 8:
						return 3;
						break;
					case 9:
						return 3;
						break;
					case 10:
						return 0;
						break;
					case 11:
						return 3;
						break;
					case 12:
						return 3;
						break;
					case 13:
						return 3;
						break;
					case 14:
						return 3;
						break;
					case 15:
						return 3;
						break;
					case 16:
						return 3;
						break;
					case 17:
						return 3;
						break;
					case 18:
						return 3;
						break;
					case 19:
						return 3;
						break;
					case 20:
						return 3;
						break;
					case 21:
						return 3;
						break;
					case 22:
						return 3;
						break;
					default:
						break;
				}
			}
			
			static int getTowerCost(int _type)
			{
				switch (_type) {
					case 0:
						return 90;
						break;
					case 1:
						return 105;
						break;
						
					case 2:
						return 115;
						break;
						
					case 3:
						return 125;
						break;
						
					case 4:
						return 145;
						break;
						
					case 5:
						return 160;
						break;
						
					case 6:
						return 180;
						break;
						
					case 7:
						return 220;
						break;
						
					case 8:
						return 260;
						break;
						
					case 9:
						return 860;
						break;
						
					case 10:
						return 260;
						break;
						
					case 11:
						return 150;
						break;
						
						
					case 12:
						return 90;
						break;
						
						
					case 13:
						return 170;
						break;
						
						
					case 14:
						return 155;
						break;
						
					case 15:
						return 190;
						break;
						
					case 16:
						return 310;
						break;
						
					case 17:
						return 350;
						break;
						
					case 18:
						return 340;
						break;
						
					case 19:
						return 270;
						break;
						
					case 20:
						return 460;
						break;
						
					case 21:
						return 940;
						break;
						
					default:
						
						return 1;
						break;
				}
			}
			
			static int getSellMoney(int _type)
			{
				switch (_type) {
					case 0:
						return 15;
						break;
					case 1:
						return 20;
						break;
					case 2:
						return 30;
						break;
					case 3:
						return 35;
						break;
						
					case 4:
						return 40;
						break;
						
					case 5:
						return 60;
						break;
						
					case 6:
						return 60;
						break;
						
					case 7:
						return 80;
						break;
						
					case 8:
						return 100;
						break;
						
					case 9:
						return 300;
						break;
						
					case 10:
						return 100;
						break;
						
						
					case 11:
						return 45;
						break;
						
						
					case 12:
						return 10;
						break;
						
						
					case 13:
						return 60;
						break;
						
						
					case 14:
						return 60;
						break;
						
					case 15:
						return 70;
						break;
						
					case 16:
						return 120;
						break;
						
					case 17:
						return 140;
						break;
						
					case 18:
						return 140;
						break;
						
					case 19:
						return 100;
						break;
						
					case 20:
						return 200;
						break;
						
					case 21:
						return 400;
						break;
						
					default:
						break;
				}
			};
			
			static float getSpeed(int _type)
			{
				switch (_type) {
					case 0:
						return 1.0f;
						break;
					case 1:
						return 2.0f;
						break;
					case 2:
						return 2.0f;
						break;
					case 3:
						return 0.8f;
						break;
						
					case 4:
						return 1.2f;
						break;
						
					case 5:
						return 0.8f;
						break;
						
					case 6:
						return 0.6f;
						break;
						
					case 7:
						return 1.0f;
						break;
						
					case 8:
						return 0.9f;
						break;
						
					case 9:
						return 1.1f;
						break;
						
					case 10:
						return 1.0f;
						break;
						
						
					case 11:
						return 2.0f;
						break;
						
						
					case 12:
						return 3.0f;
						break;
						
						
					case 13:
						return 2.5f;
						break;
						
						
					case 14:
						return 1.0f;
						break;
						
					case 15:
						return 0.9f;
						break;
						
					case 16:
						return 1.0f;
						break;
						
					case 17:
						return 1.5f;
						break;
						
					case 18:
						return 1.1f;
						break;
						
					case 19:
						return 1.2f;
						break;
						
					case 20:
						return 1.3f;
						break;
						
					case 21:
						return 0.9f;
						break;
						
					default:
						break;
				}
			};
			
			static int getPower(int _type)
			{
				switch (_type) {
					case 0:
						return 1.0f;
						break;
					case 1:
						return 2.0f;
						break;
					case 2:
						return 4.0f;
						break;
					case 3:
						return 2;
						break;
						
					case 4:
						return 4;
						break;
						
					case 5:
						return 6;
						break;
						
					case 6:
						return 10;
						break;
						
					case 7:
						return 12;
						break;
						
					case 8:
						return 14;
						break;
						
					case 9:
						return 21;
						break;
						
					case 10:
						return 3;
						break;
						
						
					case 11:
						return 8;
						break;
						
						
					case 12:
						return 10;
						break;
						
						
					case 13:
						return 6;
						break;
						
						
					case 14:
						return 10;
						break;
						
					case 15:
						return 12;
						break;
						
					case 16:
						return 14;
						break;
						
					case 17:
						return 15;
						break;
						
					case 18:
						return 18;
						break;
						
					case 19:
						return 20;
						break;
						
					case 20:
						return 20;
						break;
						
					case 21:
						return 30;
						break;
						
					default:
						break;
				}
			};
			
			static float getRange(int _type)
			{
				switch (_type) {
					case 0:
						return 2500;
						break;
					case 1:
						return 3600;
						break;
					case 2:
						return 2700;
						break;
					case 3:
						return 4800;
						break;
						
					case 4:
						return 4600;
						break;
						
					case 5:
						return 5000;
						break;
						
					case 6:
						return 5200;
						break;
						
					case 7:
						return 5500;
						break;
						
					case 8:
						return 6000;
						break;
						
					case 9:
						return 4000;
						break;
						
					case 10:
						return 3000;
						break;
						
						
					case 11:
						return 8000;
						break;
						
						
					case 12:
						return 10000;
						break;
						
						
					case 13:
						return 6000;
						break;
						
						
					case 14:
						return 8000;
						break;
						
					case 15:
						return 12000;
						break;
						
					case 16:
						return 14000;
						break;
						
					case 17:
						return 15000;
						break;
						
					case 18:
						return 18000;
						break;
						
					case 19:
						return 20000;
						break;
						
					case 20:
						return 20000;
						break;
						
					case 21:
						return 30000;
						break;
						
					default:
						break;
				}
			};
			
			static void getUpgradeChoices(int _type,int p[])
			{
				switch (_type) {
					case 0:
						p[0]=1;
						p[1]=12;
						break;
					case 1:
						
						p[0]=2;
						p[1]=11;
						break;
					case 2:
						
						p[0]=17;
						p[1]=-1;
						break;
					case 3:
						
						p[0]=5;
						p[1]=11;
						break;
						
					case 4:
						
						p[0]=5;
						p[1]=14;
						break;
						
					case 5:
						
						p[0]=6;
						p[1]=-1;
						break;
						
					case 6:
						
						p[0]=7;
						p[1]=-1;
						break;
						
					case 7:
						
						p[0]=8;
						p[1]=-1;
						break;
						
					case 8:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					case 9:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					case 10:
						
						p[0]=16;
						p[1]=-1;
						break;
						
						
					case 11:
						
						p[0]=13;
						p[1]=19;
						break;
						
						
					case 12:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
						
					case 13:
						
						p[0]=21;
						p[1]=-1;
						break;
						
						
					case 14:
						
						p[0]=15;
						p[1]=-1;
						break;
						
					case 15:
						
						p[0]=9;
						p[1]=-1;
						break;
						
					case 16:
						
						p[0]=20;
						p[1]=-1;
						break;
						
					case 17:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					case 18:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					case 19:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					case 20:
						
						p[0]=18;
						p[1]=-1;
						break;
						
					case 21:
						
						p[0]=-1;
						p[1]=-1;
						break;
						
					default:
						break;
				}
			};
			
		protected:
			int towerType;
			PointI position;
			float range;
			float interval;
			float realrange;
			float shotSpeed;
			//float accumulatedShootingTime;
			int shotAtEnemyID;
			int rid;
			Bullet *bullet;
			float bulletpos;
			int oldshotAtEnemyID;
			enum TargetType targetType;
			PointI bulletOffset[12];
			
			double lastShotTime;
			
			float accumulatedSpeed;
			float damage;
			
			enum SoundManager::SoundEffects soundEffect;
			
		public:
			PointF accuratePosition;
			
			Tower()
			:Sprite(0,0,0),
			towerType(Gun_A),
			position(0,0),
			range(2500.0f),
			interval(.04f),
			realrange(50.0f),
			shotSpeed(1.0f),
		//	accumulatedShootingTime(0),
			shotAtEnemyID(-1),
			rid(4),
			bullet(NULL),
			bulletpos(10.0f),
			oldshotAtEnemyID(-9),targetType(All),
			bulletOffset(),lastShotTime(0),accumulatedSpeed(0),damage(1),soundEffect(SoundManager::MACHINEGUN),
			accuratePosition(0,0)
			{
			}
			
			void setShotSpeed(float s)
			{
				shotSpeed=s;
			};
			
			void setDamage(float d)
			{
				damage=d;
			};
			
			void setTowerType(int _type)
			{
				towerType=_type;
			};
			
			void setSoundEffect(enum SoundManager::SoundEffects _se)
			{
				soundEffect=_se;
			};
			
			virtual ~Tower()
			{
				delete bullet;
			};
			
			void shotAtEnemy(int id)
			{
				shotAtEnemyID=id;
			};
			
			void setTargetType(TargetType _type)
			{
				targetType=_type;
			};
			
			void setBullet(Bullet *_bullet)
			{
				bullet=_bullet;
			};
			
			virtual void shotAtEnemy(int id,Enemy *e);
			
			float getRange()
			{
				return sqrt(range);
			};
			
			void setBulletOffsets(PointI bo[12])
			{
				for (int i=0; i<12; ++i) 
				{
					bulletOffset[i]=bo[i];
				}
			}
			
			virtual void draw()
			{
				towerTextures->apply();
				QuadHelper::getSingleton().drawQuad(x+offsetX,y+offsetY,width,height,towerTextures->getCoordinates());
				bullet->drawRotate();
			};
			
			void beforeShootingAtEnemy()
			{
				
				
			};
			
			void afterShootingAtEnemy();
			
			void setRange(float _range)
			{
				range=_range;
				realrange=(float) sqrt(range);
			};
			
			void setPosition(PointI _pos);			
			void setInterval(float _int)
			{
				interval=_int;
			};
			
			static const int degree0=0;
			static const int degree1=30;
			static const int degree2=60;
			
			static const int degree3=90;
			static const int degree4=150;
			static const int degree5=180;
			
			static const int degree6=210;
			static const int degree7=240;
			static const int degree8=270;
			
			static const int degree9=300;
			static const int degree10=330;
			static const int degree11=360;
			
			
			TextureAnimation *towerTextures;
			
			void setTextureIndices(TextureAnimation *_textures)
			{
				towerTextures=_textures;
			}
			
		};
	}
}

#endif