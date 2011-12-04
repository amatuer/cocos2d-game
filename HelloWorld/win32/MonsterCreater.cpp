#include "MonsterCreater.h"

#include "GameDefine.h"
#include "SceneMgr.h"
#include "Role.h"

static int s_nTargetID = E_NODE_ID_TARGET;

CMonsterCreater::CMonsterCreater(void)
{
	m_pParent = NULL;
	m_bBegin = false;
	m_nFrameCount = 0;
}

CMonsterCreater::~CMonsterCreater(void)
{
	m_vecMonsterWave.clear();
}

void CMonsterCreater::Process()
{
	if (!m_bBegin)
	{
		m_nFrameCount = 0;
		return;
	}

	m_nFrameCount++;

	std::vector<CMonsterWave*>::const_iterator iter = m_vecMonsterWave.begin();
	CSceneMgr* pSceneMgr = CSceneMgr::Instace();

	for (; iter != m_vecMonsterWave.end(); ++iter)
	{
		int nMonsterType = (*iter)->Process(m_nFrameCount);

		if (nMonsterType != E_MONSTER_TYPE_INVALID)
		{
			CRole* role = CRole::CreateRoleByType(nMonsterType);

			if (m_pParent && role)
			{
				s_nTargetID++;
				m_pParent->addChild(role, 0, s_nTargetID);
			}

			if (pSceneMgr && role)
			{
				pSceneMgr->AddRole(role);
			}
		}
	}
}

void CMonsterCreater::Begin()
{
	m_bBegin = true;
}

void CMonsterCreater::End()
{
	m_bBegin = false;
	m_vecMonsterWave.clear();
}

void CMonsterCreater::AddMonsterWaveByType( int nType )
{
	CMonsterWave* wave = CMonsterWave::CreateMonsterWave(nType);

	if (!wave)
	{
		return;
	}

	m_vecMonsterWave.push_back(wave);
}

void CMonsterCreater::SetParentNode( CCNode* pParent )
{
	m_pParent = pParent;
}

void CMonsterCreater::Pause()
{
	m_bBegin = false;
}

int CMonsterCreater::GetMonsterAmount()
{
	int nAmount = 0;
	std::vector<CMonsterWave*>::const_iterator iter = m_vecMonsterWave.begin();

	for (;iter != m_vecMonsterWave.end(); ++iter)
	{
		nAmount += (*iter)->GetMonsterAmount();
	}

	return nAmount;
}
