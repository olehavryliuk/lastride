//Author Oleh Havryliuk 07.2015
#include "LevelSceneNode.h"
#include "SquareRoomSceneNode.h"
#include "Constants.h"
#include "StraightRoomSceneNode.h"
#include "WallSceneNode.h"

LevelSceneNode::LevelSceneNode(irr::IrrlichtDevice* device,
							   irr::scene::ISceneNode* parent, 
							   irr::scene::ISceneManager* sceneManager) : 
							   irr::scene::ISceneNode(parent, sceneManager)
{
	m_device = device;
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();
	m_currentObstacle = nullptr;
	m_currentRoomNode = nullptr;
	m_currentSection = 0;
	m_currentFacePosition = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_currentFaceRotation = irr::core::vector3df(0.0f, 0.0f, 0.0f);

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);
}

bool LevelSceneNode::loadTestLevel()
{
	if (!m_sceneManager)
		return false;
/*
	StraightRoomSceneNode* straightNode;

	straightNode = new StraightRoomSceneNode(m_sceneManager->getRootSceneNode(),
											m_sceneManager,
											-1,
											m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
											STRAIGHT_SECTIONS_DEFAULT,
											ROOM_PROPORTIONS,
											irr::core::vector3df(0.0f, 0.0f, 0.0f),
											irr::core::vector3df(0.0f, 0.0f, 0.0f),
											ROOM_SCALE);
	straightNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

	CurveRoomSceneNode* curveNode;
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_UP,
										90.0f,
										CURVE_RADIUS,
										CURVE_SECTIONS,
										-1,
										m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
										ROOM_PROPORTIONS,
										irr::core::vector3df(0.0f, 0.0f, 2 * ROOM_PROPORTIONS.Z * STRAIGHT_SECTIONS_DEFAULT * ROOM_SCALE.Z),
										irr::core::vector3df(0.0f, 0.0f, 0.0f),
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_DOWN,
										180.0f,
										CURVE_RADIUS,
										CURVE_SECTIONS,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										ROOM_PROPORTIONS,
										irr::core::vector3df(0.0f, CURVE_RADIUS * ROOM_SCALE.Y, (CURVE_RADIUS + ROOM_PROPORTIONS.Z) * STRAIGHT_SECTIONS_DEFAULT * ROOM_SCALE.Z),
										irr::core::vector3df(-90.0f, 0.0f, 0.0f),
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_RIGHT,
										90.0f,
										CURVE_RADIUS,
										CURVE_SECTIONS,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(0.0f,-1000.0f,1760.0f),
										irr::core::vector3df(0.0f, 0.0f,0.0f),
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode = new CurveRoomSceneNode(m_sceneManager->getRootSceneNode(),
										m_sceneManager,
										D_LEFT,
										180.0f,
										CURVE_RADIUS,
										CURVE_SECTIONS,
										-1,
										m_driver->getTexture(TEXTURE_PATH + "wall.jpg"),
										irr::core::vector3df(8.0f, 4.0f, 4.0f),
										irr::core::vector3df(500.0f, -1000.0f, 2260.0f),
										irr::core::vector3df(0.0f, 90.0f, 0.0f),
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//curveNode->drop();
	
	//test wall
	addObstacleTo(straightNode, 0, OT_WALL, OP_LEFT_1_2);
	addObstacleTo(straightNode, 1, OT_WALL, OP_LEFT_2_3);
	addObstacleTo(straightNode, 2, OT_WALL, OP_RIGHT_1_2);
	addObstacleTo(straightNode, 3, OT_WALL, OP_RIGHT_2_3);
	addObstacleTo(straightNode, 4, OT_WALL, OP_BOTTOM_1_2);
	addObstacleTo(straightNode, 5, OT_WALL, OP_BOTTOM_2_3);
	addObstacleTo(straightNode, 6, OT_WALL, OP_TOP_1_2);
	addObstacleTo(straightNode, 7, OT_WALL, OP_TOP_2_3);
	addObstacleTo(straightNode, 9, OT_WALL, OP_TOP_1_2);
*/
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

	straightNode->drop();

	return true;
}

bool LevelSceneNode::addCurveNode(irr::u32 sectionsNumber, irr::f32 angle, DIRECTION direction, irr::core::stringw initString)
{
	CurveRoomSceneNode* curveNode = new CurveRoomSceneNode(this,
										m_sceneManager,
										direction,
										angle,
										CURVE_RADIUS,
										sectionsNumber,
										-1,
										m_driver->getTexture(TEXTURE_PATH + ROOM_TEXTURE_NAME_DEFAULT),
										ROOM_PROPORTIONS,
										m_currentFacePosition,
										m_currentFaceRotation,
										ROOM_SCALE);
	curveNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	curveNode->drop();

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
