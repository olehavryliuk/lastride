//Author Oleh Havryliuk 07.2015
#include "LevelSceneNode.h"
#include "SquareRoomSceneNode.h"
#include "CurveRoomSceneNode.h"
#include "Constants.h"
#include "StraightRoomSceneNode.h"

LevelSceneNode::LevelSceneNode(irr::IrrlichtDevice* device,
							   irr::scene::ISceneNode* parent, 
							   irr::scene::ISceneManager* sceneManager) : 
							   irr::scene::ISceneNode(parent, sceneManager)
{
	m_device = device;
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);
}

bool LevelSceneNode::loadTestLevel()
{
	if (!m_sceneManager)
		return false;

	StraightRoomSceneNode* straightNode;

	straightNode = new StraightRoomSceneNode(m_sceneManager->getRootSceneNode(),
											m_sceneManager,
											-1,
											m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
											10,
											ROOM_PROPORTIONS,
											irr::core::vector3df(0.0f, 0.0f, -40.0f),
											irr::core::vector3df(0.0f, 0.0f, 0.0f),
											irr::core::vector3df(10.0f, 10.0f, 10.0f));
	straightNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
/*
	//add light
		irr::scene::ILightSceneNode* lightNode = m_sceneManager->addLightSceneNode(0,
																				irr::core::vector3df(0.0f , 0.0f, 0.0f + (float)(i * 8 * 10)),
																				irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 
																				100.0f);
		flag = -flag;
	// attach billboard to light
		irr::scene::IBillboardSceneNode* bNode = m_sceneManager->addBillboardSceneNode(lightNode, irr::core::dimension2d<irr::f32>(5.0f, 5.0f));
		bNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		bNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		bNode->setMaterialTexture(0, m_driver->getTexture(TEXTURE_PATH + "particlewhite.bmp"));
*/
	CurveRoomSceneNode* curveNode;
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_DOWN,
										90.0f,
										50.0f,
										10,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(0.0f, 0.0f, 760.0f),
										irr::core::vector3df(0.0f, 0.0f, 0.0f),
										irr::core::vector3df(10.0f, 10.0f, 10.0f));
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_UP,
										90.0f,
										50.0f,
										10,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(0.0f, -500.0f, 1260.0f),
										irr::core::vector3df(90.0f, 0.0f, 0.0f),
										irr::core::vector3df(10.0f, 10.0f, 10.0f));
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_RIGHT,
										90.0f,
										50.0f,
										10,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(0.0f,-1000.0f,1760.0f),
										irr::core::vector3df(0.0f, 0.0f,0.0f),
										irr::core::vector3df(10.0f, 10.0f, 10.0f));
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_LEFT,
										180.0f,
										40.0f,
										10,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(500.0f, -1000.0f, 2260.0f),
										irr::core::vector3df(0.0f, 90.0f, 0.0f),
										irr::core::vector3df(10.0f, 10.0f, 10.0f));
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

	//add vehicle
	irr::scene::IMesh* mesh = m_sceneManager->getMesh(MODEL_PATH + "Vehicle\\Feisar_Ship.3DS");
    if (!mesh)
    {
        return false;
    }
    irr::scene::IMeshSceneNode* node = m_sceneManager->addMeshSceneNode(mesh);
	node->setPosition(irr::core::vector3df(0.0f, -15.0f, 30.0f));
	node->setRotation(irr::core::vector3df(0.0f, 180.0f, 0.0f));
	node->setScale(irr::core::vector3df(0.05f, 0.05f, 0.05f));
	node->setParent(m_sceneManager->getActiveCamera());
	node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
/*	irr::scene::ISceneNodeAnimator* anim = m_sceneManager->createRotationAnimator(irr::core::vector3df(0.0f,0.4f,0.0f));
		if (anim)
		{
			node->addAnimator(anim);
			anim->drop();
		}*/
	
	irr::scene::ILightSceneNode* lightNode = m_sceneManager->addLightSceneNode(0,
																				irr::core::vector3df(0.0f , 0.0f, -50.0f),
																				irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 
																				700.0f);
	irr::video::SLight& light = lightNode->getLightData();
	light.Type = irr::video::ELT_SPOT;
	light.OuterCone = 40.0f;
	//lightNode->setRotation(irr::core::vector3df(0.0f ,0.0f, 0.0f));
	lightNode->setParent(m_sceneManager->getActiveCamera());
	//animator fly circle
	//anim = m_sceneManager->createFlyCircleAnimator (irr::core::vector3df(0,0,0), 20.0f);
	//lightNode->addAnimator(anim);
	//anim->drop();

	return true;									
}

const irr::core::aabbox3d<irr::f32>& LevelSceneNode::getBoundingBox() const
{
	return m_box;
}

void LevelSceneNode::render()
{

}