//Author Oleh Havryliuk 08.2015
#ifndef __MINE_H_INCLUDED__
#define __MINE_H_INCLUDED__

#include <IMeshScenenode.h>
#include "IObstacle.h"

class Mine : public irr::IReferenceCounted, public IObstacle
{
private:
	irr::scene::IMeshSceneNode* m_sceneNode;	//weak ref

public:
	Mine();
	virtual ~Mine();

	bool initMine(irr::scene::ISceneNode* parent, 
				irr::scene::ISceneManager* sceneManager,
				irr::s32 id,
				irr::scene::IMesh* tangentMesh,
				irr::video::ITexture* diffuseTexture = nullptr,
				irr::video::ITexture* normalMapTexture = nullptr,
				const irr::core::vector3df& position = irr::core::vector3df(0.0f,0.0f,0.0f),
				const irr::core::vector3df& rotation = irr::core::vector3df(0.0f,0.0f,0.0f),
				const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
	
	virtual irr::scene::IMeshSceneNode* getSceneNode();

	virtual bool intersectsWithObject(irr::scene::ISceneNode* object);
	virtual bool isNearObject(irr::scene::ISceneNode* object);
};

#endif