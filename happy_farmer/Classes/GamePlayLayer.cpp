#include "GameConfig.h"

#include "GamePlayLayer.h"
#include "../GameCommon/Button.h"
#include "../GameCommon/GuiMgr.h"
#include "BackgroundLayer.h"
#include "TerrainLayer.h"
#include <boost/lexical_cast.hpp>

using namespace cocos2d;

enum {
	BG_LAYER,
	TERRAIN_LAYER,
	HERO_LAYER,
};

CCScene* GamePlayLayer::scene()
{
	CCScene * scene = CCScene::node();
	CCLayer* layer = GamePlayLayer::node();
	if (layer && scene) {
		scene->addChild(layer);
		return scene;
	}

	return NULL;
}

bool GamePlayLayer::init()
{
	CCLayer::init();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	m_background = BackgroundLayer::node();
	if (m_background) {
		m_background->setTag(BG_LAYER);
		this->addChild(m_background, -1);
	}

	m_terrain = TerrainLayer::node();
	if (m_terrain) {
		m_terrain->setTag(TERRAIN_LAYER);
		this->addChild(m_terrain, 1);
	}

	m_heroOffsetX = 0;
	m_acc = 0;

	this->setIsTouchEnabled(true);
	this->scheduleUpdate();

	return true;
}

void GamePlayLayer::menuCallbackStage(CCObject* pSender)
{
}

void GamePlayLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, TRUE);
}

bool GamePlayLayer::ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event)
{
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (location.x > winSize.width * 2 / 3) {
		m_acc = 1;
	} else if (location.x < winSize.width / 3) {
		m_acc = -1;
	}

	return true;
}

void GamePlayLayer::ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event)
{
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

	m_acc = 0;
}

void GamePlayLayer::update(ccTime dt)
{
	if (m_acc == -1) {
		setOffsetX(m_heroOffsetX - 5);
	} else if (m_acc == 1) {
		setOffsetX(m_heroOffsetX + 5);
	}
}

void GamePlayLayer::setOffsetX(int offsetX)
{
	if (m_heroOffsetX == offsetX) {
		return;
	}

	m_heroOffsetX = offsetX;
	
	if (m_background) {
		m_background->setOffsetX(m_heroOffsetX);
	}

	if (m_terrain) {
		m_terrain->setOffsetX(m_heroOffsetX);
	}
}