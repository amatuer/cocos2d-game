#include "HelloWorldScene.h"
#include <stdio.h>

using namespace cocos2d;

enum {
	TAG_LABLE_WIND,
	TAG_LABLE_CUR_POINT,
	TAG_LABLE_MAX_POINT,
};

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
		this->addChild(m_pBall, 10);

		// 
		m_pSharp = CCSprite::spriteWithFile("tong1.png");
		CC_BREAK_IF(! m_pSharp);
		m_pSharp->setPosition(ccp(size.width / 2, 300));
		this->addChild(m_pSharp, 1);

		// 
		m_pWind = CCSprite::spriteWithFile("wind.png");
		CC_BREAK_IF(! m_pWind);
		this->addChild(m_pWind, 1);

		//
		CCLabelAtlas* labelWind = CCLabelAtlas::labelWithString("0m/min", "fonts/tuffy_bold_italic-charmap-small.png", 24, 32, ' ');
		addChild(labelWind, 1, TAG_LABLE_WIND);
		labelWind->setScale(0.5);

		//
		CCLabelAtlas* labelCur = CCLabelAtlas::labelWithString("CUR:0", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
		labelCur->setScale(0.5);
		addChild(labelCur, 1, TAG_LABLE_CUR_POINT);
		labelCur->setPosition(ccp(0, labelCur->getContentSize().height / 2));
		CCLabelAtlas* labelMax = CCLabelAtlas::labelWithString("MAX:0", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
		labelMax->setScale(0.5);
		addChild(labelMax, 1, TAG_LABLE_MAX_POINT);
		labelMax->setPosition(ccp(0, labelMax->getContentSize().height / 2 + labelCur->getContentSize().height));

		schedule(schedule_selector(HelloWorld::GameLoop));
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
		m_bReady = true;

		//
		m_nComboTime = 0;
		m_nCurPoint = 0;
		m_nMaxPoint = 0;
		m_aX = 0.4;
		m_aY = -1;

		srand(305062);
		SetWind();

		//
		m_nMaxPoint = CCUserDefault::sharedUserDefault()->getIntegerForKey("KEY_MAX_POINT", 0);


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
	char szCurrentPoint[32] = {0};
	char szMaxPoint[32] = {0};
	sprintf(szCurrentPoint, "CUR:%d", m_nCurPoint);
	sprintf(szMaxPoint, "MAX:%d", m_nMaxPoint);
	CCLabelAtlas* pLableCur = (CCLabelAtlas*)getChildByTag(TAG_LABLE_CUR_POINT);
	CCLabelAtlas* pLableMax = (CCLabelAtlas*)getChildByTag(TAG_LABLE_MAX_POINT);
	if (pLableCur && pLableMax)
	{
		pLableCur->setString(szCurrentPoint);
		pLableMax->setString(szMaxPoint);
	}

	if (!m_pBall || !m_pSharp || m_bReady)
	{
		return;
	}

	m_vX += m_aX;
	m_vY += m_aY;
	CCPoint pntBall = m_pBall->getPosition();
	
	pntBall.x += m_vX;
	pntBall.y += m_vY;

	m_pBall->setPosition(pntBall);

	// 丢出去了就重置
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint pntSharp = m_pSharp->getPosition();
	CCSize sizeSharp = m_pSharp->getContentSize();

	if (m_vY < 0)
	{
		// oh ye!
		if (CCRect::CCRectContainsPoint(CCRectMake(pntSharp.x - sizeSharp.width / 2, pntSharp.y + sizeSharp.height / 2, sizeSharp.width, 20), pntBall))
		{
			SetWind();
			m_bReady = true;
			m_pBall->setPosition(ccp(size.width / 2, 50));
			m_nComboTime++;
			m_nCurPoint += m_nComboTime;
			if (m_nCurPoint > m_nMaxPoint)
			{
				CCUserDefault::sharedUserDefault()->setIntegerForKey("KEY_MAX_POINT", m_nCurPoint);
				m_nMaxPoint = m_nCurPoint;
			}

			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>;

			char str[64] = {0};
			for (int i = 1; i < 4; i++)
			{
				sprintf(str, "tong%d.png", i);
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(str);
				CCSpriteFrame* frame = CCSpriteFrame::frameWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));
				animFrames->addObject(frame);
			}

			CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("tong1.png");
			CCSpriteFrame* frame = CCSpriteFrame::frameWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));
			animFrames->addObject(frame);
			CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);

			m_pSharp->runAction(animate);

			return;
		}

		// 球该落水了~
		if (pntBall.y < pntSharp.y - sizeSharp.height / 2)
		{
			SetWind();
			m_bReady = true;
			m_pBall->setPosition(ccp(size.width / 2, 50));
			m_nComboTime = 0;
			m_nCurPoint = 0;
			return;
		}
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
	//CCRect rectBounding = CCRectMake(pntBall.x - 50, pntBall.y - 100, 100, 200);
	CCRect rect = m_pBall->boundingBox();
	if (!CCRect::CCRectContainsPoint(rect, pntTouch))
	{
		return false;
	}

	m_pntBegin = ccp(pntBall.x, CCDirector::sharedDirector()->getWinSize().height - pntBall.y);
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

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (m_pntEnd.y >= size.height * 3 / 4)
	{
		m_bReady = true;
		return;
	}

	// 速度分解
	const float V = 29;
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
	// 为了游戏效果，恶心的修正，上升速度固定
	m_vY = 29;
	m_vX /= 2;
}

void HelloWorld::SetWind( void )
{
	CCLabelAtlas* pLable = (CCLabelAtlas*)this->getChildByTag(TAG_LABLE_WIND);
	CC_ASSERT(pLable);

	m_aX = (float)(rand() % 5000) / 10000;
	int nrand = rand() % 100;
	if (nrand >= 50)
	{
		m_aX = -m_aX;
	}

	char string[12] = {0};
	sprintf(string, "%.3f m/s", abs(m_aX) * 10);
	pLable->setString(string);
	CCSize sizeLable = pLable->getContentSize();

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSize sizeWind = m_pWind->getContentSize();
	m_pWind->setPosition(ccp(sizeWind.width / 2, size.height - sizeWind.height / 2));

	if (m_aX < 0)
	{
		m_pWind->setFlipX(true);
		m_pWind->setPosition(ccp(size.width - sizeWind.width / 2, size.height - sizeWind.height / 2));
		pLable->setPosition(ccp(size.width - sizeLable.width / 2, 350));
	}
	else
	{
		m_pWind->setFlipX(false);
		m_pWind->setPosition(ccp(sizeWind.width / 2, size.height - sizeWind.height / 2));
		pLable->setPosition(ccp(0, 350));
	}
}