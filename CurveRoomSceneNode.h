//Author Oleh Havryliuk 07.2015

#ifndef __CURVE_ROOM_SCENE_NODE_H_INCLUDED__
#define __CURVE_ROOM_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include "Constants.h"

enum DIRECTION
{
	D_UP		= 0,
	D_DOWN		= 1,
	D_RIGHT		= 2,
	D_LEFT		= 3,
	D_FORWARD	= 4,
	D_BACKWARD  = 5,
	D_NONE		= 6
};

class CurveRoomSceneNode : public irr::scene::ISceneNode
{
protected:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[MAX_CURVE_SECTIONS*24];
	//irr::video::S3DVertex m_vertices[(MAX_CURVE_SECTIONS+1)*4];
	irr::video::S3DVertexTangents m_vertices[(MAX_CURVE_SECTIONS+1)*4];
	irr::u16 m_verticesCount;
	DIRECTION m_direction;
	irr::f32 m_angle;
	irr::f32 m_radius;
	irr::f32 m_sectionAngle;
	irr::u8 m_sectionCount;
	irr::video::SMaterial m_material;

public:
	CurveRoomSceneNode(irr::scene::ISceneNode* parent,
						irr::scene::ISceneManager* mgr,
						DIRECTION direction,
						irr::f32 angle,
						irr::f32 radius,
						irr::u8 sectionCount,
						irr::s32 id,
						irr::video::ITexture* diffuseTexture,
						irr::video::ITexture* normalMapTexture = nullptr,
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
};

#endif