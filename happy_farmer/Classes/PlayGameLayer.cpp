#include "GameConfig.h"

#include "PlayGameLayer.h"
#include "../GameCommon/Button.h"
#include "../GameCommon/GuiMgr.h"

using namespace cocos2d;

CCScene* PlayGameLayer::scene()
{
	CCScene * scene = CCScene::node();
	CCLayer* layer = PlayGameLayer::node();
	if (layer && scene) {
		scene->addChild(layer);
		return scene;
	}

	return NULL;
}

bool PlayGameLayer::init()
{
	CCLayer::init();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::spriteWithFile("data/bg.png");
	if (bg) {
		this->addChild(bg);
		bg->setTag(0);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setPosition(ccp(0, 0));
	}

	CCSprite* bgSky = CCSprite::spriteWithFile("data/bg-sky.png");
	if (bgSky) {
		this->addChild(bgSky);
		bgSky->setTag(1);
		bgSky->setAnchorPoint(ccp(0, 0));
		bgSky->setPosition(ccp(GuiMgr::instance().getData("bgLayer1-sprite", "x"), GuiMgr::instance().getData("bgLayer1-sprite", "y")));
	}

	CCSprite* bgHouse = CCSprite::spriteWithFile("data/bg-house.png");
	if (bgHouse) {
		this->addChild(bgHouse);
		bgHouse->setTag(2);
		bgHouse->setAnchorPoint(ccp(0, 0));
		bgHouse->setPosition(ccp(GuiMgr::instance().getData("bgLayer2-sprite", "x"), GuiMgr::instance().getData("bgLayer2-sprite", "y")));
	}

	CCSprite* bgFengche = CCSprite::spriteWithFile("data/bg-fengche.png");
	if (bgFengche) {
		this->addChild(bgFengche);
		bgFengche->setTag(3);
		bgFengche->setAnchorPoint(ccp(0, 0));
		bgFengche->setPosition(ccp(GuiMgr::instance().getData("bgLayer3-sprite", "x"), GuiMgr::instance().getData("bgLayer3-sprite", "y")));
	}

	CCSprite* bgHuang = CCSprite::spriteWithFile("data/bg-huang.png");
	if (bgHuang) {
		this->addChild(bgHuang);
		bgHuang->setTag(4);
		bgHuang->setAnchorPoint(ccp(0, 0));
		bgHuang->setPosition(ccp(GuiMgr::instance().getData("bgLayer4-sprite", "x"), GuiMgr::instance().getData("bgLayer4-sprite", "y")));
	}

	m_heroOffsetX = 0;
	m_acc = 0;

	this->setIsTouchEnabled(true);
	this->scheduleUpdate();

	return true;
}

void PlayGameLayer::menuCallbackStage(CCObject* pSender)
{
}

void PlayGameLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, TRUE);
}

bool PlayGameLayer::ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event)
{
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (location.x > winSize.width * 2 / 3) {
		m_acc = 1;
	} else if (location.x < winSize.width / 3) {
		m_acc = -1;
	}

	return true;
}

void PlayGameLayer::ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event)
{
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

	m_acc = 0;
}

void PlayGameLayer::update(ccTime dt)
{
	if (m_acc == -1) {
		setOffsetX(m_heroOffsetX - 5);
	} else if (m_acc == 1) {
		setOffsetX(m_heroOffsetX + 5);
	}
}

void PlayGameLayer::setOffsetX(int offsetX)
{
	if (m_heroOffsetX == offsetX) {
		return;
	}

	m_heroOffsetX = offsetX;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* sprite = (CCSprite*)this->getChildByTag(1);

	if (sprite) {
		sprite->setTextureRect(CCRectMake(offsetX * 0.7f, sprite->getPosition().y, winSize.width, winSize.height));
	}
	
	sprite = (CCSprite*)this->getChildByTag(2);
	if (sprite) {
		sprite->setTextureRect(CCRectMake(offsetX * 0.8f, sprite->getPosition().y, winSize.width, winSize.height));
	}

	sprite = (CCSprite*)this->getChildByTag(3);
	if (sprite) {
		sprite->setTextureRect(CCRectMake(offsetX * 0.5f, sprite->getPosition().y, winSize.width, winSize.height));
	}

	sprite = (CCSprite*)this->getChildByTag(4);
	if (sprite) {
		sprite->setTextureRect(CCRectMake(offsetX * 0.9f, sprite->getPosition().y, winSize.width, winSize.height));
	}

}