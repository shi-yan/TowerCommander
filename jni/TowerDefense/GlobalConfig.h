/*
 *  GlobalConfig.h
 *  JumpNRun
 *
 *  Created by Shi Yan on 8/31/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __GlobalConfig__
#define __GlobalConfig__

//#define __ANDROID__

static int TileSize = 64;
static int TowerWidth= 64;
static int TowerHeight= 96;

const float version=0.1f;
const int overallLevel=3;

const int levelAchievementSize=25;
const int levelStatisticsSize=6;
const int gameAchievementSize=32;
const int gameStatisticsSize=8;
const int gameTowerCount=22;

#ifdef __ANDROID__

#include <android/log.h>
#define  LOG_TAG    "libtowerdefense"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else

#endif

#endif