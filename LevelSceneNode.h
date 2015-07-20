//Author Oleh Havryliuk 07.2015
#ifndef __LEVEL_SCENE_NODE_H_INCLUDED__
#define __LEVEL_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include "CurveRoomSceneNode.h"
#include "Vehicle.h"
/*
enum BLOCK_TYPE
{
	BT_STRAIGHT = 0,
	BT_CURVE	= 1
};

struct NodeBlock
{
	BLOCK_TYPE m_blockType;
	DIRECTION m_direction;
	irr::f32 m_angle;
	irr::u32 m_sectionCount;
	irr::core::stringw m_obstacleString;

	NodeBlock(BLOCK_TYPE blockType, DIRECTION direction, irr::f32 angle, irr::u32 sectionCount, irr::core::stringw obstacleString) :
			m_blockType(blockType), m_direction(direction), m_angle(angle), m_sectionCount(sectionCount), m_obstacleString(obstacleString)
	{}
};*/

enum OBSTACLE_TYPE
{
	OT_WALL = 0,
	OT_MINE
};

enum OBSTACLE_POSITION
{
	OP_LEFT_1_2 = 0,
	OP_RIGHT_1_2,
	OP_BOTTOM_1_2,
	OP_TOP_1_2,
	OP_LEFT_2_3,
	OP_RIGHT_2_3,
	OP_BOTTOM_2_3,
	OP_TOP_2_3
};

class IObstacle;

class LevelSceneNode : public irr::scene::ISceneNode
{
protected:
	irr::IrrlichtDevice* m_device;               //weak ref
	irr::video::IVideoDriver* m_driver;			//weak ref
	irr::scene::ISceneManager* m_sceneManager;	//weak ref
	irr::core::aabbox3d<irr::f32> m_box;
	IObstacle* m_currentObstacle;				//weak ref
	irr::core::stringw m_obstacleString;
	irr::u32 m_currentSection;
	irr::scene::ISceneNode* m_currentRoomNode;	//weak ref
	irr::core::vector3df m_currentFacePosition;
	irr::core::vector3df m_currentFaceRotation;
	Vehicle* m_vehicle;							//strong ref
	irr::scene::ICameraSceneNode* m_cameraNode;	//weak ref
	irr::scene::ILightSceneNode* m_lightNode;	//weak ref
	irr::u32 m_lastTime;
	bool m_finished;

//navigation points array
	irr::core::array<irr::core::vector3df> m_navigationPoints;
	irr::u32 m_currentNavigationPointIndex;
	irr::core::vector3df m_currentDistanceVector;
	irr::core::vector3df m_normalizedDistanceVector;
	irr::f32 m_distanceFullBNP;
	irr::f32 m_distancePassedBNP;

//node blocks array
//	irr::core::array<NodeBlock> m_nodeBlocks;
//	irr::u32 m_currentNodeBlockIndex;

	bool addVehicleTo(irr::scene::ISceneNode* parent);
	bool addStraightNode(irr::u32 sectionsCount, irr::core::stringw initString);
	bool addCurveNode(irr::u32 sectionsCount, irr::f32 angle, DIRECTION direction, irr::core::stringw initString = "");
	bool addObstacleTo(irr::scene::ISceneNode* parent, irr::u32 sectionNumber, OBSTACLE_TYPE obstacleType, OBSTACLE_POSITION obstaclePosition);

public:
	LevelSceneNode(irr::IrrlichtDevice* device,
				   irr::scene::ISceneNode* parent, 
				   irr::scene::ISceneManager* sceneManager);
	~LevelSceneNode();
	bool loadTestLevel();
	bool loadLevelFromXML(const irr::io::path& filePath);
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual void OnRegisterSceneNode();
	virtual void update();
	virtual void render();
};

#endif