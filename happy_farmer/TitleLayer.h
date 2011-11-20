#pragma once

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();

	LAYER_NODE_FUNC(TitleLayer);

	void menuCallbackPlay(CCObject* pSender);
	void menuCallbackSetting(CCObject* pSender);
};
