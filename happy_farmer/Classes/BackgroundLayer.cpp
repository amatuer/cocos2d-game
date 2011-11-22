#include "GameConfig.h"

#include "BackgroundLayer.h"
#include "../GameCommon/Button.h"
#include "../GameCommon/GuiMgr.h"
#include <boost/lexical_cast.hpp>

using namespace cocos2d;

bool BackgroundLayer::init()
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

	CCParallaxNode* voidNode = CCParallaxNode::node();
	voidNode->setTag(1);
	voidNode->setAnchorPoint(ccp(0, 0));
	voidNode->setPosition(ccp(0, 0));
	this->addChild(voidNode);

	CCSprite* bgSky = CCSprite::spriteWithFile("data/bg-sky.png");
	if (bgSky) {
		voidNode->addChild(bgSky, 1, ccp(boost::lexical_cast<float>(GuiMgr::instance().getStr("bgLayer1-sprite", "speed", "1.0")), 1.0),
							ccp(GuiMgr::instance().getData("bgLayer1-sprite", "x"),
							GuiMgr::instance().getData("bgLayer1-sprite", "y")));
		bgSky->setTag(1);
		bgSky->setAnchorPoint(ccp(0, 0));
	}

	CCSprite* bgHouse = CCSprite::spriteWithFile("data/bg-house.png");
	if (bgHouse) {
		voidNode->addChild(bgHouse, 2, ccp(boost::lexical_cast<float>(GuiMgr::instance().getStr("bgLayer2-sprite", "speed", "1.0")), 1.0),
							ccp(GuiMgr::instance().getData("bgLayer2-sprite", "x"),
							GuiMgr::instance().getData("bgLayer2-sprite", "y")));
		bgHouse->setTag(2);
		bgHouse->setAnchorPoint(ccp(0, 0));
	}

	CCSprite* bgFengche = CCSprite::spriteWithFile("data/bg-fengche.png");
	if (bgFengche) {
		voidNode->addChild(bgFengche, 3, ccp(boost::lexical_cast<float>(GuiMgr::instance().getStr("bgLayer3-sprite", "speed", "1.0")), 1.0),
							ccp(GuiMgr::instance().getData("bgLayer3-sprite", "x"),
							GuiMgr::instance().getData("bgLayer3-sprite", "y")));
		bgFengche->setTag(3);
		bgFengche->setAnchorPoint(ccp(0, 0));
	}

	CCSprite* bgHuang = CCSprite::spriteWithFile("data/bg-huang.png");
	if (bgHuang) {
		voidNode->addChild(bgHuang, 4, ccp(boost::lexical_cast<float>(GuiMgr::instance().getStr("bgLayer4-sprite", "speed", "1.0")), 1.0),
							ccp(GuiMgr::instance().getData("bgLayer4-sprite", "x"),
							GuiMgr::instance().getData("bgLayer4-sprite", "y")));
		bgHuang->setTag(4);
		bgHuang->setAnchorPoint(ccp(0, 0));
	}

	m_heroOffsetX = 0;
	m_acc = 0;

	return true;
}

void BackgroundLayer::menuCallbackStage(CCObject* pSender)
{
}

void BackgroundLayer::setOffsetX(int offsetX)
{
	if (m_heroOffsetX == offsetX) {
		return;
	}

	m_heroOffsetX = offsetX;
	
	CCNode* voidNode = this->getChildByTag(1);
	CCPoint pt = voidNode->getPosition();
	pt.x = (float)m_heroOffsetX;
	voidNode->setPosition(pt);
}