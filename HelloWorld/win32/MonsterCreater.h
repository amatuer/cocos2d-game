#pragma once
#include "cocos2d.h"

USING_NS_CC;
#include "MonsterWave.h"

class CMonsterCreater
{
public:
	CMonsterCreater(void);
	~CMonsterCreater(void);

	CCNode* m_pParent;
	bool m_bBegin;
	int m_nFrameCount;
	std::vector<CMonsterWave*> m_vecMonsterWave;

public:
	void Begin();
	void Pause();
	void End();
	int GetMonsterAmount();
	void SetParentNode(CCNode* pParent);
	void AddMonsterWaveByType(int nType);
	void Process();
};
