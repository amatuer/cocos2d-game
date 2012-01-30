#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		CCSprite *sprite = CCSprite::spriteWithFile("bg.png");
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(CCPointMake(0,0));
		addChild(sprite,-1);

        CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
        CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);

		// add by wang fei
		m_bReady = false;

		m_pBall = CCSprite::spriteWithFile("ball1.png");
		CC_BREAK_IF(! m_pBall);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		m_pBall->setPosition(ccp(size.width / 2, 50));
		this->addChild(m_pBall, 0);

		// 
		m_pSharp = CCSprite::spriteWithFile("Sharp.png");
		CC_BREAK_IF(! m_pSharp);

		m_pSharp->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(m_pSharp, 1);

		schedule(schedule_selector(HelloWorld::GameLoop));
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
		m_bReady = true;

		//
		m_aX = 0.2;
		m_aY = -0.5;

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::GameLoop( ccTime delta )
{
	if (!m_pBall || !m_pSharp || m_bReady)
	{
		return;
	}

// 	float vx = m_vX + m_aX;
// 	float vy = m_vY + m_aY;
	m_vX += m_aX;
	m_vY += m_aY;
	CCPoint pntBall = m_pBall->getPosition();
	
	pntBall.x += m_vX;
	pntBall.y += m_vY;

	m_pBall->setPosition(pntBall);

	// 丢出去了就重置
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (!CCRect::CCRectContainsPoint(CCRectMake(0, 0, size.width, size.height), pntBall))
	{
		m_bReady = true;
		m_pBall->setPosition(ccp(size.width / 2, 50));
		return;
	}
	// 球该落水了~
	CCPoint pntSharp = m_pSharp->getPosition();

	if (m_vY < 0  && pntBall.y < pntSharp.y)
	{
		m_bReady = true;
		m_pBall->setPosition(ccp(size.width / 2, 50));
		return;
	}
}

bool HelloWorld::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	if (!m_bReady)
	{
		return false;
	}

	if (!m_pBall)
	{
		return false;
	}

	CCPoint pntBall = m_pBall->getPosition();
	CCPoint pntTouch = touch->locationInView(touch->view());
	pntTouch.y = CCDirector::sharedDirector()->getWinSize().height - pntTouch.y;
	CCRect rectBounding = CCRectMake(pntBall.x - 50, pntBall.y - 50, 100, 100);
	CCRect rect = m_pBall->boundingBox();
	if (!CCRect::CCRectContainsPoint(rectBounding, pntTouch))
	{
		return false;
	}

	m_pntBegin = touch->locationInView(touch->view());
	return true;
}

void HelloWorld::ccTouchMoved( CCTouch* touch, CCEvent* event )
{

}

void HelloWorld::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	m_pntEnd = touch->locationInView(touch->view());
	m_bReady = false;

	if (!m_pBall)
	{
		m_bReady = true;
		return;
	}

	CCPoint pntBall = m_pBall->getPosition();
	CCPoint pntTouch = touch->locationInView(touch->view());
	pntTouch.y = CCDirector::sharedDirector()->getWinSize().height - pntTouch.y;
	CCRect rectBounding = CCRectMake(pntBall.x - 50, pntBall.y - 50, 100, 100);
	if (CCRect::CCRectContainsPoint(rectBounding, pntTouch))
	{
		m_bReady = true;
		return;
	}

	if (m_pntEnd.y >= m_pntBegin.y)
	{
		m_bReady = true;
		return;
	}

	// 速度分解
	const float V = 13;
	float fX = m_pntEnd.x - m_pntBegin.x;
	float fY = m_pntEnd.y - m_pntBegin.y;
	if (fX >= 0)
	{
		double fAlpha = atan(fY / -fX);
		m_vX = V * cos(fAlpha);
		m_vY = V * sin(fAlpha);
	} else {
		double fAlpha = atan(fY / fX);
		m_vX = -V * cos(fAlpha);
		m_vY = V * sin(fAlpha);
	}
	// 上升速度固定
	m_vY = 15;
}
