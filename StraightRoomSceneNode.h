//Author Oleh Havryliuk 07.2015
#ifndef __STRAIGHT_ROOM_SCENE_NODE_H_INCLUDED__
#define __STRAIGHT_ROOM_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include "Constants.h"

class StraightRoomSceneNode : public irr::scene::ISceneNode
{
private:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[MAX_STRAIGHT_SECTIONS*24];
	irr::video::S3DVertex m_vertices[(MAX_STRAIGHT_SECTIONS+1)*4];
	irr::u16 m_verticesCount;
	irr::u16 m_sectionCount;
	irr::video::SMaterial m_material;

public:
	StraightRoomSceneNode(irr::scene::ISceneNode* parent,
						irr::scene::ISceneManager* mgr,
						irr::s32 id,
						irr::video::ITexture* texture,
						irr::u16 sectionCount = 1,
						const irr::core::vector3df& halfSize = ROOM_PROPORTIONS,
						const irr::core::vector3df& position = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& rotation = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));

	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
};

#endif