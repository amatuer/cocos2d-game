#pragma once

class CGameMgr
{
public:
	CGameMgr(void);
	~CGameMgr(void);

private:
	int m_nCurrentFoodType;
	int m_nMaxFood;
	int m_nLeftFood;
public:
	static CGameMgr* Instance();

	inline void SetCurrentFoodType(int nType) { m_nCurrentFoodType = nType; };
	inline int GetCurrentFoodType(void) { return m_nCurrentFoodType; };
	inline void SetMaxFood(int nNum) { m_nMaxFood = nNum; };
	inline int GetMaxFood(void) { return m_nMaxFood; };
	inline void SetLeftFood(int nNum) { m_nLeftFood = nNum; };
	inline int GetLeftFood(void) { return m_nLeftFood; };
};
