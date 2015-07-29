#include "CSceneNodeAnimatorTextureSheet.h"
#include "ISceneNode.h"

CSceneNodeAnimatorTextureSheet::CSceneNodeAnimatorTextureSheet(irr::u32 w, irr::u32 h, irr::u32 timePerFrame, irr::u32 startTime, bool loop)
        :W(w), H(h), TimePerFrame(timePerFrame), StartTime(startTime), Loop(loop)
{
	#ifdef _DEBUG
    setDebugName("CSceneNodeAnimatorTextureSheet");
    #endif

    FinishTime = timePerFrame * w * h;
}

CSceneNodeAnimatorTextureSheet::~CSceneNodeAnimatorTextureSheet()
{

}

void CSceneNodeAnimatorTextureSheet::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
	if(node)
    {
		irr::u32 idx = 0;
		timeMs -= StartTime;
        if (!Loop && timeMs > FinishTime)
            idx = W * H - 1;
        else
            idx = (timeMs / TimePerFrame) % (W * H);
        float x = float(idx % W) / float(W);
        float y = float(idx / W) / float(H);
        node->getMaterial(0).getTextureMatrix(0).setTextureTranslate(x, y);
    }
}

void CSceneNodeAnimatorTextureSheet::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
{
    out->addInt("TimePerFrame", TimePerFrame);
	out->addInt("StartTime", StartTime);
    out->addBool("Loop", Loop);
    out->addInt("W", W);
    out->addInt("H", H);
}

void CSceneNodeAnimatorTextureSheet::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
{
    TimePerFrame = in->getAttributeAsInt("TimePerFrame");
	StartTime = in->getAttributeAsInt("StartTime");
    Loop = in->getAttributeAsBool("Loop");
    W = in->getAttributeAsInt("W");
    H = in->getAttributeAsInt("H");
    FinishTime = TimePerFrame * W * H;
}

irr::scene::ISceneNodeAnimator* CSceneNodeAnimatorTextureSheet::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
{
	CSceneNodeAnimatorTextureSheet * newAnimator = new CSceneNodeAnimatorTextureSheet(W, H, TimePerFrame, StartTime, Loop);
    return newAnimator;
}

void CSceneNodeAnimatorTextureSheet::reset(irr::u32 startTime)
{
	StartTime = startTime;
}