#include "HelloWorldScene.h"
#include "SlotMachineLayer.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    CCLayer::init();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::spriteWithFile("data/bg.png");
	CCSize bgSize = bg->getContentSize();
	bg->setAnchorPoint(ccp(0, 0));
	bg->setScaleX(winSize.width / bgSize.width);
	bg->setScaleY(winSize.height / bgSize.height);
	bg->setPosition(ccp(0, 0));
	this->addChild(bg, -1);

	CCSprite* top = CCSprite::spriteWithFile("sm/top.png");
	CCSize imageSize = top->getContentSize();
	top->setAnchorPoint(ccp(0, 0));
	top->setScaleX(winSize.width / imageSize.width);
	top->setScaleY(kTopScale);
	top->setPosition(ccp(0, 0));
	this->addChild(top, 4);
	CCSprite* bottom = CCSprite::spriteWithFile("sm/top.png");
	bottom->setFlipY(true);
	bottom->setAnchorPoint(ccp(0, 0));
	bottom->setScaleX(winSize.width / imageSize.width);
	bottom->setScaleY(kTopScale);
	bottom->setPosition(ccp(0, winSize.height - imageSize.height * kTopScale));
	this->addChild(bottom, 4);


	CCSprite* topg = CCSprite::spriteWithFile("sm/glass.png");
	CCSize imageGlassSize = topg->getContentSize();
	topg->setAnchorPoint(ccp(0, 0));
	topg->setScaleX((winSize.width - 30) / imageGlassSize.width);
	topg->setScaleY(kGlassScale);
	topg->setPosition(ccp(15, imageSize.height * kTopScale - 10));
	this->addChild(topg, 3);

	CCSprite* bottomg = CCSprite::spriteWithFile("sm/glass.png");
	bottomg->setFlipY(true);
	bottomg->setAnchorPoint(ccp(0, 0));
	bottomg->setScaleX((winSize.width - 30) / imageGlassSize.width);
	bottomg->setScaleY(kGlassScale);
	bottomg->setPosition(ccp(15, winSize.height - imageSize.height * kTopScale - imageGlassSize.height * kGlassScale + 10));
	this->addChild(bottomg, 3);


	CCMenuItemImage* start = CCMenuItemImage::itemFromNormalImage("sm/startn.png", "sm/startc.png", "sm/startd.png", this, menu_selector(HelloWorld::menuCallbackPlay));
	start->setScaleX(0.6f);
	start->setScaleY(0.6f);
	CCSize startSize = start->getContentSize();
	CCMenu* menu  = CCMenu::menuWithItem(start);
	menu->setPosition(ccp(winSize.width  / 2, startSize.height / 2 - 10));
	this->addChild(menu, 10);

	m_slotMachineLayer = SlotMachineLayer::node();
	if (m_slotMachineLayer) {
		m_slotMachineLayer->init(0, 0, imageGlassSize.width * kGlassScale - 30, 0);
		this->addChild(m_slotMachineLayer, -1);
	}
	return true;
}

void HelloWorld::menuCallbackPlay(CCObject* pSender)
{
	if (m_slotMachineLayer) {
		if (m_slotMachineLayer->isStart()) {
			m_slotMachineLayer->stop();
		} else {
			m_slotMachineLayer->start();
		}
	}
}

