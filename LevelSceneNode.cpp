//Author Oleh Havryliuk 07.2015
#include "LevelSceneNode.h"
#include "SquareRoomSceneNode.h"
#include "Constants.h"
#include "StraightRoomSceneNode.h"
#include "WallSceneNode.h"
#include "GameManager.h"

LevelSceneNode::LevelSceneNode(GameManager* gameManager,
							   irr::IrrlichtDevice* device,
							   irr::scene::ISceneNode* parent, 
							   irr::scene::ISceneManager* sceneManager) : 
							   irr::scene::ISceneNode(parent, sceneManager)
{
	m_gameManager = gameManager;
	m_device = device;
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();
	m_currentObstacle = nullptr;
	m_currentRoomNode = nullptr;
	m_vehicle= nullptr;
	m_cameraNode = nullptr;
	m_lightNode = nullptr;
	m_currentSection = 0;
	m_currentFacePosition = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_currentFaceRotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_lastTime = 0;
	m_finished = false;
	m_isScratchingWalls = false;
	m_scratchedWallLR = D_NONE;
	m_scratchedWallDU = D_NONE;

//camera target animation
	m_animatingCameraTarget = false;
//	m_cameraTargetAnimationCount = 0;
//	m_cameraTargetAnimationStep = 0;
	m_cameraTargetAnimationDelta = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_cameraTargetAnimationEnd = irr::core::vector3df(0.0f, 0.0f, 0.0f);

//navigation points
	m_currentNavigationPointIndex = 0;
	m_distanceFullBNP = 0.0f;
	m_distancePassedBNP = 0.0f;

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

//input
	m_inputPositionDelta = irr::core::vector3df(0.0f, 0.0f, 0.0f);
}

LevelSceneNode::~LevelSceneNode()
{
	delete m_vehicle;
}

bool LevelSceneNode::addVehicleTo(irr::scene::ISceneNode* parent)
{
	m_vehicle = new Vehicle();
	if (!m_vehicle->initVehicle(parent, m_sceneManager, MODEL_PATH + VEHICLE_MODEL_NAME_DEFAULT))
		return false;

	//m_vehicle->m_sceneNode->setVisible(false);

//add spot light to vehicle
	irr::scene::ILightSceneNode* m_lightNode = m_sceneManager->addLightSceneNode(m_vehicle->m_sceneNode,
																				LIGHT_POSITION,
																				LIGHT_COLOR, 
																				LIGHT_RADIUS);
	irr::video::SLight& light = m_lightNode->getLightData();
	light.Type = irr::video::ELT_SPOT;
	light.OuterCone = 40.0f;
	m_lightNode->setRotation(irr::core::vector3df(0.0f, 180.0f, 0.0f));

//navigation points
	if (!m_navigationPoints.empty())
	{
		m_currentDistanceVector = m_navigationPoints[m_currentNavigationPointIndex];
		m_distanceFullBNP = sqrtf(m_currentDistanceVector.X * m_currentDistanceVector.X + 
										   m_currentDistanceVector.Y * m_currentDistanceVector.Y +
										   m_currentDistanceVector.Z * m_currentDistanceVector.Z);
		m_normalizedDistanceVector = m_currentDistanceVector / m_distanceFullBNP;
		m_distancePassedBNP = 0.0f;

//update rotation
		irr::core::matrix4 absoluteTransformMatrix = m_vehicle->m_sceneNode->getAbsoluteTransformation();
		irr::core::matrix4 rotationMatrix;
		rotationMatrix.buildRotateFromTo(m_vehicle->m_speedVector, m_normalizedDistanceVector);
		absoluteTransformMatrix = rotationMatrix * absoluteTransformMatrix;
		m_vehicle->m_sceneNode->setRotation(absoluteTransformMatrix.getRotationDegrees());

//update speed vector
		m_vehicle->m_speedVector = m_normalizedDistanceVector * m_vehicle->m_speedScalar;
		
		m_lastTime = m_device->getTimer()->getTime();
	}

	return true;
}

bool LevelSceneNode::loadTestLevel()
{
	if (!m_sceneManager)
		return false;

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
	
	irr::scene::ILightSceneNode* lightNode = m_sceneManager->addLightSceneNode(0,
																				irr::core::vector3df(0.0f , 0.0f, -50.0f),
																				irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 
																				700.0f);
	irr::video::SLight& light = lightNode->getLightData();
	light.Type = irr::video::ELT_SPOT;
	light.OuterCone = 40.0f;
	lightNode->setParent(m_sceneManager->getActiveCamera());

	return true;									
}

bool LevelSceneNode::loadLevelFromXML(const irr::io::path& filePath)
{
	irr::io::IXMLReader* xml = m_device->getFileSystem()->createXMLReader(filePath);
	if (!xml)
		return false;

	irr::core::stringw currentNode;
	irr::core::stringw attribute;
	irr::u32 sectionsCount;
	irr::f32 angle;

	while (xml->read())
	{
		switch (xml->getNodeType())
		{
			case irr::io::EXN_ELEMENT:
			{
				currentNode = xml->getNodeName();
				if (currentNode.equals_ignore_case(L"straight"))
				{
					sectionsCount = xml->getAttributeValueAsInt(L"sections");
				}
				else if (currentNode.equals_ignore_case(L"left"))
				{
					sectionsCount = xml->getAttributeValueAsInt(L"sections");
					angle = xml->getAttributeValueAsFloat(L"angle");
					addCurveNode(sectionsCount, angle, D_LEFT);
				}
				else if (currentNode.equals_ignore_case(L"right"))
				{
					sectionsCount = xml->getAttributeValueAsInt(L"sections");
					angle = xml->getAttributeValueAsFloat(L"angle");
					addCurveNode(sectionsCount, angle, D_RIGHT);				
				}
				else if (currentNode.equals_ignore_case(L"down"))
				{
					sectionsCount = xml->getAttributeValueAsInt(L"sections");
					angle = xml->getAttributeValueAsFloat(L"angle");
					addCurveNode(sectionsCount, angle, D_DOWN);				
				}
				else if (currentNode.equals_ignore_case(L"up"))
				{
					sectionsCount = xml->getAttributeValueAsInt(L"sections");
					angle = xml->getAttributeValueAsFloat(L"angle");
					addCurveNode(sectionsCount, angle, D_UP);				
				}
			}
			break;
			case irr::io::EXN_TEXT:
			{
				if (currentNode.equals_ignore_case(L"straight"))
				{
					m_obstacleString = xml->getNodeData();
					addStraightNode(sectionsCount, m_obstacleString.trim());
				}
			}
			break;
			case irr::io::EXN_ELEMENT_END:
				currentNode=L"";
			break;
		}
	}
	xml->drop();

//vehicle
	if (!addVehicleTo(m_sceneManager->getRootSceneNode()))
		return false;

//camera
	if(!addCameraTo(m_vehicle->m_sceneNode))
		return false;

	return true;
}

const irr::core::aabbox3d<irr::f32>& LevelSceneNode::getBoundingBox() const
{
	return m_box;
}

void LevelSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void LevelSceneNode::render()
{

}

void LevelSceneNode::update()
{
	if (m_vehicle && !m_finished)
	{
		irr::u32 newTime = m_device->getTimer()->getTime();
		irr::f32 deltaTimeInSeconds = (float)(newTime - m_lastTime) / 1000.0f;
		m_lastTime = newTime;

//process key input
		processInput(deltaTimeInSeconds);

//nav points
		irr::core::vector3df vehiclePosition = m_vehicle->m_sceneNode->getPosition();
		irr::core::vector3df leftToNavPointVector = m_normalizedDistanceVector * (m_distanceFullBNP - m_distancePassedBNP);
		m_distancePassedBNP += m_vehicle->m_speedScalar * deltaTimeInSeconds;
		if (m_distancePassedBNP > m_distanceFullBNP)
		{
			m_distancePassedBNP = m_distancePassedBNP - m_distanceFullBNP;
			m_currentNavigationPointIndex++;
			if (m_currentNavigationPointIndex >= m_navigationPoints.size())
			{
				m_finished = true;
				return;
			}
			m_currentDistanceVector = m_navigationPoints[m_currentNavigationPointIndex] - m_navigationPoints[m_currentNavigationPointIndex-1];
			m_distanceFullBNP = sqrtf(m_currentDistanceVector.X * m_currentDistanceVector.X + 
										   m_currentDistanceVector.Y * m_currentDistanceVector.Y +
										   m_currentDistanceVector.Z * m_currentDistanceVector.Z);
			irr::core::vector3df oldNormalizedDistanceVector = m_normalizedDistanceVector;
			m_normalizedDistanceVector = m_currentDistanceVector / m_distanceFullBNP;

//update rotation and input translation
			irr::core::matrix4 rotationMatrix;
			rotationMatrix.buildRotateFromTo(m_vehicle->m_speedVector, m_normalizedDistanceVector);
			irr::core::matrix4 absoluteTransformMatrix = m_vehicle->m_sceneNode->getAbsoluteTransformation();
			absoluteTransformMatrix = rotationMatrix * absoluteTransformMatrix;
			m_vehicle->m_sceneNode->setRotation(absoluteTransformMatrix.getRotationDegrees());

//update speed vector
			m_vehicle->m_speedVector = m_normalizedDistanceVector * m_vehicle->m_speedScalar;

			vehiclePosition += leftToNavPointVector + m_normalizedDistanceVector * m_distancePassedBNP;

//update camera
			m_cameraNode->setTarget(vehiclePosition + (oldNormalizedDistanceVector * CAMERA_TARGET_DISTANCE));
			startCameraTargetAnimation(oldNormalizedDistanceVector * CAMERA_TARGET_DISTANCE, m_normalizedDistanceVector * CAMERA_TARGET_DISTANCE);

			irr::core::vector3df cameraUpVector = m_cameraNode->getUpVector();
			rotationMatrix.transformVect(cameraUpVector);
			m_cameraNode->setUpVector(cameraUpVector);
		}
		else
		{
			vehiclePosition += m_vehicle->m_speedVector * deltaTimeInSeconds;
		}

		m_vehicle->m_sceneNode->setPosition(vehiclePosition);

//animate camera target
		animateCameraTarget();

		//m_vehicle->update(deltaTimeInSeconds);
	}
}

bool LevelSceneNode::addStraightNode(irr::u32 sectionsCount, irr::core::stringw initString)
{
	if (!m_sceneManager)
		return false;
	StraightRoomSceneNode* straightNode = new StraightRoomSceneNode(this,
											m_sceneManager,
											-1,
											m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
											sectionsCount,
											ROOM_PROPORTIONS,
											m_currentFacePosition,
											m_currentFaceRotation,
											ROOM_SCALE);
	straightNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

//add navigation points
	const irr::u32 vertexCount = straightNode->getVertexCount();
	const irr::video::S3DVertex* vertices = straightNode->getVertices();
	irr::core::matrix4 absoluteTransform = straightNode->getAbsoluteTransformation();
	irr::core::vector3df navigationPoint;
	for (irr::u32 i = 4; i < vertexCount; i+=4)
	{
		navigationPoint = (vertices[i].Pos + vertices[2+i].Pos) / 2.0f;
		absoluteTransform.transformVect(navigationPoint);
		m_navigationPoints.push_back(navigationPoint);
	}

//adding obstacles to node
	for (irr::u32 i = 0; i < initString.size(); i++)
	{
		switch (initString[i])
		{
		case 'l':
			addObstacleTo(straightNode, i, OT_WALL, OP_LEFT_1_2);
			break;
		case 'r':
			addObstacleTo(straightNode, i, OT_WALL, OP_RIGHT_1_2);
			break;
		case 'b':
			addObstacleTo(straightNode, i, OT_WALL, OP_BOTTOM_1_2);
			break;
		case 't':
			addObstacleTo(straightNode, i, OT_WALL, OP_TOP_1_2);
			break;
		case 'L':
			addObstacleTo(straightNode, i, OT_WALL, OP_LEFT_2_3);
			break;
		case 'R':
			addObstacleTo(straightNode, i, OT_WALL, OP_RIGHT_2_3);
			break;
		case 'B':
			addObstacleTo(straightNode, i, OT_WALL, OP_BOTTOM_2_3);
			break;
		case 'T':
			addObstacleTo(straightNode, i, OT_WALL, OP_TOP_2_3);
			break;
		default:
			break;
		}
	}

//changing current face position and direction
	irr::core::matrix4 transformMatrix;
	irr::core::vector3df newTranslation = irr::core::vector3df(0.0f, 0.0f, ROOM_SCALE.Z * ROOM_PROPORTIONS.Z * (float)(2 * sectionsCount));
	transformMatrix.setRotationDegrees(m_currentFaceRotation);
	transformMatrix.transformVect(newTranslation);
	m_currentFacePosition += newTranslation;

//add to node blocks array
	//m_nodeBlocks.push_back(NodeBlock(BT_STRAIGHT, D_FORWARD, 0.0f, sectionsCount, initString));

	straightNode->drop();

	return true;
}

bool LevelSceneNode::addCurveNode(irr::u32 sectionsCount, irr::f32 angle, DIRECTION direction, irr::core::stringw initString)
{
	CurveRoomSceneNode* curveNode = new CurveRoomSceneNode(this,
										m_sceneManager,
										direction,
										angle,
										CURVE_RADIUS,
										sectionsCount,
										-1,
										m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
										ROOM_PROPORTIONS,
										m_currentFacePosition,
										m_currentFaceRotation,
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

//add navigation points
	const irr::u32 vertexCount = curveNode->getVertexCount();
	const irr::video::S3DVertex* vertices = curveNode->getVertices();
	irr::core::matrix4 absoluteTransform = curveNode->getAbsoluteTransformation();
	irr::core::vector3df navigationPoint;
	for (irr::u32 i = 4; i < vertexCount; i+=4)
	{
		navigationPoint = (vertices[i].Pos + vertices[2+i].Pos) / 2.0f;
		absoluteTransform.transformVect(navigationPoint);
		m_navigationPoints.push_back(navigationPoint);
	}

//changing current face position and rotation
	irr::core::vector3df newRotation;
	irr::core::vector3df newTranslation;
	irr::f32 angleInRadians = angle * irr::core::PI / 180.0f; 
	switch (direction)
	{
	case D_LEFT:
		newRotation = irr::core::vector3df(0.0f, -angle, 0.0f);
		newTranslation = irr::core::vector3df(CURVE_RADIUS * ROOM_SCALE.X * (cos(angleInRadians) - 1.0f), 0.0f, CURVE_RADIUS * ROOM_SCALE.Z * sin(angleInRadians));
		break;
	case D_RIGHT:
		newRotation = irr::core::vector3df(0.0f, angle, 0.0f);
		newTranslation = irr::core::vector3df(CURVE_RADIUS * ROOM_SCALE.X * (-cos(angleInRadians) + 1.0f), 0.0f, CURVE_RADIUS * ROOM_SCALE.Z * sin(angleInRadians));
		break;
	case D_DOWN:
		newRotation = irr::core::vector3df(angle, 0.0f, 0.0f);
		newTranslation = irr::core::vector3df(0.0f, CURVE_RADIUS * ROOM_SCALE.Y * (cos(angleInRadians) - 1.0f), CURVE_RADIUS * ROOM_SCALE.Z * sin(angleInRadians));
		break;
	case D_UP:
		newRotation = irr::core::vector3df(-angle, 0.0f, 0.0f);
		newTranslation = irr::core::vector3df(0.0f, CURVE_RADIUS * ROOM_SCALE.X * (-cos(angleInRadians) + 1.0f), CURVE_RADIUS * ROOM_SCALE.Z * sin(angleInRadians));
		break;
	}

	irr::core::matrix4 newRotationMatrix;
	irr::core::matrix4 transformMatrix;
	transformMatrix.setRotationDegrees(m_currentFaceRotation);
	newRotationMatrix.setRotationDegrees(newRotation);
	transformMatrix.transformVect(newTranslation);
	newRotationMatrix = transformMatrix * newRotationMatrix;
	m_currentFaceRotation = newRotationMatrix.getRotationDegrees();
	m_currentFacePosition += newTranslation;

//add to node blocks array
	//m_nodeBlocks.push_back(NodeBlock(BT_STRAIGHT, D_FORWARD, 0.0f, sectionsCount, initString));

	curveNode->drop();

	return true;
}

bool LevelSceneNode::addObstacleTo(irr::scene::ISceneNode* parent, irr::u32 sectionNumber, OBSTACLE_TYPE obstacleType, OBSTACLE_POSITION obstaclePosition)
{
	irr::scene::ISceneNode* obstacleNode;
	irr::core::vector3df halfSize;
	irr::core::vector3df position;
	irr::core::vector3df rotation;
	//irr::core::vector3df scale;

	if (obstacleType == OT_WALL)
	{
		switch(obstaclePosition)
		{
		case OP_LEFT_1_2:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.Y, ROOM_PROPORTIONS.X / 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(-ROOM_PROPORTIONS.X / 2.0f, 0.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 90.0f);
			break;
		case OP_RIGHT_1_2:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.Y, ROOM_PROPORTIONS.X / 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(ROOM_PROPORTIONS.X / 2.0f, 0.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 90.0f);
			break;
		case OP_BOTTOM_1_2:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.X, ROOM_PROPORTIONS.Y / 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(0.0f, -ROOM_PROPORTIONS.Y / 2.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
			break;
		case OP_TOP_1_2:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.X, ROOM_PROPORTIONS.Y / 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(0.0f, ROOM_PROPORTIONS.Y / 2.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
			break;
		case OP_LEFT_2_3:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.Y, ROOM_PROPORTIONS.X * 2.0f / 3.0f, WALL_WIDTH);
			position = irr::core::vector3df(-ROOM_PROPORTIONS.X / 3.0f, 0.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 90.0f);
			break;
		case OP_RIGHT_2_3:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.Y, ROOM_PROPORTIONS.X * 2.0f / 3.0f, WALL_WIDTH);
			position = irr::core::vector3df(ROOM_PROPORTIONS.X / 3.0f, 0.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 90.0f);
			break;
		case OP_BOTTOM_2_3:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.X, ROOM_PROPORTIONS.Y / 3.0f * 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(0.0f, -ROOM_PROPORTIONS.Y / 3.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
			break;
		case OP_TOP_2_3:
			halfSize = irr::core::vector3df(ROOM_PROPORTIONS.X, ROOM_PROPORTIONS.Y / 3.0f * 2.0f, WALL_WIDTH);
			position = irr::core::vector3df(0.0f, ROOM_PROPORTIONS.Y / 3.0f, ROOM_PROPORTIONS.Z * (float)(2 * sectionNumber + 1));
			rotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
			break;
		default:
			break;
		}

		obstacleNode = new WallSceneNode(parent,
										m_sceneManager,
										-1,
										m_driver->getTexture(TEXTURE_PATH + WALL_TEXTURE_NAME_DEFAULT),
										halfSize,
										position,
										rotation);
		obstacleNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		obstacleNode->drop();
	}
	else if (obstacleType == OT_MINE)
	{
		
	}

	return true;
}

bool LevelSceneNode::addCameraTo(irr::scene::ISceneNode* parent)
{
	m_cameraNode = m_sceneManager->addCameraSceneNode(parent);
	m_cameraNode->setPosition(CAMERA_POSITION);
	m_currentCameraTarget = irr::core::vector3df(0.0f, 0.0f, CAMERA_TARGET_DISTANCE);
	m_cameraNode->setTarget(m_currentCameraTarget);
	startCameraTargetAnimation(m_currentCameraTarget, m_normalizedDistanceVector * CAMERA_TARGET_DISTANCE);

	//m_sceneManager->addCameraSceneNodeFPS();

	return true;
}

void LevelSceneNode::processInput(irr::f32 deltaTimeInSeconds)
{
	irr::core::vector3df inputVector = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	const GameEventReceiver* gameEventReceiver = m_gameManager->getEventReceiver();
	
	if(m_scratchedWallDU != D_UP && (gameEventReceiver->IsKeyDown(irr::KEY_KEY_W) || gameEventReceiver->IsKeyDown(irr::KEY_UP)))
		inputVector = irr::core::vector3df(0.0f, KEY_REACTION_SPEED_DEFAULT * deltaTimeInSeconds, 0.0f);
	else if(m_scratchedWallDU != D_DOWN && (gameEventReceiver->IsKeyDown(irr::KEY_KEY_S) || gameEventReceiver->IsKeyDown(irr::KEY_DOWN)))
		inputVector = irr::core::vector3df(0.0f, -KEY_REACTION_SPEED_DEFAULT * deltaTimeInSeconds, 0.0f);
	
	if(m_scratchedWallLR != D_LEFT && (gameEventReceiver->IsKeyDown(irr::KEY_KEY_A) || gameEventReceiver->IsKeyDown(irr::KEY_LEFT)))
		inputVector += irr::core::vector3df(KEY_REACTION_SPEED_DEFAULT * deltaTimeInSeconds, 0.0f, 0.0f);
	else if(m_scratchedWallLR != D_RIGHT && (gameEventReceiver->IsKeyDown(irr::KEY_KEY_D) || gameEventReceiver->IsKeyDown(irr::KEY_RIGHT)))
		inputVector += irr::core::vector3df(-KEY_REACTION_SPEED_DEFAULT * deltaTimeInSeconds, 0.0f, 0.0f);

	m_inputPositionDelta += inputVector * VEHICLE_SCALE;
	checkForWallCollisions();

	irr::core::matrix4 translationMatrix;
	translationMatrix.setTranslation(inputVector);
	translationMatrix = m_vehicle->m_sceneNode->getAbsoluteTransformation() * translationMatrix;
	inputVector = translationMatrix.getTranslation();
	m_vehicle->m_sceneNode->setPosition(inputVector);
}

void LevelSceneNode::resetLevel()
{
	m_currentSection = 0;
	m_currentFacePosition = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_currentFaceRotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_lastTime = 0;
	m_finished = false;
	m_isScratchingWalls = false;
	m_scratchedWallLR = D_NONE;
	m_scratchedWallDU = D_NONE;
	m_animatingCameraTarget = false;

//navigation points
	m_currentNavigationPointIndex = 0;
	m_distanceFullBNP = 0.0f;
	m_distancePassedBNP = 0.0f;

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

//camera target animation
	m_animatingCameraTarget = false;
//	m_cameraTargetAnimationCount = 0;
//	m_cameraTargetAnimationStep = 0;
	m_cameraTargetAnimationDelta = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_cameraTargetAnimationEnd = irr::core::vector3df(0.0f, 0.0f, 0.0f);

//input
	m_inputPositionDelta = irr::core::vector3df(0.0f, 0.0f, 0.0f);
}

void LevelSceneNode::checkForWallCollisions()
{
	irr::core::vector3df roomHalfSize = ROOM_PROPORTIONS * ROOM_SCALE;
	irr::core::aabbox3d<irr::f32> vehicleBoundingBox = m_vehicle->m_sceneNode->getBoundingBox();
	vehicleBoundingBox.MinEdge *= VEHICLE_SCALE.X;
	vehicleBoundingBox.MaxEdge *= VEHICLE_SCALE.X;

//center bounding box at (0.0f, 0.0f, 0.0f)
	irr::core::vector3df edgeDiff = (vehicleBoundingBox.MaxEdge - vehicleBoundingBox.MinEdge) / 2.0f;

	if (-edgeDiff.X + m_inputPositionDelta.X <= -roomHalfSize.X)
		m_scratchedWallLR = D_RIGHT;
	else if (edgeDiff.X + m_inputPositionDelta.X >= roomHalfSize.X)
		m_scratchedWallLR = D_LEFT;
	else
		m_scratchedWallLR = D_NONE;

	if (-edgeDiff.Y + m_inputPositionDelta.Y <= -roomHalfSize.Y)
		m_scratchedWallDU = D_DOWN;
	else if (-edgeDiff.Y + m_inputPositionDelta.Y >= roomHalfSize.Y)
		m_scratchedWallDU = D_UP;
	else
		m_scratchedWallDU = D_NONE;

	if (m_scratchedWallLR == D_NONE && m_scratchedWallDU == D_NONE)
		m_isScratchingWalls = false;
	else
		m_isScratchingWalls = true;
}

//camera target animation
void LevelSceneNode::startCameraTargetAnimation(irr::core::vector3df startPosition, irr::core::vector3df endPosition)
{
	m_cameraTargetAnimationStart = startPosition;
	m_animatingCameraTarget = true;
	m_cameraTargetAnimationDelta = endPosition - m_cameraTargetAnimationStart;
	m_cameraTargetAnimationEnd = endPosition;
	m_currentCameraTarget = m_cameraTargetAnimationStart;
}

void LevelSceneNode::animateCameraTarget()
{
	if (m_animatingCameraTarget)
	{
		if (m_distancePassedBNP < m_distanceFullBNP)
		{
			irr::core::vector3df newCameraTarget = m_cameraTargetAnimationStart + (m_cameraTargetAnimationDelta * (m_distancePassedBNP / m_distanceFullBNP));

//animate vehicle rotation
			irr::core::matrix4 rotationMatrix;
			rotationMatrix.buildRotateFromTo(m_currentCameraTarget, newCameraTarget);
			irr::core::matrix4 absoluteTransformMatrix = m_vehicle->m_sceneNode->getAbsoluteTransformation();
			rotationMatrix = rotationMatrix * absoluteTransformMatrix;
			m_vehicle->m_sceneNode->setRotation(rotationMatrix.getRotationDegrees());

			m_currentCameraTarget = newCameraTarget;
			m_cameraNode->setTarget(m_currentCameraTarget);
		}
		else
		{
			m_animatingCameraTarget = false;
			m_cameraNode->setTarget(m_cameraTargetAnimationEnd);
		}
	}
}