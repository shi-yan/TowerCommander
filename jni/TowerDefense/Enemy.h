/*
 *  Enemy.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Enemy__
#define __Enemy__

#include "GlobalConfig.h"
#include "Sprite.h"
#include "Point.h"
#include <deque>
#include <vector>
#include "TextureAnimation.h"
#include "SmallAnimationManager.h"
#include "CoinAnimation.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class GameMap;
		
		class Enemy: public Sprite
		{		
		protected:
			static TextureAnimation *bloodTexture;
			int currentBloodAnimationID;
			double lastMoveTime;
			
			static std::vector<int> *enemyOrder;
			static int ydimension;
			
		public:
			
			static void initializeEnemyOrder(int _y)
			{
				if (enemyOrder) 
				{
					delete [] enemyOrder;
				}
				
				enemyOrder=new std::vector<int>[ydimension=_y];
			}
			
			static void releaseEnemyOrder()
			{
				delete [] enemyOrder;
				enemyOrder=NULL;
			};
			
			static std::vector<int> & getEnemyOrderByY(int _y)
			{
				return enemyOrder[_y];
			};
			
			static void registerEnemyOrder(int _y,int _eid)
			{
				enemyOrder[_y].push_back(_eid);
			};
			
			static void clearEnemyOrder()
			{
				for (int i=0; i<ydimension; ++i) {
					enemyOrder[i].clear();
				}
			};
			
			int getPathY()
			{
				return path[pathStep].y;
			};
			
			enum EnemyType 
			{
				Ground,
				Air,
			};
			
			virtual enum EnemyType getEnemyType()
			{
				return Ground;
			};
			
			static void setBloodTexture();
			static void releaseBloodTexture()
			{
				if(bloodTexture)
					delete bloodTexture;
			};
			
			enum WalkDirection
			{
				North,
				South,
				West,
				East,
				NONEDIR,
			};
			
			enum AnimationType
			{
				Walk,
				Shoot,
				Crash,
			};
			
			PointI position;
			PointF fakePosition;
			enum WalkDirection direction;
			bool isDead;
			PointF movestart;
			PointF moveend;
			float moved ;
			float speed ;
			std::vector<PointI> path;
			float health;
			float fullHealth;
			int pathStep;
			int accumulatedLastingDamage;
			float slowDownRate;
			int applyLastingDamageCounter;
			int money;
			int explosionType;
			
			Enemy(int width=0,int height=0)
			:Sprite(width,height,0),
			currentBloodAnimationID(0),lastMoveTime(0),
			position(),
			fakePosition(),
			direction(North),
			isDead(false),
			movestart(),
			moveend(),
			moved ( 0.0f),
			speed( 0.04f),
			path(),
			health(10), 
			fullHealth(10),
			pathStep(0), 
			accumulatedLastingDamage(0),
			slowDownRate(1.0f),
			applyLastingDamageCounter(0),money(15),explosionType(0)
			{
			};
			
			virtual ~Enemy()
			
			{
				
			};
			
			void setExplosionType(int _type)
			{
				explosionType=_type;
			};
			
			void setPosition(PointI pos)
			{
				position=pos;
			};
			
			void setMoney(int _mon)
			{
				money=_mon;
			};
			
			void setFullHealth(float _fullHealth)
			{
				fullHealth=health=_fullHealth;
			};
			
			void lastingDamage(int d);
			
			void immediateDamage(float d);
			
			void slowDown(float rate);
			
			void setSlowDownRate(float rate)
			{
				slowDownRate=rate;
			};
			
			void setSpeed(float _speed)
			{
				speed=_speed;
			};
			
			void applyLastingDamage();
			
			void setTextureIndices(Texture *_up,Texture *_down,Texture *_left,Texture *_right)
			{
				addTexture(_up);
				addTexture(_down);
				addTexture(_left);
				addTexture(_right);
			};
			
			void setDeath()
			{
				isDead=true;
			};
			
			void setKilled();
			
			void beginMove();
			
			virtual bool findTempPathWithTempBlock(std::deque<PointI> & tmppath,PointI tempBlockPoint);
			virtual bool findTempPath(std::deque<PointI> & tmppath);
			virtual void findPath();
			virtual void draw();
			virtual bool move();			
			virtual void renewDisplayPosition();
		};
	}
}

#endif