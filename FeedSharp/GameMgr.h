#pragma once

class CGameMgr
{
public:
	CGameMgr(void);
	~CGameMgr(void);

private:
	int m_nCurrentFoodType;
public:
	static CGameMgr* Instance();

	inline void SetCurrentFoodType(int nType) { m_nCurrentFoodType = nType; };
	inline int GetCurrentFoodType(void) { return m_nCurrentFoodType; };
};
