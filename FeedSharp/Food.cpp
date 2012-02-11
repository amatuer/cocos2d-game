#include "cocos2d.h"
#include "Food.h"

CFoodMgr::CFoodMgr(void)
{
}

CFoodMgr::~CFoodMgr(void)
{
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
	return 29;
}

float CFoodMgr::GetAX( int nType )
{
	return 0;
}

float CFoodMgr::GetAY( int nType )
{
	return -1;
}

int CFoodMgr::GetFoodAmount( void )
{
	return 3;
}

std::string CFoodMgr::GetFoodTitle(int nType)
{
	return "food";
}

int CFoodMgr::GetFoodFrameAmount( int nType )
{
	return 1;
}
