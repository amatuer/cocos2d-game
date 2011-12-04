#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum {
	E_POWER_GAIN_AUTO,
	E_POWER_GAIN_KILL_MONSTER,
};

class CRole :public CCSprite
{
public:
	CRole(void);
	~CRole(void);
private:
	int m_nType;		// ½ÇÉ«ÀàÐÍ

	int m_nAttack;
	int m_nAttVelocity;
	int m_nLife;
	int m_nMaxLife;
	int m_nPower;
	int m_nMaxPower;
	//int m_nVelocity;

public:
	static CRole* CreateRoleByType(int nType);
	static CRole* CreateRoleFromFile(char* pFleName);
	static CRole* CreateRoleFromeSpriteFrame(CCSpriteFrame* Frame);

	CC_SYNTHESIZE(float, m_fVelocity, Velocity)
	// init function
	void SetType(int nType);
	void SetAttack(int nAttack);
	void SetAttVelocity(int nVelocity);
	void SetLife(int nLife);
	void SetMaxLife(int nLife);
	void SetPower(int nPower);
	void SetMaxPower(int nPower);
	//void SetVelocity(int nVelocity);

	int GetType(void);
	int GetAttack(void);
	int GetAttVelocity(void);
	int GetLife(void);
	int GetMaxLife(void);
	int GetPower(void);
	int GetMaxPower(void);
	//int GetVelocity(void);

	// 
	int BeginAttack(int nType , CCPoint pntBegin, CCPoint pntDest);
	int AddPower(int nPower);
	int MinusLife(int nLife);
	int MinusPower(int nPower);
	void Die(void);
	void Process();
	void AutoAttack();
	void PowerGain(int nType);

	virtual void draw(void);
	void RemoveRole(CCNode* sender);

private:
	void SetAttackAction(void);
};
