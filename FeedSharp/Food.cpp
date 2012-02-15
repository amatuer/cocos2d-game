#include "cocos2d.h"
#include "Food.h"

CFoodMgr::CFoodMgr(void)
{
}

CFoodMgr::~CFoodMgr(void)
{
	m_mapFoodData.clear();
}

CFoodMgr* CFoodMgr::Instance()
{
	static CFoodMgr* s_pFoodMgr = NULL;

	if (!s_pFoodMgr)
	{
		s_pFoodMgr = new CFoodMgr;

		if (s_pFoodMgr)
		{
			return s_pFoodMgr;
		}
	}

	return s_pFoodMgr;
}

float CFoodMgr::GetVelocity( int nType )
{
	if (m_mapFoodData.size())
	{
		return m_mapFoodData[nType].fVelocity;
	}

	return 0;
}

float CFoodMgr::GetVXRate( int nType )
{
	if (m_mapFoodData.size())
	{
		return m_mapFoodData[nType].fVXRate;
	}
	return 0;
}

float CFoodMgr::GetAY( int nType )
{
	if (m_mapFoodData.size())
	{
		return m_mapFoodData[nType].fAY;
	}
	return -1;
}

int CFoodMgr::GetFoodAmount( void )
{
	return m_mapFoodData.size();
}

int CFoodMgr::GetFoodFrameAmount( int nType )
{
	return 1;
}

void CFoodMgr::InitFoodData( void )
{
	if (m_mapFoodData.size())
	{
		return;
	}

	FOOD_ATTRIB_INFO info;

	info.fVelocity = 29;
	info.fVXRate = 1;
	info.fAY = -1;

	m_mapFoodData[0] = info;

	info.fVXRate = 1.25;
	m_mapFoodData[1] = info;

	info.fVXRate = 0.5;
	m_mapFoodData[2] = info;
}