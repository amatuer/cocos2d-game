#include "StageFail.h"

#include "LoadingScene.h"

CStageFail::CStageFail(void)
{
}

CStageFail::~CStageFail(void)
{
}

bool CStageFail::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* Tip = CCLabelTTF::labelWithString("Stage Failed!", "Arial", 30);
	Tip->setPosition(ccp(s.width / 2, s.height / 2));
	this->addChild(Tip);

	CCLabelTTF* labelItem = CCLabelTTF::labelWithString("Main Menu", "Arial", 20);

	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(labelItem, this, menu_selector(CStageFail::menuCallback));

	CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition(ccp(s.width / 2, s.height / 2 - 100));

	addChild(pMenu, 1);
	return true;
}

void CStageFail::menuCallback( CCObject* pSender )
{
	CCScene* pScene = new CLoadingScene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}