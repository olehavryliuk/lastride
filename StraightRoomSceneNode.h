//Author Oleh Havryliuk 07.2015
#ifndef __STRAIGHT_ROOM_SCENE_NODE_H_INCLUDED__
#define __STRAIGHT_ROOM_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include "Constants.h"

class StraightRoomSceneNode : public irr::scene::ISceneNode
{
protected:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[MAX_STRAIGHT_SECTIONS*24];
	//irr::video::S3DVertex m_vertices[(MAX_STRAIGHT_SECTIONS+1)*4];
	irr::video::S3DVertexTangents m_vertices[(MAX_STRAIGHT_SECTIONS+1)*4];
	irr::core::vector3df m_halfSize;
	irr::u32 m_verticesCount;
	irr::u32 m_sectionCount;
	irr::video::SMaterial m_material;

public:
	StraightRoomSceneNode(irr::scene::ISceneNode* parent,
						irr::scene::ISceneManager* mgr,
						irr::s32 id,
						irr::video::ITexture* diffuseTexture,
						irr::video::ITexture* normalMapTexture = nullptr,
						irr::u32 sectionCount = 1,
						const irr::core::vector3df& halfSize = ROOM_PROPORTIONS,
						const irr::core::vector3df& position = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& rotation = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));

	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
	virtual irr::u32 getVertexCount() const;
	virtual const irr::video::S3DVertexTangents* getVertices() const;
	virtual irr::core::vector3df centerPositionTransformedForSection(irr::u32 sectionNumber);
	virtual irr::core::vector3df centerPositionForSection(irr::u32 sectionNumber);
};

#endif