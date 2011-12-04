#include "MonsterWave.h"

#include "GameDefine.h"

CMonsterWave::CMonsterWave(int nType)
{
	m_nType = nType;
	m_nCount = 0;
}

CMonsterWave::~CMonsterWave(void)
{
}
CMonsterWave* CMonsterWave::CreateMonsterWave( int nType )
{
	CMonsterWave* pMonsterWave = new CMonsterWave(nType);

	return pMonsterWave;
}

int CMonsterWave::Process( int nTime )
{
	switch (m_nType)
	{
	case E_MONSTER_WAVE_TYPE_0:
		{
			const int START_TIME = 0;
			const int END_TIME = 60*22;
			const int VELOCITY = 120;
			const int MAX_COUNT = 8;
			static int s_nFrameCount = 0;

			if (nTime > START_TIME && nTime <= END_TIME && m_nCount < MAX_COUNT)
			{
				// 定时出怪
				s_nFrameCount++;

				if (s_nFrameCount > VELOCITY)
				{
					s_nFrameCount = 0;
					m_nCount++;
					return E_MONSTER_TYPE_0;
				}
			}
		}
		break;
	case E_MONSTER_WAVE_TYPE_1:
		{
			const int START_TIME = 60 * 10;
			const int END_TIME = 60*22;
			const int VELOCITY = 150;
			const int MAX_COUNT = 4;
			static int s_nFrameCount = 0;

			if (nTime > START_TIME && nTime <= END_TIME && m_nCount < MAX_COUNT)
			{
				// 定时出怪
				s_nFrameCount++;

				if (s_nFrameCount > VELOCITY)
				{
					s_nFrameCount = 0;
					m_nCount++;
					return E_MONSTER_TYPE_1;
				}
			}
		}
		break;
	default:
		break;
	}

	return E_MONSTER_TYPE_INVALID;
}

int CMonsterWave::GetType( void )
{
	return m_nType;
}

int CMonsterWave::GetMonsterAmount()
{
	switch (m_nType)
	{
	case E_MONSTER_WAVE_TYPE_0:
		{
			const int MAX_COUNT = 8;

			return MAX_COUNT;
		}
		break;
	case E_MONSTER_WAVE_TYPE_1:
		{
			const int MAX_COUNT = 4;

			return MAX_COUNT;
		}
		break;
	default:
		break;
	}

	return 0;
}