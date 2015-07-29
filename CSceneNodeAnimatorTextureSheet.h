#ifndef __C_SCENE_NODE_ANIMATOR_TEXTURE_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_TEXTURE_H_INCLUDED__

#include "ISceneNodeAnimator.h"

class CSceneNodeAnimatorTextureSheet : public irr::scene::ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorTextureSheet(irr::u32 w, irr::u32 h, irr::u32 timePerFrame, irr::u32 startTime, bool loop);
	virtual ~CSceneNodeAnimatorTextureSheet();
	virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
	virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options = 0) const;
	virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0);
	virtual irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const { return irr::scene::ESNAT_TEXTURE; }
	virtual ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager=0);
	virtual void reset(irr::u32 startTime);

private:
	irr::u32 W;
	irr::u32 H;
	irr::u32 TimePerFrame;
	irr::u32 StartTime;
	irr::u32 FinishTime;
	bool Loop;
};

#endif