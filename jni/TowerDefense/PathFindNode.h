/*
 *  PathFindNode.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/30/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __PathFindNode__
#define __PathFindNode__

#include "GlobalConfig.h"
#include "Point.h"

namespace AnimalCrackers 
{
	namespace TowerDefense 
	{
		class PathFindNode 
		{
		public:
			PointI pos;
			PathFindNode *pre;
	
			PathFindNode(PointI position)
			:pos(position.x,position.y),pre(NULL) 
			{
			};
		};
	}
}
#endif