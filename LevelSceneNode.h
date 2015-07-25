//Author Oleh Havryliuk 07.2015
#ifndef __LEVEL_SCENE_NODE_H_INCLUDED__
#define __LEVEL_SCENE_NODE_H_INCLUDED__

#include <irrlicht.h>
#include "CurveRoomSceneNode.h"
#include "Vehicle.h"

class GameManager;
/*
enum BLOCK_TYPE
{
	BT_STRAIGHT = 0,
	BT_CURVE	= 1
};
*/
struct NodeBlock
{
	DIRECTION m_direction;
	irr::u32 m_sectionCount;
	irr::f32 m_angle;
	irr::core::stringw m_obstacleString;

	NodeBlock(DIRECTION direction, irr::u32 sectionCount, irr::f32 angle, irr::core::stringw obstacleString) :
			m_direction(direction), m_sectionCount(sectionCount), m_angle(angle), m_obstacleString(obstacleString)
	{}
};

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
	GameManager* m_gameManager;					//weak ref	
	irr::IrrlichtDevice* m_device;              //weak ref
	irr::video::IVideoDriver* m_driver;			//weak ref
	irr::scene::ISceneManager* m_sceneManager;	//weak ref
	irr::core::aabbox3d<irr::f32> m_box;

//obstacles
	irr::core::array<IObstacle*> m_obstacles;
	irr::u32 m_currentObstacleIndex;
	irr::core::aabbox3d<irr::f32> m_wideCurrentObstacleBox;
	bool m_wasNearCurrentObstacle;

	irr::scene::ISceneNode* m_currentRoomNode;	//weak ref
	irr::core::vector3df m_currentFacePosition;
	irr::core::vector3df m_currentFaceRotation;
	Vehicle* m_vehicle;							//strong ref
	irr::scene::ICameraSceneNode* m_cameraNode;	//weak ref
	irr::scene::ILightSceneNode* m_lightNode;	//weak ref
	irr::u32 m_lastTime;

//game logic flags
	bool m_finished;
	bool m_isScratchingWalls;
	DIRECTION m_scratchedWallLR;
	DIRECTION m_scratchedWallDU;

	bool m_animatingCameraTarget;
//camera target animation
	irr::core::vector3df m_cameraTargetAnimationDelta;
	irr::core::vector3df m_cameraTargetAnimationStart;
	irr::core::vector3df m_cameraTargetAnimationEnd;
	irr::core::vector3df m_currentCameraTarget;

//navigation points array
	irr::core::array<irr::core::vector3df> m_navigationPoints;
	irr::u32 m_currentNavigationPointIndex;
	irr::core::vector3df m_currentDistanceVector;
	irr::core::vector3df m_normalizedDistanceVector;
	irr::f32 m_distanceFullBNP;
	irr::f32 m_distancePassedBNP;
	irr::f32 m_distanceBNPInputDelta;

//input
	irr::core::vector3df m_inputPositionDelta;

//node blocks array
	irr::core::array<NodeBlock> m_nodeBlocks;
	irr::u32 m_currentNodeBlockIndex;
	irr::u32 m_currentSectionIndex;

	void updateNodeBlocksIndex();

	bool addVehicleTo(irr::scene::ISceneNode* parent);
	bool addStraightNode(irr::u32 sectionsCount, irr::core::stringw initString);
	bool addCurveNode(irr::u32 sectionsCount, irr::f32 angle, DIRECTION direction, irr::core::stringw initString = "");
	bool addObstacleTo(irr::scene::ISceneNode* parent, irr::u32 sectionNumber, OBSTACLE_TYPE obstacleType, OBSTACLE_POSITION obstaclePosition);
	bool addCameraTo(irr::scene::ISceneNode* parent);
	void resetLevel();
	
	void checkForWallCollisions();

	void checkForObstacleCollisions();

//camera target animation
	void startCameraTargetAnimation(irr::core::vector3df startPosition, irr::core::vector3df endPosition);
	void animateCameraTarget();

public:
	LevelSceneNode(GameManager* gameManager,
				   irr::IrrlichtDevice* device,
				   irr::scene::ISceneNode* parent, 
				   irr::scene::ISceneManager* sceneManager);
	~LevelSceneNode();
	bool loadTestLevel();
	bool loadLevelFromXML(const irr::io::path& filePath);
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual void OnRegisterSceneNode();
	virtual void update();
	virtual void render();
	virtual void processInput(irr::f32 deltaTimeInSeconds);
};

#endif