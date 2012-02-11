#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CFoodLayer : public CCLayer
{
public:
	CFoodLayer(void);
	~CFoodLayer(void);
private:

	virtual bool init();  

public:
	static cocos2d::CCScene* scene();
	LAYER_NODE_FUNC(CFoodLayer);

	bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
	void update(cocos2d::ccTime dt);

	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
};
