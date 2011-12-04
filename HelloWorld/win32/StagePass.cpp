#include "StagePass.h"
#include "HelloWorldScene.h"

CStagePass::CStagePass(void)
{
}

CStagePass::~CStagePass(void)
{
}

bool CStagePass::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* Tip = CCLabelTTF::labelWithString("Stage Pass!", "Arial", 30);
	Tip->setPosition(ccp(s.width / 2, s.height / 2));
	this->addChild(Tip);

	CCLabelTTF* labelItem = CCLabelTTF::labelWithString("Next Stage", "Arial", 20);

	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(labelItem, this, menu_selector(CStagePass::menuCallback));

	CCMenu* pMenu =CCMenu::menuWithItems(pMenuItem, NULL);
	pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition(ccp(s.width / 2, s.height / 2 - 100));

	addChild(pMenu, 1);
	return true;
}

void CStagePass::menuCallback( CCObject* pSender )
{
	CCScene *pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}