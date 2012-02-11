#include "LoadingScene.h"
#include "GameLayer.h"

CLoadingScene::CLoadingScene(void)
{
	 CCScene::init();
}

CLoadingScene::~CLoadingScene(void)
{
}

void CLoadingScene::onEnter()
{
	CCScene::onEnter();

	//add the menu item for back to main menu

	CCLabelTTF* label = CCLabelTTF::labelWithString("Start Game", "Arial", 20);

	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(CLoadingScene::StartGameCallback));

	CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition(ccp(s.width / 2, s.height * 1 / 4));

	addChild(pMenu, 1);

	CCSprite* pSprite = CCSprite::spriteWithFile("logo.png");
	if (pSprite)
	{
		pSprite->setPosition(ccp(s.width / 2, s.height * 3 / 4));
		addChild(pSprite);
	}

	CCLabelTTF* labelTitle = CCLabelTTF::labelWithString("Feed Sharp!", "Arial", 28);
	if (labelTitle)
	{
		labelTitle->setPosition(ccp(s.width / 2, s.height / 2));
		addChild(labelTitle);
	}
}

void CLoadingScene::StartGameCallback( CCObject* pSender )
{
	CCScene *pScene = CGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}