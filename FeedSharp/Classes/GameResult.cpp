#include "GameResult.h"

#include "LoadingScene.h"

CGameResult::CGameResult(void)
{
}

CGameResult::~CGameResult(void)
{
}

bool CGameResult::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* Tip = CCLabelTTF::labelWithString("Game Result", "Arial", 24);
	Tip->setPosition(ccp(s.width / 2, s.height / 4));
	this->addChild(Tip);

	CCLabelTTF* lablePoint = CCLabelTTF::labelWithString("Your Point:0", "Arial", 24);
	lablePoint->setPosition(ccp(s.width / 2, s.height / 3));
	this->addChild(lablePoint);
	int nMaxPoint = CCUserDefault::sharedUserDefault()->getIntegerForKey("KEY_MAX_POINT", 0);

	CCLabelTTF* labelItem = CCLabelTTF::labelWithString("Main Menu", "Arial", 20);

	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(labelItem, this, menu_selector(CGameResult::menuCallback));

	CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition(ccp(s.width / 2, s.height / 2 - 100));

	addChild(pMenu, 1);
	return true;
}

void CGameResult::menuCallback( CCObject* pSender )
{
	CCScene* pScene = new CLoadingScene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}