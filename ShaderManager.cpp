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
			vsFileName = BUMP_GLSL_VERTEX_SHADER_PATH;
			psFileName = BUMP_GLSL_FRAGMENT_SHADER_PATH;
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
	if (m_gpu)
	{
		irr::io::path vsFileName = PARALLAX_HLSL_VERTEX_SHADER_PATH;		
		irr::io::path psFileName = PARALLAX_HLSL_PIXEL_SHADER_PATH;	

		irr::video::E_VERTEX_SHADER_TYPE vertexShaderType = irr::video::EVST_VS_3_0;
		irr::video::E_PIXEL_SHADER_TYPE pixelShaderType = irr::video::EPST_PS_3_0;

		if (m_videoDriverType == irr::video::EDT_OPENGL)
		{
			vsFileName = PARALLAX_GLSL_VERTEX_SHADER_PATH;
			psFileName = PARALLAX_GLSL_FRAGMENT_SHADER_PATH;
			vertexShaderType = irr::video::EVST_VS_1_1;
			pixelShaderType = irr::video::EPST_PS_1_1;
		}

		BumpParallaxShaderCallBack* shaderCallBack = new BumpParallaxShaderCallBack(m_gameManager->getDevice());

		m_parallaxMaterial = m_gpu->addHighLevelShaderMaterialFromFiles(
							vsFileName, "main", vertexShaderType,
							psFileName, "main", pixelShaderType,
							shaderCallBack, 
							irr::video::EMT_SOLID,
							0,
							irr::video::EGSL_DEFAULT);

		shaderCallBack->drop();

		return m_parallaxMaterial;
	}

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