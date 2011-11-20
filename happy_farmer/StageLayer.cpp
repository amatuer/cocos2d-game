#include "GameConfig.h"

#include "StageLayer.h"
#include "../GameCommon/Button.h"
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

	Button* btn1 = Button::itemWithId("stage1-btn", this, menu_selector(StageLayer::menuCallbackStage));
	btn1->setTag(1);

	CCMenu* menu = CCMenu::menuWithItems(btn1, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));
	menu->setContentSize(winSize);
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

}