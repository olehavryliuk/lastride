//Author Oleh Havryliuk 08.2015

#include <irrlicht.h>
#include "BumpParallaxShaderCallBack.h"
#include "../../Constants.h"

BumpParallaxShaderCallBack::BumpParallaxShaderCallBack(irr::IrrlichtDevice* device)
{
	m_device = device;
	m_material = nullptr;
}

void BumpParallaxShaderCallBack::OnSetMaterial(const irr::video::SMaterial& material)
{
	m_material = &material;
}

void BumpParallaxShaderCallBack::OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
{
	irr::video::IVideoDriver* driver = services->getVideoDriver();

//vertex shader constants
	irr::core::matrix4 matModel;
	irr::core::matrix4 matModelView;
	irr::core::matrix4 matModelViewProj;
	matModel = driver->getTransform(irr::video::ETS_WORLD);
	matModelView = driver->getTransform(irr::video::ETS_VIEW) * matModel;
	matModelViewProj = driver->getTransform(irr::video::ETS_PROJECTION) * matModelView;

	services->setVertexShaderConstant("matModelView", matModelView.pointer(), 16);
	services->setVertexShaderConstant("matModelViewProjection", matModelViewProj.pointer(), 16);

	//irr::core::vector3df lightPos = irr::core::vector3df(0.0f, 0.0f, 0.0f);
	//irr::core::vector3df pos = m_device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
	//driver->getTransform(irr::video::ETS_VIEW).transformVect(pos);
	//matModelView.transformVect(pos);
	//services->setVertexShaderConstant("fvLightPosition", reinterpret_cast<irr::f32*>(&pos), 3);
	//services->setVertexShaderConstant("fvEyePosition", reinterpret_cast<irr::f32*>(&pos), 3);

//pixel shader constants
	irr::video::SColorf ambientMaterialColor = AMBIENT_MATERIAL_DEFAULT;
	irr::video::SColorf diffuseMaterialColor = DIFFUSE_MATERIAL_DEFAULT;
	irr::video::SColorf specularMaterialColor = SPECULAR_MATERIAL_DEFAULT;
	irr::f32 specularPower = SPECULAR_POWER;
/*
	if (m_material)
	{
		ambientMaterialColor = m_material->AmbientColor;
		diffuseMaterialColor = m_material->DiffuseColor;
		specularMaterialColor = m_material->SpecularColor;
		specularPower = m_material->Shininess;
	}
*/
	services->setPixelShaderConstant("fvAmbient", reinterpret_cast<irr::f32*>(&ambientMaterialColor), 4);
	services->setPixelShaderConstant("fvDiffuse", reinterpret_cast<irr::f32*>(&diffuseMaterialColor), 4);
	services->setPixelShaderConstant("fvSpecular", reinterpret_cast<irr::f32*>(&specularMaterialColor), 4);
	services->setPixelShaderConstant("fSpecularPower", &specularPower, 1);

	//set textures
	irr::s32 TextureLayerID = 0;
	services->setPixelShaderConstant("diffuseMap", &TextureLayerID, 1);
	TextureLayerID = 1;
	services->setPixelShaderConstant("normalMap", &TextureLayerID, 1);
}