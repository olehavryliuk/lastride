//Author Oleh Havryliuk 07.2015
#ifndef __I_OBSTACLE_H_INCLUDED__
#define __I_OBSTACLE_H_INCLUDED__

class irr::scene::ISceneNode;

class IObstacle
{
public:
	virtual bool intersectsWithObject(irr::scene::ISceneNode* object) = 0;
};

#endif