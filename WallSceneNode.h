//Author Oleh Havryliuk 07.2015
#ifndef __WALL_SCENE_NODE_H_INCLUDED__
#define __WALL_SCENE_NODE_H_INCLUDED__

#include "CubicSceneNode.h"
#include "IObstacle.h"

class WallSceneNode : public CubicSceneNode, public IObstacle
{
public:
	WallSceneNode(irr::scene::ISceneNode* parent, 
				    irr::scene::ISceneManager* mgr,
					irr::s32 id,
					irr::video::ITexture* texture,
					const irr::core::vector3df& halfSize = irr::core::vector3df(3.0f,1.0f,4.0f),
					const irr::core::vector3df& position = irr::core::vector3df(0.0f,0.0f,0.0f),
					const irr::core::vector3df& rotation = irr::core::vector3df(0.0f,0.0f,0.0f),
					const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));

	virtual bool intersectsWithObject(ISceneNode* object);
};

#endif