#include "SlotMachineLayer.h"
#include "SlotMachineData.h"

#pragma warning (disable:4996)
using namespace cocos2d;

SlotMachineLayer* SlotMachineLayer::node()
{
	SlotMachineLayer* ret = new SlotMachineLayer;
	if (ret) {
		ret->autorelease();
		return ret;
	}

	return NULL;
}

bool SlotMachineLayer::init(float x, float y, float width, float height)
{
	CCLayer::init();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float top = kLabelTopStart;
	char text[128] = {0};
	for (int i = 0; i < LABEL_COUNT; ++i) {
		m_labelBg[i] = CCSprite::spriteWithFile("sm/labelbg.png");
		this->addChild(m_labelBg[i], 0);

		CCSize size = m_labelBg[i]->getContentSize();
		CCPoint pt = ccp(winSize.width / 2, top);
		m_labelBg[i]->setPosition(pt);
		m_labelBg[i]->setScaleX(width / size.width);
		m_labelBg[i]->setScaleY(0.8f);

		_snprintf(text, sizeof(text) - 1, "Test%d", i);
		m_label[i] = CCLabelTTF::labelWithString(text, "Arial", 28);
		this->addChild(m_label[i], 1);
		m_label[i]->setPosition(pt);

		top -= size.height / 2 + kLabelLineSpace;
	}

	m_focusLabel = CCSprite::spriteWithFile("sm/labelbgf.png");
	if (m_focusLabel) {
		m_focusLabel->setScaleX(width / m_focusLabel->getContentSize().width);
		m_focusLabel->setScaleY(0.8f);
		m_focusLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(m_focusLabel, 1);
		m_focusLabel->setIsVisible(false);
	}

	m_startRand = false;
	m_curSpeed = 0;
	m_curAcc = 0;

	SlotMachineData::instance().createDataListByNumber(0, 10, "Test", "");

	this->scheduleUpdate();
	return true;
}

void SlotMachineLayer::start()
{
	m_startRand = true;
	m_startTime = getTime();
}


