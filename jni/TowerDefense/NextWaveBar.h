/*
 *  NextWaveBar.h
 *  towerdefense
 *
 *  Created by Shi Yan on 10/10/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __NextWaveBar__
#define __NextWaveBar__

#include "GlobalConfig.h"
#include "UIItem.h"
#include <deque>
#include "QuadHelper.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{
	
		class NextWaveBar : public UIItem 
		{
		private:
			bool isVisable;
			int nextWave;
			std::deque<int> digits;
			
			std::deque<int> overallWave;
			std::deque<int> currentWave;
		
			Texture *digitTextures[10];
			TextureAnimation *nextWaveTexture;
			Texture *waveCounterBar;
		
			int atlasID;
		
			NextWaveBar():UIItem(40,40),nextWave(0),isVisable(false)
			{};
		
			~NextWaveBar()
			{
				delete nextWaveTexture;
				for (int i=0; i<10; ++i) 
				{
					delete digitTextures[i];
				}
				
				delete waveCounterBar;
			};
		
	public:
		
		void setVisible(bool vis)
		{
			isVisable=vis;
		}
		
		int getTime()
		{
			return nextWave;
		};
		
		void init(int _atlas,int time=20);
		
		void setTime(int tim)
		{
			nextWave=tim=tim>=0?tim:0;
			
			digits.clear();
			while (tim>9) 
			{
				int di=tim%10;
				digits.push_front(di);
				tim=(tim-di)/10;
			}
			
			digits.push_front(tim);
		};
			
			void setCurrentWave(int cw)
			{
				cw=cw>=0?cw:0;
				
				currentWave.clear();
				while (cw>9) 
				{
					int di=cw%10;
					currentWave.push_front(di);
					cw=(cw-di)/10;
				}
				
				currentWave.push_front(cw);
			};
			
			void setOverallWave(int ow)
			{
				ow=ow>=0?ow:0;
				
				overallWave.clear();
				while (ow>9) 
				{
					int di=ow%10;
					overallWave.push_front(di);
					ow=(ow-di)/10;
				}
				
				overallWave.push_front(ow);
			};
		
		static NextWaveBar & getSingleton()
		{
			static NextWaveBar obj;
			return obj;
		};
		
		void draw();		
		
	};
}
}

#endif