/*
 *  Point.h
 *  towerdefense
 *
 *  Created by Shi Yan on 9/30/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Point__
#define __Point__

#include "GlobalConfig.h"
#include <cmath>
static const double PI= 4.*atan(1.);

template<class Scalar>
class Point
{
public:
	Scalar x;
	Scalar y;

	Point():x(0),y(0)
	{};
	
	Point(Scalar _x,Scalar _y):x(_x),y(_y){};
	
	~Point(){};
	
	
	void operator=(const Point<Scalar> &_in)
	{
		x=_in.x;
		y=_in.y;
	};
	
	bool operator==(const Point<Scalar> &_in)
	{
		return (_in.x==x && _in.y==y);
	};
};

typedef Point<float> PointF;
typedef Point<int> PointI;

#endif