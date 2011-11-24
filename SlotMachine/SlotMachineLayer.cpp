#include "SlotMachineLayer.h"
#include "../GameCommon/BaseFunc.h"

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

	SlotMachineData::instance().createDataListByNumber(0, 10, "Test", "");

	float top = kLabelTopStart;
	for (int i = 0; i < kLabelCount; ++i) {
		CCSprite* bg = CCSprite::spriteWithFile("sm/labelbg.png");
		this->addChild(bg, 0);

		CCLabelTTF* text = CCLabelTTF::labelWithString(SlotMachineData::instance().getNextName().c_str(), "Arial", 28);
		this->addChild(text, 2);

		CCSize size = bg->getContentSize();
		bg->setScaleX(width / size.width);
		bg->setScaleY(0.8f);

		NameLabel label;
		label.bg = bg;
		label.text = text;

		CCPoint pt = ccp(winSize.width / 2, top);
		label.setPosition(pt);
		m_allLabel.push_back(label);

		m_labelPos[i] = pt;

		top -= size.height / 2 + kLabelLineSpace;
	}

	m_focusLabel = CCSprite::spriteWithFile("sm/labelbgf.png");
	if (m_focusLabel) {
		m_focusLabel->setScaleX(width / m_focusLabel->getContentSize().width);
		m_focusLabel->setScaleY(0.8f);
		m_focusLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		m_focusLabel->setOpacity(0);
		this->addChild(m_focusLabel, 1);
	}

	m_speedState = SPEED_NONE;

	this->scheduleUpdate();
	return true;
}

void SlotMachineLayer::start()
{
	m_curSpeed = 0;
	m_hasReachMaxSpeed = false;
	m_speedState = SPEED_ADD;

	GLubyte opa = m_focusLabel->getOpacity();

	if (opa != 0) {
		m_focusLabel->runAction(CCFadeOut::actionWithDuration(0.2f));
	}

	m_startTime = getTime();
}

void SlotMachineLayer::modifyPos()
{
	for (std::deque<NameLabel>::iterator itr = m_allLabel.begin(); itr != m_allLabel.end(); ++itr) {
		itr->modifyPos(m_labelPos[itr - m_allLabel.begin()]);
	}

	m_focusLabel->setOpacity(0);
	m_focusLabel->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.8f), CCFadeIn::actionWithDuration(0.5f), NULL));
}

void SlotMachineLayer::stop()
{
	m_speedState = SPEED_DEC;
}

void SlotMachineLayer::update(cocos2d::ccTime dt)
{
	if (m_speedState == SPEED_NONE) {
		return;
	}

	if (m_speedState == SPEED_ADD) {
		m_curSpeed += kAcc;

		if (m_curSpeed > kMaxSpeed) {
			m_curSpeed = kMaxSpeed;
			m_speedState = SPEED_EVEN;
		}
	} else if (m_speedState == SPEED_DEC) {
		m_curSpeed -= kAcc;

		if (m_curSpeed < kMaxSpeed) {
			m_curSpeed = 0.0f;
			m_speedState = SPEED_NONE;
			this->modifyPos();
		}
	}

	for (std::deque<NameLabel>::iterator itr = m_allLabel.begin(); itr != m_allLabel.end(); ++itr) {
		NameLabel& label = *itr;
		CCPoint pt = label.getPosition();
		pt.y -= m_curSpeed;
		label.setPosition(pt);
	}

	NameLabel lastLabel = m_allLabel[kLabelCount - 1];
	CCPoint pt = lastLabel.getPosition();
	if (pt.y < m_labelPos[kLabelCount - 1].y) {
		pt.y = m_labelPos[0].y;
		lastLabel.setPosition(pt);
		lastLabel.text->setString(SlotMachineData::instance().getRandomName(m_allLabel[0].text->getString(), m_allLabel[1].text->getString()).c_str());
		m_allLabel.pop_back();
		m_allLabel.push_front(lastLabel);
	}
}

bool SlotMachineLayer::isStart() const
{
	return m_speedState != SPEED_NONE;
}