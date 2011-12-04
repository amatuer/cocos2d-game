#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CGameInfo : public CCLayer
{
public:
	CGameInfo(void);
	~CGameInfo(void);
private:
	CCLabelTTF* m_lablePower;

	virtual bool init();  

public:
	static cocos2d::CCScene* scene();
	LAYER_NODE_FUNC(CGameInfo);

	bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
	void update(cocos2d::ccTime dt);

	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	virtual void menuGotoCallback(CCObject* pSender);
};
