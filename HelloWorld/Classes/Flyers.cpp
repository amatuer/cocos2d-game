#include "Flyers.h"

CFlyers::CFlyers(void)
{
	m_nType = -1;		// 飞行物类型

	m_nAttack = 0;
	m_nVelocity = 1;
	m_nParentID = -1;
}

CFlyers::~CFlyers(void)
{
}

void CFlyers::SetType( int nType )
{
	m_nType = nType;
}

void CFlyers::SetAttack( int nAttack )
{
	m_nAttack =nAttack;
}

void CFlyers::SetVelocity( int nVelocity )
{
	m_nVelocity = nVelocity;
}

int CFlyers::GetType( void )
{
	return m_nType;
}

int CFlyers::GetAttack( void )
{
	return m_nAttack;
}

int CFlyers::GetVelocity( void )
{
	return m_nVelocity;
}

CFlyers* CFlyers::CreateFlyerFromFile( char* pFleName )
{
	CFlyers *pobSprite = new CFlyers();
	if (pobSprite && pobSprite->initWithFile(pFleName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CFlyers* CFlyers::CreateFlyerFromeSpriteFrame( CCSpriteFrame* Frame )
{
	CFlyers *pobSprite = new CFlyers();
	if (pobSprite && pobSprite->initWithSpriteFrame(Frame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void CFlyers::SetParentID( int nID )
{
	m_nParentID = nID;
}

int CFlyers::GetParentID( void )
{
	return m_nParentID;
}