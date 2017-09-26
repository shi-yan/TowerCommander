#ifndef __SmallAnimation__
#define __SmallAnimation__

#include "GlobalConfig.h"
#include "Sprite.h"
#include "GameTimeManager.h"


namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class SmallAnimation :public Sprite
		{
		protected:
			double beginTime;
			double lastingTime;
			double elapsedTime;
			bool _isDead;
			
		public:
			SmallAnimation(void);
			virtual ~SmallAnimation(void);
			
			void beginAnimation()
			{
				beginTime=GameTimeManager::getSingleton().getCurrentTime();
			};
			
			void setLastingTime(double l)
			{
				lastingTime=l;
			};
			
			void animate()
			{
				double currentTime=GameTimeManager::getSingleton().getCurrentTime();
				elapsedTime=currentTime-beginTime;
				
				if (elapsedTime>lastingTime) {
					elapsedTime=lastingTime;
					_isDead=true;
				}
			};
			
			bool isDead()
			{
				return _isDead;
			}
		};
	}
}

#endif