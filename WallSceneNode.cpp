//Author Oleh Havryliuk 07.2015
#include "WallSceneNode.h"

WallSceneNode::WallSceneNode(irr::scene::ISceneNode* parent, 
							irr::scene::ISceneManager* mgr,
							irr::s32 id,
							irr::video::ITexture* texture,
							const irr::core::vector3df& halfSize,
							const irr::core::vector3df& position,
							const irr::core::vector3df& rotation,
							const irr::core::vector3df& scale) :
							CubicSceneNode(parent, mgr, id, texture, halfSize, position, rotation, scale)
{
}

bool WallSceneNode::intersectsWithObject(irr::scene::ISceneNode* object)
{
	return getBoundingBox().intersectsWithBox(object->getBoundingBox());
}