//Author Oleh Havryliuk 07.2015
#ifndef __SQUARE_ROOM_SCENE_NODE_H_INCLUDED__
#define __SQUARE_ROOM_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>

class SquareRoomSceneNode : public irr::scene::ISceneNode
{
protected:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[4];
	irr::video::S3DVertex m_vertices[16];
	irr::video::SMaterial m_material[4];

public:
	SquareRoomSceneNode(irr::scene::ISceneNode* parent, 
						irr::scene::ISceneManager* mgr,
						irr::s32 id,
						irr::video::ITexture* texture,
						const irr::core::vector3df& halfSize = irr::core::vector3df(3.0f,1.0f,4.0f),
						const irr::core::vector3df& position = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& rotation = irr::core::vector3df(0.0f,0.0f,0.0f),
						const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
	SquareRoomSceneNode(irr::scene::ISceneNode* parent, 
						irr::scene::ISceneManager* mgr,
						irr::s32 id,
						irr::video::ITexture* bottom,
						irr::video::ITexture* left,
						irr::video::ITexture* top,
						irr::video::ITexture* right,
						const irr::core::vector3df& halfSize = irr::core::vector3df(3.0f,1.0f,4.0f),
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