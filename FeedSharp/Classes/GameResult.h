#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CGameResult : public CCLayer
{
public:
	CGameResult(void);
	~CGameResult(void);

	virtual bool init();
	LAYER_NODE_FUNC(CGameResult);

	virtual void menuCallback(CCObject* pSender);
};
