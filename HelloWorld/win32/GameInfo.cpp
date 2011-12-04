#include "GameInfo.h"

#include "gamedefine.h"
#include "LoadingScene.h"
#include "Role.h"

CGameInfo::CGameInfo(void)
{
}

CGameInfo::~CGameInfo(void)
{
}

cocos2d::CCScene* CGameInfo::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	CGameInfo *layer = CGameInfo::node();

	// add layer as a child to scene
	scene->addChild(layer, 0, E_NODE_ID_GAME_INFO);

	// return the scene
	return scene;
}

bool CGameInfo::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CGameInfo::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	CCMenuItemImage *pGotoItem = CCMenuItemImage::itemFromNormalImage(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(CGameInfo::menuGotoCallback) );
	pGotoItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 80) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, pGotoItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	m_lablePower = CCLabelTTF::labelWithString("Power:0/0",CCSizeMake(150, 20), CCTextAlignmentLeft, "Arial", 20);;
	if (m_lablePower)
	{
		m_lablePower->setPosition( ccp(80, 300) );
		this->addChild(m_lablePower);
	}
	//this->setIsTouchEnabled(true);
	this->scheduleUpdate();
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void CGameInfo::menuCloseCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CGameInfo::menuGotoCallback( CCObject* pSender )
{
	CCScene* pScene = new CLoadingScene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

bool CGameInfo::ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent *event )
{
	return true;
}

void CGameInfo::ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{

}

void CGameInfo::update( cocos2d::ccTime dt )
{
	CCNode* pParent = this->getParent();

	if (!pParent)
	{
		return;
	}

	CRole* pMainRole = (CRole*)(pParent->getChildByTag(E_NODE_ID_HERO));

	if (!pMainRole)
	{
		return;
	}

	int nPower = pMainRole->GetPower();
	int nMaxPower = pMainRole->GetMaxPower();

	char szPower[16] = {0};

	sprintf_s(szPower, 15, "Power:%d/%d", nPower, nMaxPower);
	szPower[15] = 0;

	m_lablePower->setString(szPower);
}