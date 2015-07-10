//Author Oleh Havryliuk 07.2015
#ifndef __CUBIC_SCENE_NODE_H_INCLUDED__
#define __CUBIC_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>

class CubicSceneNode : public irr::scene::ISceneNode
{
private:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[4];
	irr::video::S3DVertex m_vertices[24];
	irr::video::SMaterial m_material[6];

public:
	CubicSceneNode(irr::scene::ISceneNode* parent, 
				    irr::scene::ISceneManager* mgr,
					irr::s32 id,
					irr::video::ITexture* front,
					irr::video::ITexture* bottom,
					irr::video::ITexture* left,
					irr::video::ITexture* back,
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