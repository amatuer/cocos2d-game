#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CStagePass : public CCLayer
{
public:
	CStagePass(void);
	~CStagePass(void);
	virtual bool init();
	LAYER_NODE_FUNC(CStagePass);

	virtual void menuCallback(CCObject* pSender);
};
