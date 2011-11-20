#include "GameConfig.h"
#include "TitleLayer.h"
#include "StageLayer.h"
#include "../GameCommon/Button.h"

using namespace cocos2d;

CCScene* TitleLayer::scene()
{
	CCScene * scene = CCScene::node();
	CCLayer* layer = TitleLayer::node();
	if (layer && scene) {
		scene->addChild(layer);
		return scene;
	}

	return NULL;
}

bool TitleLayer::init()
{
	CCLayer::init();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::spriteWithFile("data/title-bg.png");
	if (bg) {
		this->addChild(bg);		
		bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	}

	Button* play = Button::itemWithId("play-btn", this, menu_selector(TitleLayer::menuCallbackPlay));
	Button* setting = Button::itemWithId("setting-btn", this, menu_selector(TitleLayer::menuCallbackSetting));

	CCMenu* menu = CCMenu::menuWithItems( play, setting, NULL);
	menu->alignItemsVerticallyWithPadding(20.0f);
	this->addChild(menu);

	// elastic effect
	int i=0;
	CCNode* child;
	CCArray * pArray = menu->getChildren();
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if(pObject == NULL) {
			continue;
		}

		child = (CCNode*)pObject;

		CCPoint dstPoint = child->getPosition();
		int offset = (int) (winSize.width/2 + 50);
		if( i % 2 == 0) {
			offset = -offset;
		}

		child->setPosition( CCPointMake( dstPoint.x + offset, dstPoint.y) );
		child->runAction(CCEaseElasticOut::actionWithAction(CCMoveBy::actionWithDuration(2, CCPointMake(dstPoint.x - offset,0)), 0.35f));
		i++;
	}
	
	return true;
}

void TitleLayer::menuCallbackPlay(CCObject* pSender)
{
	CCScene* stage = StageLayer::scene();
	if (stage) {
		CCTransitionSlideInR *transitionScene = CCTransitionSlideInR::transitionWithDuration(1, stage);
		CCDirector::sharedDirector()->replaceScene(transitionScene);
	}
}

void TitleLayer::menuCallbackSetting(CCObject* pSender)
{

}