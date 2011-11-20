#pragma once

#include "cocos2d.h"

class StageLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();

	LAYER_NODE_FUNC(StageLayer);

	void menuCallbackStage(CCObject* pSender);
private:
	void gotoStage(int index);
};