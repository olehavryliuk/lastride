//Author Oleh Havryliuk 07.2015

#include "ShaderManager.h"
#include "GameManager.h"
#include "Shaders/ShaderPathConstants.h"
#include "Shaders/ShaderConstantSetCallBacks/BumpParallaxShaderCallBack.h"

ShaderManager::ShaderManager(GameManager* gameManager)
{
	m_gameManager		= gameManager;
	m_gpu				= 0;

	irr::video::IVideoDriver* driver = m_gameManager->getDevice()->getVideoDriver();
	m_videoDriverType	= driver->getDriverType(); 
	m_gpu				= driver->getGPUProgrammingServices();
	m_bumpMaterial		= 0;
	m_parallaxMaterial	= 0;
}

irr::s32 ShaderManager::initBumpMaterial()
{
	if (m_gpu)
	{
		irr::io::path vsFileName;		// filename for the vertex shader
		irr::io::path psFileName;		// filename for the pixel shader

		if (m_videoDriverType == irr::video::EDT_DIRECT3D9)
		{
			vsFileName = BUMP_HLSL_VERTEX_SHADER_PATH;
			psFileName = BUMP_HLSL_PIXEL_SHADER_PATH;
		}
		else if (m_videoDriverType == irr::video::EDT_OPENGL)
		{
//opengl shader path	
		}
		else
		{
			return 0;
		}

		BumpParallaxShaderCallBack* shaderCallBack = new BumpParallaxShaderCallBack(m_gameManager->getDevice());

		m_bumpMaterial = m_gpu->addHighLevelShaderMaterialFromFiles(
						vsFileName, "main", irr::video::EVST_VS_3_0,
						psFileName, "main", irr::video::EPST_PS_3_0,
						shaderCallBack, 
						irr::video::EMT_SOLID,
						0,
						irr::video::EGSL_DEFAULT);

		shaderCallBack->drop();

		return m_bumpMaterial;
	}

	return 0;
}

irr::s32 ShaderManager::initParallaxMaterial()
{


	return 0;
}

irr::s32 ShaderManager::getBumpMaterial()
{
	return m_bumpMaterial;
}

irr::s32 ShaderManager::getParallaxMaterial()
{
	return m_parallaxMaterial;
}