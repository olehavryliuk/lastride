//Author Oleh Havryliuk 07.2015
#include "WallSceneNode.h"
#include "Constants.h"

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
	irr::core::aabbox3d<irr::f32> thisNodeBox = getTransformedBoundingBox();
	irr::core::aabbox3d<irr::f32> objectNodeBox = object->getTransformedBoundingBox();
	thisNodeBox.repair();
	objectNodeBox.repair();
	return thisNodeBox.intersectsWithBox(objectNodeBox);
}

bool WallSceneNode::isNearObject(irr::scene::ISceneNode* object)
{
	irr::core::aabbox3d<irr::f32> objectNodeBox = object->getTransformedBoundingBox();
	irr::core::aabbox3d<irr::f32> increasedBoundingBox = m_box;
	increasedBoundingBox.MinEdge *= BOX_INCREASE_MULTIPLIER;
	increasedBoundingBox.MaxEdge *= BOX_INCREASE_MULTIPLIER;
	AbsoluteTransformation.transformBoxEx(increasedBoundingBox);
	increasedBoundingBox.repair();
	objectNodeBox.repair();

	return increasedBoundingBox.intersectsWithBox(objectNodeBox);
}