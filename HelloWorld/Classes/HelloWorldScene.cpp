#include "HelloWorldScene.h"

#include "GameDefine.h"
#include "../GestureRecognize/GeometricRecognizer.h"
#include "Role.h"
#include "Flyers.h"
#include "LoadingScene.h"
#include "StageFail.h"
#include "StagePass.h"
#include "SceneMgr.h"

const int MAX_RECOGNIZE_POINT = 128;

USING_NS_CC;

HelloWorld::HelloWorld()
{
	m_bOver = false;
}

HelloWorld::~HelloWorld()
{

}

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer, 0, E_NODE_ID_APP);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_layerGameInfo = CGameInfo::node();

	if (m_layerGameInfo)
	{
		this->addChild(m_layerGameInfo, 10, E_NODE_ID_GAME_INFO);
	}

	CCSprite *sprite = CCSprite::spriteWithFile("bg.png");
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(CCPointMake(0,0));
	addChild(sprite,-1);

	// add player
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame* frameMain = cache->spriteFrameByName("poisonhand/7.png");
	CRole* pMainRole = CRole::CreateRoleFromeSpriteFrame(frameMain);

	if (!pMainRole)
	{
		return false;
	}

	// set attribute
	pMainRole->SetAttack(20);
	pMainRole->setVelocity(0);
	pMainRole->SetMaxPower(100);

	CCSize sizeSprite = pMainRole->getContentSize();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pMainRole->setPosition(ccp(sizeSprite.width / 2, size.height / 2));

	this->addChild(pMainRole, 0, E_NODE_ID_HERO);
	CSceneMgr::Instace()->AddRole(pMainRole);

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
	schedule( schedule_selector(HelloWorld::GameLoop));
	m_MonsterCreater.SetParentNode(this);
	m_Recognizer.loadTemplates();

	srand((unsigned int)time(NULL));
	return true;
}

void HelloWorld::onEnter()
{
	CCLayer::onEnter();
	m_MonsterCreater.AddMonsterWaveByType(E_MONSTER_WAVE_TYPE_0);
	m_MonsterCreater.AddMonsterWaveByType(E_MONSTER_WAVE_TYPE_1);
	m_MonsterCreater.Begin();
}

void HelloWorld::onExit()
{
	CCLayer::onExit();
	m_MonsterCreater.End();
}

bool HelloWorld::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	CCPoint touchPoint = touch->locationInView( touch->view() );
	m_PathRec.push_back(DollarRecognizer::Point2D(touchPoint.x, touchPoint.y));

	return true;
}

void HelloWorld::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	CCPoint touchPoint = touch->locationInView( touch->view() );

	if (m_PathRec.size() < MAX_RECOGNIZE_POINT)
	{
		m_PathRec.push_back(DollarRecognizer::Point2D(touchPoint.x, touchPoint.y));
	}
}

void HelloWorld::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	CCPoint touchPoint = touch->locationInView( touch->view() );
	touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

	DollarRecognizer::RecognitionResult recResult = m_Recognizer.recognize(m_PathRec);
	m_PathRec.clear();

	// recognized!
	if (recResult.score > 0.8 && recResult.name == "V")
	{
		ProcessGestureV();
		return;
	}

	// Attack!
	CRole* pMainRole = dynamic_cast<CRole*>(this->getChildByTag(E_NODE_ID_HERO));

	if (!pMainRole)
	{
		return;
	}
	CCPoint pntAttacker = pMainRole->getPosition();

	if (touchPoint.x < 80)
	{
		if (touchPoint.y < pntAttacker.y)
		{
			MoveMainRoleDown();
		}
		if (touchPoint.y > pntAttacker.y)
		{
			MoveMainRoleUp();
		}

		return;
	}

	pntAttacker.x += pMainRole->getContentSize().width / 2;
	int nFlyID = pMainRole->BeginAttack(E_ATTACK_TYPE_0, pntAttacker, touchPoint);
}

void HelloWorld::GameLoop( ccTime delta )
{
	if (m_bOver)
	{
		return;
	}
	CSceneMgr* pSceneMgr = CSceneMgr::Instace();

	if (!pSceneMgr)
	{
		return;
	}

	if (pSceneMgr->GetFailAmount() > 5)
	{
		pSceneMgr->Reset();
		this->GameOver();
		return;
	}

	if (pSceneMgr->GetDelMounsterAmount() >= m_MonsterCreater.GetMonsterAmount())
	{
		pSceneMgr->Reset();
		this->GamePass();
		return;
	}

	pSceneMgr->Process();
	m_MonsterCreater.Process();
}

void HelloWorld::draw()
{
	// ª≠ Û±Í ÷ ∆
	if (m_PathRec.size() < 5)
	{
		return;
	}
	glPointSize(20);

	glColor4f(0.0, 0.0, 1.0, 0.5);
	for (int i = 0; i < m_PathRec.size(); i++)
	{
		CCPoint Point = CCDirector::sharedDirector()->convertToGL( CCPointMake(m_PathRec[i].x, m_PathRec[i].y) );
		ccDrawPoint(Point);
	}
	glPointSize(1);
}

void HelloWorld::ProcessGestureV( void )
{
	CRole* pMainRole = (CRole*)(getChildByTag(E_NODE_ID_HERO));

	if (pMainRole || pMainRole->GetPower() < 20)
	{
		return;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bomb = CCSprite::spriteWithFile("drop/0.png");
	bomb->setPosition(ccp(0, winSize.height));

	CCAnimation* animation = CCAnimation::animation();
	char frameName[100] = {0};
	for( int i=0;i<3;i++)
	{
		sprintf(frameName, "drop/%d.png", i);
		animation->addFrameWithFileName(frameName);
	}

	CCActionInterval*  action = CCAnimate::actionWithDuration(0.3, animation, false);
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( action, NULL) );

	bomb->runAction( CCRepeatForever::actionWithAction( seq ));

	CCActionInterval*  move = CCMoveTo::actionWithDuration(1, CCPointMake(winSize.width/2, 0));
	CCCallFuncN* CallFunction = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::Bomb));

	bomb->runAction( CCSequence::actions(move, CallFunction, NULL));

	this->addChild(bomb);
}

void HelloWorld::Bomb( CCNode* sender )
{
	this->removeChild(sender, true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bomb = CCSprite::spriteWithFile("0.png");
	bomb->setPosition(ccp(winSize.width / 2 - bomb->getContentSize().width / 2, bomb->getContentSize().height / 2));

	CCAnimation* animation = CCAnimation::animation();
	char frameName[100] = {0};
	for( int i=0;i<8;i++)
	{
		sprintf(frameName, "%d.png", i);
		animation->addFrameWithFileName(frameName);
	}

	CCActionInterval*  action1 = CCAnimate::actionWithDuration(1, animation, false);
	CCCallFuncN* CallFunction1 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::RemoveBombEffect));

	bomb->runAction( CCSequence::actions(action1, CallFunction1, NULL));

	CCSprite* bomb2 = CCSprite::spriteWithFile("0.png");
	bomb2->setPosition(ccp(winSize.width / 2 + bomb->getContentSize().width / 2, bomb->getContentSize().height / 2));
	bomb2->setFlipX(true);

	CCActionInterval*  action2 = CCAnimate::actionWithDuration(1, animation, false);
	CCCallFuncN* CallFunction2 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::RemoveBombEffect));
	bomb2->runAction( CCSequence::actions(action2, CallFunction2, NULL));

	this->addChild(bomb);
	this->addChild(bomb2);
}

void HelloWorld::RemoveBombEffect( CCNode* sender )
{
	this->removeChild(sender, true);

	CSceneMgr* pSceneMgr = CSceneMgr::Instace();

	for (int i = 0; i < pSceneMgr->GetRoleAmount(); i++)
	{
		CRole* pTarget = pSceneMgr->GetRoleByIndex(i);

		pTarget->MinusLife(100);
	}
}

void HelloWorld::MoveMainRoleUp( void )
{
	CRole* pMainRole = dynamic_cast<CRole*>(this->getChildByTag(E_NODE_ID_HERO));

	if (!pMainRole)
	{
		return;
	}

	CCSize sizeSprite = pMainRole->getContentSize();
	CCPoint point = pMainRole->getPosition();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if (point.y < size.height * 3 / 4)
	{
		pMainRole->setPosition(ccp(sizeSprite.width / 2, point.y + size.height / 4));
	}
}

void HelloWorld::MoveMainRoleDown( void )
{
	CRole* pMainRole = dynamic_cast<CRole*>(this->getChildByTag(E_NODE_ID_HERO));

	if (!pMainRole)
	{
		return;
	}

	CCSize sizeSprite = pMainRole->getContentSize();
	CCPoint point = pMainRole->getPosition();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if (point.y > size.height / 4)
	{
		pMainRole->setPosition(ccp(sizeSprite.width / 2, point.y - size.height / 4));
	}
}

void HelloWorld::GameOver( void )
{
	this->removeChild(m_layerGameInfo, true);
	m_MonsterCreater.End();
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);

	m_bOver = true;

	CStageFail* layer = CStageFail::node();

	if (layer)
	{
		this->addChild(layer);
	}
}

void HelloWorld::GamePass( void )
{
	this->removeChild(m_layerGameInfo, true);
	m_MonsterCreater.End();
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);

	m_bOver = true;

	CStagePass* layer = CStagePass::node();

	if (layer)
	{
		this->addChild(layer);
	}
}