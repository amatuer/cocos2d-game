#pragma once
#include <string>
#include <map>

enum {
	E_FOOD_INVALID,
	E_FOOD_SMALL_FISH,
	E_FOOD_BIG_FISH,
	E_GOOD_HEAVY_FISH,
};

struct FOOD_ATTRIB_INFO 
{
	float fVelocity;	// ���ٶ�
	float fVXRate;		// ˮƽ�ٶȵ�����ϵ����ģ�����Ʒ���ص�Ч����
	float fAY;			// �������ٶ�
};

typedef std::map<int, FOOD_ATTRIB_INFO> MAP_FOOD_DATA;
class CFoodMgr
{
public:
	CFoodMgr(void);
	~CFoodMgr(void);

	MAP_FOOD_DATA m_mapFoodData;
//	CC_SYNTHESIZE(int, m_nType, Type)
// 	CC_SYNTHESIZE(float, m_fVelocity, Velocity)
// 	CC_SYNTHESIZE(float, m_fAX, AX)
// 	CC_SYNTHESIZE(float, m_fAY, AY)
	void InitFoodData(void);
	float GetVelocity(int nType);
	float GetVXRate(int nType);
	float GetAY(int nType);
	int GetFoodFrameAmount(int nType);
	int GetFoodAmount(void);
	
	static CFoodMgr* Instance();
};
