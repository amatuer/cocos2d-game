#pragma once
#include <string>
enum {
	E_FOOD_INVALID,
	E_FOOD_SMALL_FISH,
	E_FOOD_BIG_FISH,
	E_GOOD_HEAVY_FISH,
};

class CFoodMgr
{
public:
	CFoodMgr(void);
	~CFoodMgr(void);

//	CC_SYNTHESIZE(int, m_nType, Type)
// 	CC_SYNTHESIZE(float, m_fVelocity, Velocity)
// 	CC_SYNTHESIZE(float, m_fAX, AX)
// 	CC_SYNTHESIZE(float, m_fAY, AY)
	float GetVelocity(int nType);
	float GetAX(int nType);
	float GetAY(int nType);
	int GetFoodFrameAmount(int nType);
	std::string GetFoodTitle(int nType);
	int GetFoodAmount(void);
	
	static CFoodMgr* Instance();
};
