#pragma once

#include "cocos2d.h"

class TerrainLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  

	LAYER_NODE_FUNC(TerrainLayer);

	void menuCallbackStage(CCObject* pSender);

	void setOffsetX(int offsetX);
private:
	int m_acc;
	int m_heroOffsetX;
};