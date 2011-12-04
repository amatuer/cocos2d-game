#include "Role.h"

#include "GameDefine.h"
#include "Flyers.h"
#include "HelloWorldScene.h"
#include "SceneMgr.h"

namespace {
	static int s_FlyersID = E_NODE_ID_FLYER;
}

CRole::CRole(void)
{
	m_nType = -1;		// ½ÇÉ«ÀàÐÍ

	m_nAttack = 0;
	m_nAttVelocity = 100;
	m_nLife = 0;
	m_nMaxLife = 0;
	m_nPower = 0;
	m_nMaxPower = 0;
	//m_nVelocity = 1;
	m_fVelocity = 0.0;
}

CRole::~CRole(void)
{
}

void CRole::SetType( int nType )
{
	m_nType = nType;
}

void CRole::SetAttack( int nAttack )
{
	m_nAttack =nAttack;
}

void CRole::SetAttVelocity( int nVelocity )
{
	m_nAttVelocity = nVelocity;
}

void CRole::SetLife( int nLife )
{
	m_nLife = nLife;
}

void CRole::SetMaxLife( int nLife )
{
	m_nMaxLife = nLife;
}

void CRole::SetPower( int nPower )
{
	m_nPower = nPower;
}

void CRole::SetMaxPower( int nPower )
{
	m_nMaxPower = nPower;
}

// void CRole::SetVelocity( int nVelocity )
// {
// 	m_nVelocity = nVelocity;
// }

int CRole::GetType( void )
{
	return m_nType;
}

int CRole::GetAttack( void )
{
	return m_nAttack;
}

int CRole::GetAttVelocity( void )
{
	return m_nAttVelocity;
}

int CRole::GetLife( void )
{
	return m_nLife;
}

int CRole::GetMaxLife( void )
{
	return m_nMaxLife;
}

int CRole::GetPower( void )
{
	return m_nPower;
}

int CRole::GetMaxPower( void )
{
	return m_nMaxPower;
}

// int CRole::GetVelocity( void )
// {
// 	return m_nVelocity;
// }

int CRole::MinusLife( int nLife )
{
	m_nLife -= nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	return m_nLife;
}

int CRole::MinusPower( int nPower )
{
	m_nPower -= nPower;

	assert(nPower >= 0);

	return m_nPower;
}

int CRole::AddPower( int nPower )
{
	m_nPower += nPower;

	if (m_nPower > m_nMaxPower)
	{
		m_nPower = m_nMaxPower;
	}

	return m_nPower;
}

CRole* CRole::CreateRoleFromFile( char* pFleName )
{
	CRole *pobSprite = new CRole();
	if (pobSprite && pobSprite->initWithFile(pFleName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CRole* CRole::CreateRoleFromeSpriteFrame( CCSpriteFrame* Frame )
{
	CRole *pobSprite = new CRole();
	if (pobSprite && pobSprite->initWithSpriteFrame(Frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CRole* CRole::CreateRoleByType( int nType )
{
	CRole *pobSprite = new CRole();
	if (!pobSprite)
	{
		return NULL;
	}

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame* Frame = NULL;

	if (!cache)
	{
		CC_SAFE_DELETE(pobSprite);
		return NULL;
	}

	switch (nType)
	{
	case E_MONSTER_TYPE_0:
		{
			Frame = cache->spriteFrameByName("brown_ser/0.png");

			if (!pobSprite->initWithSpriteFrame(Frame))
			{
				break;
			}
			pobSprite->autorelease();

			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			int nrand = rand();
			int actualY = (nrand % 3 + 1) * winSize.height / 4;
			pobSprite->setPosition(ccp(winSize.width + (pobSprite->getContentSize().width/2), actualY));
			pobSprite->SetMaxLife(50);
			pobSprite->SetLife(50);
			pobSprite->setVelocity(1.5);
			pobSprite->SetType(E_MONSTER_TYPE_0);

			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(15);

			char str[100] = {0};
			for (int i = 0; i < 13; i++)
			{
				sprintf(str, "brown_ser/%d.png", i);
				CCSpriteFrame* frame = cache->spriteFrameByName( str );
				animFrames->addObject(frame);
			}

			CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( animate, NULL) );

			pobSprite->setFlipX(true);
			pobSprite->runAction(CCRepeatForever::actionWithAction( seq ) );
			animFrames->release();    // win32 : memory leak    2010-0415

			return pobSprite;
		}
		break;
	case E_MONSTER_TYPE_1:
		{
			Frame = cache->spriteFrameByName("scasababy/0.png");

			if (!pobSprite->initWithSpriteFrame(Frame))
			{
				break;
			}
			pobSprite->autorelease();

			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			int nrand = rand();
			int actualY = (nrand % 3 + 1) * winSize.height / 4;
			pobSprite->setPosition(ccp(winSize.width + (pobSprite->getContentSize().width/2), actualY));
			pobSprite->SetMaxLife(50);
			pobSprite->SetLife(80);
			pobSprite->setVelocity(1.0);
			pobSprite->SetType(E_MONSTER_TYPE_1);

			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(15);

			char str[100] = {0};
			for (int i = 0; i < 13; i++)
			{
				sprintf(str, "scasababy/%d.png", i);
				CCSpriteFrame* frame = cache->spriteFrameByName( str );
				animFrames->addObject(frame);
			}

			CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( animate, NULL) );

			pobSprite->setFlipX(true);
			pobSprite->runAction(CCRepeatForever::actionWithAction( seq ) );
			animFrames->release();    // win32 : memory leak    2010-0415

			return pobSprite;
		}
		break;
	default:
		break;
	}

	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void CRole::draw( void )
{
	CCSprite::draw();

	if (m_nLife <= 0)
	{
		return;
	}

	CCRect rectBoundingBox = this->boundingBox();
	float nPercent = (float)m_nLife / m_nMaxLife;
	//float fWidth = nPercent * rectBoundingBox.size.width;
	float fWidth = nPercent * 50;

	glLineWidth(5);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	ccDrawLine(ccp(0, rectBoundingBox.size.height), CCPointMake(fWidth, rectBoundingBox.size.height));

	glLineWidth(1.0f);
}

int CRole::BeginAttack( int nType , CCPoint pntBegin, CCPoint pntDest)
{
	SetAttackAction();

	switch (nType)
	{
	case E_ATTACK_TYPE_0:
		{
			if (m_nPower < 10)
			{
				return E_NODE_ID_INVALID;
			}
			m_nPower -= 10;
			CCNode* pParent = this->getParent();
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			CFlyers *fly = CFlyers::CreateFlyerFromFile("target.png");
			fly->SetAttack(100);
			fly->SetVelocity(12);
			fly->setFlipX(true);
			fly->SetParentID(E_NODE_ID_HERO);
			fly->setPosition(ccp(pntBegin.x, pntBegin.y));

			int offX = pntDest.x - fly->getPosition().x;
			int offY = pntDest.y - fly->getPosition().y;

			if (offX <= 0) return E_NODE_ID_INVALID;

			s_FlyersID++;
			pParent->addChild(fly, 0, s_FlyersID);

			CSceneMgr* pSceneMgr = CSceneMgr::Instace();
			pSceneMgr->AddFly(fly);

			return s_FlyersID;
		}
		break;
	case E_ATTACK_TYPE_1:
		{
			CCNode* pParent = this->getParent();
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			CFlyers *fly = CFlyers::CreateFlyerFromFile("fly.png");
			fly->SetAttack(10);
			fly->SetVelocity(10);
			fly->SetParentID(E_NODE_ID_HERO);
			fly->setPosition(ccp(pntBegin.x, pntBegin.y));

			s_FlyersID++;
			pParent->addChild(fly, 0, s_FlyersID);

			CSceneMgr* pSceneMgr = CSceneMgr::Instace();
			pSceneMgr->AddFly(fly);

			fly->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(0.5, 360) ));

			return s_FlyersID;
		}
		break;
	case E_ATTACK_TYPE_2:
		break;
	case E_ATTACK_TYPE_3:
		break;
	default:
		break;
	}

	return E_NODE_ID_INVALID;
}

void CRole::Die( void )
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	this->stopAllActions();

	switch (m_nType)
	{
	case E_MONSTER_TYPE_0:
		{
			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>;

			CCSpriteFrame* frame0 = cache->spriteFrameByName( "brown_ser/38.png" );
			animFrames->addObject(frame0);
			CCSpriteFrame* frame1 = cache->spriteFrameByName( "brown_ser/39.png" );
			animFrames->addObject(frame1);
			CCSpriteFrame* frame2 = cache->spriteFrameByName( "brown_ser/39.png" );
			animFrames->addObject(frame2);


			CCNode* pParent = this->getParent();
			CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			CCCallFuncN* CallFunction = CCCallFuncN::actionWithTarget(this, callfuncN_selector(CRole::RemoveRole));

			this->setFlipX(true);
			this->runAction( CCSequence::actions(animate, CallFunction, NULL));
			animFrames->release();

			// The main role gains power
			CRole* pMainRole = (CRole*)(pParent->getChildByTag(E_NODE_ID_HERO));

			if (pMainRole)
			{
				pMainRole->PowerGain(E_POWER_GAIN_KILL_MONSTER);
			}
		}
		break;
	case E_MONSTER_TYPE_1:
		{
			CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>;

			CCSpriteFrame* frame0 = cache->spriteFrameByName( "scasababy/23.png" );
			animFrames->addObject(frame0);
			CCSpriteFrame* frame1 = cache->spriteFrameByName( "scasababy/24.png" );
			animFrames->addObject(frame1);
			CCSpriteFrame* frame2 = cache->spriteFrameByName( "scasababy/25.png" );
			animFrames->addObject(frame2);


			CCNode* pParent = this->getParent();
			CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
			CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
			CCCallFuncN* CallFunction = CCCallFuncN::actionWithTarget(this, callfuncN_selector(CRole::RemoveRole));

			this->setFlipX(true);
			this->runAction( CCSequence::actions(animate, CallFunction, NULL));
			animFrames->release();

			// The main role gains power
			CRole* pMainRole = (CRole*)(pParent->getChildByTag(E_NODE_ID_HERO));

			if (pMainRole)
			{
				pMainRole->PowerGain(E_POWER_GAIN_KILL_MONSTER);
			}
		}
		break;
	default:
		RemoveRole(this);
		break;
	}

	CSceneMgr::Instace()->DeleteRole(this);
}

void CRole::SetAttackAction( void )
{
	CCNode* pParent = this->getParent();

	if (!pParent)
	{
		return;
	}
	this->stopAllActions();

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	if (this == pParent->getChildByTag(E_NODE_ID_HERO))
	{
		CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>;

		char str[64] = {0};
		for (int i = 44; i < 49; i++)
		{
			sprintf(str, "poisonhand/%d.png", i);
			CCSpriteFrame* frame = cache->spriteFrameByName( str );
			animFrames->addObject(frame);
		}

		CCSpriteFrame* frame = cache->spriteFrameByName( "poisonhand/44.png" );
		animFrames->addObject(frame);
		CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.1f);
		CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);

		this->runAction(animate);
	}
}

void CRole::RemoveRole( CCNode* sender )
{
	this->getParent()->removeChild(sender, true);
}

void CRole::Process()
{
	int nTag = getTag();

	if (nTag >= E_NODE_ID_TARGET)
	{
		if (m_nLife <= 0)
		{
			Die();
		}
	}

	AutoAttack();
	PowerGain(E_POWER_GAIN_AUTO);
}

void CRole::AutoAttack()
{
	static int s_nCount = 0;
	int nAttVelocity = GetAttVelocity();
	int nTag = getTag();

	if (nAttVelocity <= 0)
	{
		return;
	}

	if (nTag < E_NODE_ID_HERO || nTag >= E_NODE_ID_TARGET)
	{
		return;
	}

	if (s_nCount != GetAttVelocity())
	{
		s_nCount++;
		return;
	}
	s_nCount = 0;

	CCPoint pntAttacker = getPosition();

	pntAttacker.x += getContentSize().width / 2;
	BeginAttack(E_ATTACK_TYPE_1, pntAttacker, ccp(0, 0));
}

void CRole::PowerGain( int nType )
{
	int nTag = getTag();
	if (nTag != E_NODE_ID_HERO)
	{
		return;
	}

	switch (nType)
	{
	case E_POWER_GAIN_AUTO:
		{
			static int nFrameCount = 0;

			nFrameCount++;

			if (nFrameCount == 60)
			{
				nFrameCount = 0;
				m_nPower++;
			}
		}
		break;
	case E_POWER_GAIN_KILL_MONSTER:
		{
			m_nPower += 5;
		}
		break;
	default:
		break;
	}

	if (m_nPower > m_nMaxPower)
	{
		m_nPower = m_nMaxPower;
	}
}