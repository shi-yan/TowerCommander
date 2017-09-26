/*
 *  GameTimeManager.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/20/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __GameTimeManager__
#define __GameTimeManager__

#include "GlobalConfig.h"

#ifdef WIN32

#include <time.h>
#include <windows.h> //I've ommited this line.

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};
 
static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
    /*converting file time to unix epoch*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tmpres /= 10;  /*convert into microseconds*/
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }
    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }
 
  return 0;
}
#else
#include <sys/time.h>
#endif

namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		class GameTimeManager  
		{
		private:
			GameTimeManager():beginTime(0),currentTime(0)
			{};
			~GameTimeManager(){};
			double beginTime;
			double currentTime;
			
		public:
			double gameBegin();
			double getElapsedTime();
			double getCurrentTime();
			double refreshCurrentTime();
			
			static GameTimeManager & getSingleton()
			{
				static GameTimeManager obj;
				return obj;
			}
		};
	}
}

#endif