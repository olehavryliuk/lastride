#include <irrlicht.h>

class VertexRoomSceneNode : public irr::scene::ISceneNode
{
private:
	irr::core::aabbox3d<irr::f32> m_box;
	irr::u16 m_indices[4];
	irr::video::S3DVertex m_vertices[16];
	irr::video::SMaterial m_material[4];

public:
	VertexRoomSceneNode(irr::scene::ISceneNode* parent, 
						irr::scene::ISceneManager* mgr,
						irr::video::ITexture* bottom,
						irr::video::ITexture* left,
						irr::video::ITexture* top,
						irr::video::ITexture* right,
						irr::s32 id);
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
};