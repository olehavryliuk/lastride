//Author Oleh Havryliuk 08.2015
#ifndef __SHADER_MANAGER_H_INCLUDED__
#define __SHADER_MANAGER_H_INCLUDED__

#include <irrlicht.h>

class GameManager;

class ShaderManager
{
private:
	GameManager*						 m_gameManager;		//weak ref
	irr::video::IGPUProgrammingServices* m_gpu;				//weak ref
	irr::video::E_DRIVER_TYPE			 m_videoDriverType;

	irr::s32	m_bumpMaterial;
	irr::s32	m_parallaxMaterial;

public:
	ShaderManager(GameManager* gameManager);

	irr::s32 initBumpMaterial();
	irr::s32 initParallaxMaterial();

	irr::s32 getBumpMaterial();
	irr::s32 getParallaxMaterial();
};

#endif