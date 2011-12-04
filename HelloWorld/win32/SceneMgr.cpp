#include "SceneMgr.h"
#include "GameDefine.h"

CSceneMgr::CSceneMgr(void)
{
	m_pRole = new CCMutableArray<CRole*>;
	m_pFly = new CCMutableArray<CFlyers*>;
	m_pRoleToDelete = new CCMutableArray<CRole*>;
	m_pFlyToDelete = new CCMutableArray<CFlyers*>;

	m_nFailAmount = 0;
	m_nDeleteAmount = 0;
	m_nStageLevel = 0;
}

CSceneMgr::~CSceneMgr(void)
{
	if (m_pRole)
	{
		m_pRole->release();
	}
	if (m_pFly)
	{
		m_pFly->release();
	}
	if (m_pRoleToDelete)
	{
		m_pRoleToDelete->release();
	}
	if (m_pFlyToDelete)
	{
		m_pFlyToDelete->release();
	}
}

CSceneMgr* CSceneMgr::Instace()
{
	static CSceneMgr* s_pSceneMgr = NULL;

	if (!s_pSceneMgr)
	{
		s_pSceneMgr = new CSceneMgr;

		if (s_pSceneMgr)
		{
			return s_pSceneMgr;
		}
	}

	return s_pSceneMgr;
}

void CSceneMgr::AddRole( CRole* pRole )
{
	if (!pRole)
	{
		return;
	}
	m_pRole->addObject(pRole);
}

void CSceneMgr::AddFly( CFlyers* pFly )
{
	if (!pFly)
	{
		return;
	}
	m_pFly->addObject(pFly);
}

void CSceneMgr::Process()
{

	CCMutableArray<CRole*>::CCMutableArrayIterator iterRoleToDle = m_pRoleToDelete->begin();
	for (; iterRoleToDle != m_pRoleToDelete->end(); ++iterRoleToDle)
	{
		m_pRole->removeObject(*iterRoleToDle);
		m_nDeleteAmount++;
	}
	m_pRoleToDelete->removeAllObjects();

// 	CCMutableArray<CRole*>::CCMutableArrayIterator iterFlyToDle = m_pFlyToDelete->begin();
// 	for (; iterFlyToDle != m_pFlyToDelete->end(); ++iterFlyToDle)
// 	{
// 		m_pFly->removeObject(*iterFlyToDle);
// 	}
// 	m_pFlyToDelete->removeAllObjects();

	ProcessMove();
	ProcessCollision();

	CCMutableArray<CRole*>::CCMutableArrayIterator iterRole = m_pRole->begin();
	
	for (; iterRole != m_pRole->end(); ++iterRole)
	{
		(*iterRole)->Process();
	}
}

void CSceneMgr::ProcessMove()
{
	CCMutableArray<CRole*>::CCMutableArrayIterator iterRole = m_pRole->begin();
	CCMutableArray<CRole*> *RoleToDelete = new CCMutableArray<CRole*>;

	for (; iterRole != m_pRole->end(); ++iterRole)
	{
		CRole* pRole = *iterRole;

		CCPoint point = pRole->getPosition();

		if (point.x < 0)
		{
			RoleToDelete->addObject(pRole);
			m_nFailAmount++;
			m_nDeleteAmount++;
		}
		else
		{
			point.x -= pRole->getVelocity();
			pRole->setPosition(point);
		}
	}

	// delete target
	CCMutableArray<CRole*>::CCMutableArrayIterator iterDelete = RoleToDelete->begin();
	for (; iterDelete != RoleToDelete->end(); ++iterDelete)
	{
		CRole* pDelTarget = *iterDelete;

		if (pDelTarget)
		{
			CCNode* pParent = pDelTarget->getParent();
			if (pParent)
			{
				pParent->removeChild(pDelTarget, true);
			}
		}
		m_pRole->removeObject(pDelTarget);
	}
	RoleToDelete->removeAllObjects(true);
	RoleToDelete->release();

	CCMutableArray<CFlyers*>::CCMutableArrayIterator iterFlyers = m_pFly->begin();
	CCMutableArray<CFlyers*> *FlyToDelete = new CCMutableArray<CFlyers*>;

	for (; iterFlyers != m_pFly->end(); ++iterFlyers)
	{
		CFlyers* pFly = *iterFlyers;

		CCPoint point = pFly->getPosition();

		if (point.x > 480)
		{
			FlyToDelete->addObject(pFly);
		}
		else
		{
			point.x += pFly->GetVelocity();
			pFly->setPosition(point);
		}
	}

	// delete fly

	CCMutableArray<CFlyers*>::CCMutableArrayIterator iterDeleteFly = FlyToDelete->begin();
	for (; iterDeleteFly != FlyToDelete->end(); ++iterDeleteFly)
	{
		CFlyers* pDelTarget = *iterDeleteFly;

		if (pDelTarget)
		{
			CCNode* pParent = pDelTarget->getParent();
			if (pParent)
			{
				pParent->removeChild(pDelTarget, true);
			}
		}
		m_pFly->removeObject(pDelTarget);
	}

	FlyToDelete->release();
}

void CSceneMgr::ProcessCollision()
{
	CCMutableArray<CFlyers*> *FlyToDelete = new CCMutableArray<CFlyers*>;
	CCMutableArray<CFlyers*>::CCMutableArrayIterator iterFly = m_pFly->begin();

	for (; iterFly != m_pFly->end(); ++iterFly)
	{
		CCMutableArray<CRole*>::CCMutableArrayIterator iterRole = m_pRole->begin();

		CFlyers* pFly = *iterFly;
		CCRect FlyRect = CCRectMake(
			pFly->getPosition().x - (pFly->getContentSize().width/2),
			pFly->getPosition().y - (pFly->getContentSize().height/2),
			pFly->getContentSize().width,
			pFly->getContentSize().height);

		CCMutableArray<CRole*> *RoleToDelete = new CCMutableArray<CRole*>;

		// record
		for (; iterRole != m_pRole->end(); ++iterRole)
		{
			CRole* pRole = *iterRole;
			int nTag = pRole->getTag();

			if (nTag >= E_NODE_ID_HERO && nTag < E_NODE_ID_TARGET)
			{
				continue;
			}

			CCRect roleRect = CCRectMake(
				pRole->getPosition().x - (pRole->getContentSize().width/2),
				pRole->getPosition().y - (pRole->getContentSize().height/2),
				pRole->getContentSize().width,
				pRole->getContentSize().height);


			if (CCRect::CCRectIntersectsRect(FlyRect, roleRect))
			{
				RoleToDelete->addObject(pRole);
			}
		}

		if (RoleToDelete->count() > 0)
		{
			FlyToDelete->addObject(pFly);
		}

		// delete target
		CCMutableArray<CRole*>::CCMutableArrayIterator iterDelete = RoleToDelete->begin();
		for (; iterDelete != RoleToDelete->end(); ++iterDelete)
		{
			CRole* pDelTarget = *iterDelete;
			CFlyers* Fly = pFly;

			int nAttact = Fly->GetAttack();
			int nID = Fly->GetParentID();
			CCNode* pParent = Fly->getParent()->getChildByTag(nID);

			pDelTarget->MinusLife(dynamic_cast<CRole*>(pParent)->GetAttack() + nAttact);
		}

		RoleToDelete->release();
	}

	// delete fly
	CCMutableArray<CFlyers*>::CCMutableArrayIterator iterDelete = FlyToDelete->begin();
	for (; iterDelete != FlyToDelete->end(); ++iterDelete)
	{
		CFlyers* pDelTarget = *iterDelete;

		pDelTarget->removeFromParentAndCleanup(true);
		m_pFly->removeObject(pDelTarget);
	}

	FlyToDelete->release();
}

int CSceneMgr::GetRoleAmount()
{
	return m_pRole->count();
}

CRole* CSceneMgr::GetRoleByIndex( int nIndex )
{
	return *(m_pRole->begin() + nIndex);
}

void CSceneMgr::DeleteRole( CRole* pRole )
{
	m_pRoleToDelete->addObject(pRole);
}

void CSceneMgr::DeleteFly( CFlyers* pFly )
{
	m_pFlyToDelete->addObject(pFly);
}

int CSceneMgr::GetFailAmount( void )
{
	return m_nFailAmount;
}

void CSceneMgr::Reset( void )
{
	m_nFailAmount = 0;
	m_nDeleteAmount = 0;
	m_pRole->removeAllObjects();
	m_pFly->removeAllObjects();
	m_pRoleToDelete->removeAllObjects();
	m_pFlyToDelete->removeAllObjects();
}

int CSceneMgr::GetDelMounsterAmount( void )
{
	return m_nDeleteAmount;
}