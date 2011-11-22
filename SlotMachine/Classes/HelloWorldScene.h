#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#define LABEL_COUNT 5
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallbackPlay(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(HelloWorld);

	void update(cocos2d::ccTime dt);
private:
	cocos2d::CCSprite* m_labelBg[LABEL_COUNT];
	cocos2d::CCLabelTTF* m_label[LABEL_COUNT];
	cocos2d::CCSprite* m_focusLabel;
	bool m_startRand;
	float m_curSpeed;
	float m_curAcc;
	int m_startTime;
};

#endif  // __HELLOWORLD_SCENE_H__