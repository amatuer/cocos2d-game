#pragma once

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  

	LAYER_NODE_FUNC(BackgroundLayer);

	void menuCallbackStage(CCObject* pSender);
	void setOffsetX(int offsetX);
private:
	int m_acc;
	int m_heroOffsetX;
};