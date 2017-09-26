/*
 *  AirEnemy.cpp
 *  towerdefense
 *
 *  Created by Shi Yan on 9/29/10.
 *  Copyright 2010 Univerisity of California, Davis. All rights reserved.
 *
 */

#include "AirEnemy.h"
#include "GameMap.h"
#include <queue>
#include "PathFindNode.h"


namespace AnimalCrackers
{
	namespace TowerDefense 
	{
		void AirEnemy::renewDisplayPosition()
		{
			PointI p=GameMap::getSingleton().getMapOffset();
			setXY(fakePosition.x-20-p.x, fakePosition.y-60-p.y);
		}
	
		void AirEnemy::findPath()
		{
			std::vector<PathFindNode*> nodepool;
			nodepool.reserve(1000);
		
			bool* hasBeenVisited=new bool[GameMap::getSingleton().dimension.x*GameMap::getSingleton().dimension.y];
		
			for(int x=0;x<GameMap::getSingleton().dimension.x;++x)
				for(int y=0;y<GameMap::getSingleton().dimension.y;++y)
					hasBeenVisited[x+GameMap::getSingleton().dimension.x*y]=false;
		
			std::queue<PathFindNode*> breadthFirstQueue;
		
			PathFindNode *initialNode=new PathFindNode(position);
			breadthFirstQueue.push(initialNode);
			nodepool.push_back(initialNode);
		
			while ( breadthFirstQueue.size() > 0 && !GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos))
			{
				PathFindNode *tempnode=breadthFirstQueue.front();
				breadthFirstQueue.pop();
				PointI tempPosition=tempnode->pos;
				std::vector<int> walkableTiles; 
				walkableTiles.reserve(4);
				GameMap::getSingleton().airWalkable(tempPosition,walkableTiles);
			
				for (std::vector<int>::iterator walkabledir=walkableTiles.begin();walkabledir!=walkableTiles.end();++walkabledir)
				{
					switch (*walkabledir)
					{
						case GameMap::North:
						{
							if(hasBeenVisited[tempPosition.x + GameMap::getSingleton().dimension.x*(tempPosition.y - 1)]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x, tempPosition.y - 1));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+ GameMap::getSingleton().dimension.x* (tempPosition.y - 1)]=true;
							}
						}
						break;
					
						case GameMap::South:
						{
							if(hasBeenVisited[tempPosition.x + GameMap::getSingleton().dimension.x*(tempPosition.y + 1)]==false)
							{
								PathFindNode *newnode = new PathFindNode(PointI(tempPosition.x, tempPosition.y + 1));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+ GameMap::getSingleton().dimension.x* (tempPosition.y + 1)]=true;
							}
						}
						break;
					
						case GameMap::West:
						{
							if(hasBeenVisited[tempPosition.x-1 +GameMap::getSingleton().dimension.x* tempPosition.y]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x - 1, tempPosition.y));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x-1+ GameMap::getSingleton().dimension.x* tempPosition.y]=true;
							}
						}
						break;
					
						case GameMap::East:
						{
							if(hasBeenVisited[tempPosition.x+1 + GameMap::getSingleton().dimension.x*tempPosition.y ]==false)
							{
								PathFindNode *newnode = new PathFindNode( PointI(tempPosition.x + 1, tempPosition.y));
								nodepool.push_back(newnode);
								newnode->pre = tempnode;
								breadthFirstQueue.push(newnode);
								hasBeenVisited[tempPosition.x+1+GameMap::getSingleton().dimension.x*tempPosition.y ]=true;
							}
						}
						break;
					
					}
				}
			}
			
			delete [] hasBeenVisited;
		
			if (breadthFirstQueue.size() == 0) 
			{
				//no path;
			
				//error blocked way
			
				//breadthFirstQueue.clear();
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) 
				{
					delete (*iter);
				}
			
				nodepool.clear();
				return ;
			}
			else if (GameMap::getSingleton().isEnd(breadthFirstQueue.front()->pos)) 
			{
				std::deque<PointI> tmppath;
				PathFindNode *tempnode=breadthFirstQueue.front();
				while(tempnode->pre!=NULL)
				{
					tmppath.push_front(tempnode->pos);
					tempnode = tempnode->pre;
				}
			
				tmppath.push_front( tempnode->pos);
				for (std::deque<PointI>::iterator iter=tmppath.begin(); iter!=tmppath.end(); ++iter) 
				{
					PointI p((*iter).x,(*iter).y);
					path.push_back(p);
				}
			
				pathStep=0;
				for (std::vector<PathFindNode*>::iterator iter=nodepool.begin(); iter!=nodepool.end(); ++iter) 
				{
					delete (*iter);
				}
			
				nodepool.clear();
				return ;
			}
			return ;
		}
	}
}