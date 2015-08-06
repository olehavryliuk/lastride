//Author Oleh Havryliuk 08.2015
#ifndef __BUMP_PARALLAX_SHADER_CALL_BACK_H_INCLUDED__
#define __BUMP_PARALLAX_SHADER_CALL_BACK_H_INCLUDED__

#include <IShaderConstantSetCallBack.h>

class BumpParallaxShaderCallBack : public irr::video::IShaderConstantSetCallBack
{
protected:
	const irr::video::SMaterial* m_material;		//weak ref
	irr::IrrlichtDevice*		 m_device;			//weak ref

public:
	BumpParallaxShaderCallBack(irr::IrrlichtDevice* device);

	virtual void OnSetMaterial(const irr::video::SMaterial& material);
	virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData);
};

#endif