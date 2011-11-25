#pragma once

#include "cocos2d.h"

class TerrainLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  

	LAYER_NODE_FUNC(TerrainLayer);

	void menuCallbackStage(CCObject* pSender);

	void setOffsetX(int offsetX);
	void draw();
private:
	int m_acc;
	int m_offsetX;
	int m_fromKeyPointIndex;
	int m_toKeyPointIndex;
	std::vector<cocos2d::CCPoint> m_hillKeyPoints;

	void genHillKeyPoints(int maxNumber);
	void resetHillVertices();
};