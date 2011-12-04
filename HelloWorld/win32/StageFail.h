#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CStageFail : public CCLayer
{
public:
	CStageFail(void);
	~CStageFail(void);

	virtual bool init();
	LAYER_NODE_FUNC(CStageFail);

	virtual void menuCallback(CCObject* pSender);
};
