#pragma once

class CMonsterWave
{
public:
	CMonsterWave(int nType);
	~CMonsterWave(void);
private:
	int m_nType;
	int m_nCount;
public:
	int Process(int nTime);
	int GetType(void);
	int GetMonsterAmount();

	static CMonsterWave* CreateMonsterWave(int nType);
};
