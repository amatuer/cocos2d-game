#include "UILayer.h"
#include "FoodLayer.h"

CUILayer::CUILayer(void)
{
}

CUILayer::~CUILayer(void)
{
}

cocos2d::CCScene* CUILayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	CUILayer *layer = CUILayer::node();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool CUILayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pContainer = CCMenuItemImage::itemFromNormalImage(
		"tong_normal.png",
		"tong_select.png",
		this,
		menu_selector(CUILayer::menuCloseCallback) );
	pContainer->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
	CCMenu* pMenu = CCMenu::menuWithItems(pContainer, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	CFoodLayer* pFoodLayer = CFoodLayer::node();

	if (pFoodLayer)
	{
		this->addChild(pFoodLayer, 15, 1);
		pFoodLayer->setIsVisible(false);
	}

	this->scheduleUpdate();
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}

void CUILayer::menuCloseCallback( CCObject* pSender )
{
//	CCDirector::sharedDirector()->end();

	CCNode* node = getChildByTag(1);
	if (node)
	{
		node->setIsVisible(!node->getIsVisible());
	}

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
// 	exit(0);
// #endif
}

bool CUILayer::ccTouchBegan( cocos2d::CCTouch * touch, cocos2d::CCEvent *event )
{
	return true;
}

void CUILayer::ccTouchEnded( cocos2d::CCTouch * touch, cocos2d::CCEvent * event )
{

}

void CUILayer::update( cocos2d::ccTime dt )
{

}