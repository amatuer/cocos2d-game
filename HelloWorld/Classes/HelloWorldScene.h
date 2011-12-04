#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ccTypes.h"
#include "../GestureRecognize/GeometricRecognizer.h"
#include "MonsterCreater.h"
#include "GameInfo.h"

USING_NS_CC;

class HelloWorld : public CCLayer
{
public:
	HelloWorld();
	~HelloWorld();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnter();
	virtual void onExit();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);

private:
	void GameLoop(ccTime delta);
	void ProcessGestureV(void);

	DollarRecognizer::Path2D m_PathRec;
	DollarRecognizer::GeometricRecognizer m_Recognizer;
	CMonsterCreater m_MonsterCreater;
	CGameInfo* m_layerGameInfo;

	bool m_bOver;
public:
	void Bomb(CCNode* sender);
	void RemoveBombEffect(CCNode* sender);
	void MoveMainRoleUp(void);
	void MoveMainRoleDown(void);

	void GameOver(void);
	void GamePass(void);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void draw();
};

#endif // __HELLOWORLD_SCENE_H__
