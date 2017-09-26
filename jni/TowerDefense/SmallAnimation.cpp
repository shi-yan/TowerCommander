#include "SmallAnimation.h"

namespace AnimalCrackers 
{
	namespace TowerDefense
	{
		SmallAnimation::SmallAnimation(void):Sprite(0, 0, 0, 0, 0),
		_isDead(false),beginTime(0),lastingTime(1),elapsedTime(0)
		{
		}

		SmallAnimation::~SmallAnimation(void)
		{
		}
	}
}