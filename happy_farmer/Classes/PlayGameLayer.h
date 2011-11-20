#pragma once

#include "cocos2d.h"

class PlayGameLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();

	LAYER_NODE_FUNC(PlayGameLayer);

	void menuCallbackStage(CCObject* pSender);

	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
	void update(cocos2d::ccTime dt);

	void setOffsetX(int offsetX);
private:
	int m_acc;
	int m_heroOffsetX;
};