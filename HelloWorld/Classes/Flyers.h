#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CFlyers :public CCSprite
{
public:
	CFlyers(void);
	~CFlyers(void);
private:
	int m_nType;		// 飞行物类型

	int m_nAttack;
	int m_nVelocity;

	int m_nParentID;
public:
	static CFlyers* CreateFlyerFromFile(char* pFleName);
	static CFlyers* CreateFlyerFromeSpriteFrame(CCSpriteFrame* Frame);

	// init function
	void SetType(int nType);
	void SetParentID(int nID);
	void SetAttack(int nAttack);
	void SetVelocity(int nVelocity);

	int GetType(void);
	int GetParentID(void);
	int GetAttack(void);
	int GetVelocity(void);

};
