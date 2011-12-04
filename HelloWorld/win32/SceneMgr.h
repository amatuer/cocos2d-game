#pragma once
#include "cocos2d.h"

USING_NS_CC;

#include "Role.h"
#include "Flyers.h"

class CSceneMgr
{
public:
	CSceneMgr(void);
	~CSceneMgr(void);

private:
	CCMutableArray<CRole*> *m_pRole;
	CCMutableArray<CRole*> *m_pRoleToDelete;
	CCMutableArray<CFlyers*> *m_pFly;
	CCMutableArray<CFlyers*> *m_pFlyToDelete;

	int m_nFailAmount;
	int m_nDeleteAmount;

	CC_SYNTHESIZE(float, m_nStageLevel, StageLevel)

	void ProcessMove();
	void ProcessCollision();
public:
	void AddRole(CRole* pRole);
	void DeleteRole(CRole* pRole);
	void AddFly(CFlyers* pFly);
	void DeleteFly(CFlyers* pFly);

	int GetRoleAmount();
	CRole* GetRoleByIndex(int nIndex);

	int GetFailAmount(void);
	int GetDelMounsterAmount(void);
	void Process();
	void Reset(void);
	static CSceneMgr* Instace();
};
