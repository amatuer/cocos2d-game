#pragma once

#include "cocos2d.h"

class BackgroundLayer;
class TerrainLayer;

class GamePlayLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();

	LAYER_NODE_FUNC(GamePlayLayer);

	void menuCallbackStage(CCObject* pSender);

	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
	void update(cocos2d::ccTime dt);

	void setOffsetX(int offsetX);
private:
	int m_acc;
	int m_heroOffsetX;

	BackgroundLayer* m_background;
	TerrainLayer* m_terrain;
};