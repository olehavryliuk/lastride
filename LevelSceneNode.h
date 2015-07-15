//Author Oleh Havryliuk 07.2015
#ifndef __LEVEL_SCENE_NODE_H_INCLUDED__
#define __LEVEL_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>

class LevelSceneNode : public irr::scene::ISceneNode
{
private:
	irr::IrrlichtDevice* m_device;               //weak ref
	irr::video::IVideoDriver* m_driver;			//weak ref
	irr::scene::ISceneManager* m_sceneManager;	//weak ref
	irr::core::aabbox3d<irr::f32> m_box;

public:
	LevelSceneNode(irr::IrrlichtDevice* device,
				   irr::scene::ISceneNode* parent, 
				   irr::scene::ISceneManager* sceneManager);
	bool loadTestLevel();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual void render();
};

#endif