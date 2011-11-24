#pragma once

#include "cocos2d.h"
#include "SlotMachineData.h"
#include <deque>

#define kLabelCount 5
#define kTopScale 0.8f
#define kGlassScale 0.5f

#define kLabelTopStart  480.0f
#define kLabelBottomEnd  0.0f
#define kLabelLineSpace	30.0f
#define kLabelHeight  90.0f

#define kAcc 0.3f
#define kMaxSpeed 15.0f

enum {
	SPEED_NONE,	// 静止
	SPEED_EVEN,	// 匀速
	SPEED_ADD,	// 匀加速
	SPEED_DEC,	// 匀减速
};

struct NameLabel {
	cocos2d::CCSprite* bg;
	cocos2d::CCLabelTTF* text;

	void setPosition(cocos2d::CCPoint pt)
	{
		bg->setPosition(pt);
		text->setPosition(pt);
	}

	cocos2d::CCPoint getPosition() const
	{
		return bg->getPosition();
	}

	void modifyPos(cocos2d::CCPoint pt)
	{
		bg->runAction(cocos2d::CCMoveTo::actionWithDuration(0.5f, pt));
		text->runAction(cocos2d::CCMoveTo::actionWithDuration(0.5f, pt));
	}
};

class SlotMachineLayer : public cocos2d::CCLayer
{
public:
	virtual bool init(float x, float y, float width, float height);
	static SlotMachineLayer* node();

	void update(cocos2d::ccTime dt);

	void start();
	void stop();
	bool isStart() const;
	void modifyPos();
private:
	std::deque<NameLabel> m_allLabel;
	cocos2d::CCPoint m_labelPos[kLabelCount];
	cocos2d::CCSprite* m_focusLabel;
	uint32 m_startTime;

	float m_labelHeight;
	float m_speedStep;
	float m_curSpeed;
	bool m_hasReachMaxSpeed;
	int m_speedState;
	
};