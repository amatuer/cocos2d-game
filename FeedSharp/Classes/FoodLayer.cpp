#include "FoodLayer.h"
#include "Food.h"
#include "GameMgr.h"

CFoodLayer::CFoodLayer(void)
{
}

CFoodLayer::~CFoodLayer(void)
{
}

cocos2d::CCScene* CFoodLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	CFoodLayer *layer = CFoodLayer::node();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool CFoodLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	int nAmount = CFoodMgr::Instance()->GetFoodAmount();

	for (int i = 0; i < nAmount; i++)
	{
		char szNormal[64] = {0};
		char szSelected[64] = {0};
		sprintf(szNormal, "food%d.png", i);
		sprintf(szSelected, "food%d.png", i);

		CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
			szNormal,
			szSelected,
			this,
			menu_selector(CFoodLayer::menuCloseCallback) );
		pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
		CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
		pMenu->setPosition( ccp(0, 40 + 40 * i) );
		this->addChild(pMenu, 1, i);
	}

	this->scheduleUpdate();
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void CFoodLayer::menuCloseCallback( CCObject* pSender )
{
	CCNode* pNode = (CCNode*)pSender;

	int nTag = pNode->getTag();

	CGameMgr::Instance()->SetCurrentFoodType(nTag);
	this->setIsVisible(false);
}

bool CFoodLayer::ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent *event )
{
	return true;
}

void CFoodLayer::ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{

}

void CFoodLayer::update( cocos2d::ccTime dt )
{

}