//Author Oleh Havryliuk 07.2015
#ifndef __VEHICLE_H_INCLUDED__
#define __VEHICLE_H_INCLUDED__

#include <irrlicht.h>

class Vehicle
{
public:
	irr::scene::IMeshSceneNode* m_sceneNode;  //weak ref
	irr::core::vector3df m_speedVector;
	irr::f32 m_speedScalar;
	//irr::f32 m_angleSpeed;

	Vehicle();
	virtual ~Vehicle();
	virtual bool initVehicle(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* sceneManager ,const irr::io::path& modelPath);
	virtual void update(irr::u32 deltaTime);
	virtual void increaseSpeedBy(irr::f32 multiplier);

private:
	//void recalculateAngleSpeed();
};

#endif