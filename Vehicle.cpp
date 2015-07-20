//Author Oleh Havryliuk 07.2015

#include "Vehicle.h"
#include "Constants.h"

Vehicle::Vehicle()
{
	m_sceneNode = nullptr;
	m_speedVector = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	m_speedScalar = 0;
//	m_angleSpeed = 0.0f;
}

Vehicle::~Vehicle()
{
}

bool Vehicle::initVehicle(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* sceneManager ,const irr::io::path& modelPath)
{
	irr::scene::IMesh* mesh = sceneManager->getMesh(modelPath);
    if (!mesh)
    {
        return false;
    }
	m_sceneNode = sceneManager->addMeshSceneNode(mesh, parent);
	m_sceneNode->setScale(VEHICLE_SCALE);
	m_sceneNode->setRotation(irr::core::vector3df(0.0f, 180.0f, 0.0f));
	m_sceneNode->updateAbsolutePosition();
	m_sceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

	m_speedVector = VEHICLE_START_SPEED;
	m_speedScalar = VEHICLE_START_SPEED.Z;
	//m_angleSpeed = VEHICLE_START_SPEED.Z / CURVE_RADIUS;

	return true;
}

void Vehicle::update(irr::u32 deltaTime)
{
	/*
	irr::core::vector3df position = m_sceneNode->getPosition();
	position += m_speedVector * ((float)deltaTime / 1000.0f);
	m_sceneNode->setPosition(position);
*/
}

void Vehicle::increaseSpeedBy(irr::f32 multiplier)
{
	m_speedVector *= multiplier;
	m_speedScalar *= multiplier;
	//m_angleSpeed *= multiplier;
}
/*
void Vehicle::recalculateAngleSpeed()
{
	m_angleSpeed = sqrtf(m_speed.X * m_speed.X + m_speed.Y * m_speed.Y + m_speed.Z * m_speed.Z);
}*/