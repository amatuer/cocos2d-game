#include "GameConfig.h"

#include "TerrainLayer.h"
#include "../GameCommon/Button.h"
#include "../GameCommon/GuiMgr.h"
#include <boost/lexical_cast.hpp>

using namespace cocos2d;

bool TerrainLayer::init()
{
	CCLayer::init();
	return true;
}

void TerrainLayer::menuCallbackStage(CCObject* pSender)
{
}

void TerrainLayer::setOffsetX(int offsetX)
{
	if (m_heroOffsetX == offsetX) {
		return;
	}

	m_heroOffsetX = offsetX;
}