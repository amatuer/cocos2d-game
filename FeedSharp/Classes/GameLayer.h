#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

class CGameLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
	LAYER_NODE_FUNC(CGameLayer);
private:
	bool m_bReady;
	CCPoint m_pntBegin;
	CCPoint m_pntEnd;
	CCSprite* m_pFood;
	CCSprite* m_pSharp;
	CCSprite* m_pWind;
	float m_vX;
	float m_vY;
	float m_aX;
	FLOAT m_aY;
	int m_nFoodType;

	int m_nCurPoint;
	int m_nMaxPoint;
	int m_nComboTime;
	int m_nLeftFood;

	void GameLoop(ccTime delta);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void SetWind(void);
	void SetFood(void);
	void CheckFoodType(void);
};

#endif  // __GAMELAYER_H__