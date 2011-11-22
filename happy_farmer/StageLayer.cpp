#include "GameConfig.h"

#include "StageLayer.h"
#include "../GameCommon/Button.h"
#include "GamePlayLayer.h"

#include <boost/format.hpp>

using namespace cocos2d;

CCScene* StageLayer::scene()
{
	CCScene * scene = CCScene::node();
	CCLayer* layer = StageLayer::node();
	if (layer && scene) {
		scene->addChild(layer);
		return scene;
	}

	return NULL;
}

bool StageLayer::init()
{
	CCLayer::init();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::spriteWithFile("data/stage-bg.png");
	if (bg) {
		this->addChild(bg);
		bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	}

	CCSprite* road = CCSprite::spriteWithFile("data/road.png");
	if (road) {
		this->addChild(road);
		road->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	}

	Button* btn0 = Button::itemWithId("stage0-btn", this, menu_selector(StageLayer::menuCallbackStage));
	btn0->setTag(0);

	CCMenu* menu = CCMenu::menuWithItems(btn0, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));
	menu->setContentSize(winSize);

	for (int i = 1; i <= 12; ++i) {
		std::string btnId = str(boost::format("stage%d-btn") % i);
		Button* btn = Button::itemWithId(btnId.c_str(), this, menu_selector(StageLayer::menuCallbackStage));
		btn->setTag(i);
		menu->addChild(btn, i);
	}
	this->addChild(menu);

	return true;
}

void StageLayer::menuCallbackStage(CCObject* pSender)
{
	CCNode* btn = (CCNode*)pSender;
	int tag = btn->getTag();
	gotoStage(tag);
}

void StageLayer::gotoStage(int index)
{
	CCScene* stage = GamePlayLayer::scene();
	if (stage) {
		CCTransitionSlideInR *transitionScene = CCTransitionSlideInR::transitionWithDuration(1, stage);
		CCDirector::sharedDirector()->replaceScene(transitionScene);
	}
}