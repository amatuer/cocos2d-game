#include "cocos2d.h"
#include "GameMgr.h"

CGameMgr::CGameMgr(void)
{
	m_nCurrentFoodType = 0;
}

CGameMgr::~CGameMgr(void)
{
}

CGameMgr* CGameMgr::Instance()
{
	static CGameMgr* s_pGameMgr = NULL;

	if (!s_pGameMgr)
	{
		s_pGameMgr = new CGameMgr;

		if (s_pGameMgr)
		{
			return s_pGameMgr;
		}
	}

	return s_pGameMgr;
}