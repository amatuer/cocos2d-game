#pragma once

#include "cocos2d.h"

#define LABEL_COUNT 5
#define kTopScale 0.8f
#define kGlassScale 0.5f

#define kLabelTopStart  480.0f
#define kLabelBottomEnd  0.0f
#define kLabelLineSpace	60.0f
#define kLabelLeft  80.0f

#define kAcc 0.3f
#define kMacSpeed 15.0f

enum {
	SPEED_NONE,	// 静止
	SPEED_EVEN,	// 匀速
	SPEED_ADD,	// 匀加速
	SPEED_DEC,	// 匀减速
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
private:
	cocos2d::CCSprite* m_labelBg[LABEL_COUNT];
	cocos2d::CCLabelTTF* m_label[LABEL_COUNT];
	cocos2d::CCSprite* m_focusLabel;
	bool m_startRand;
	float m_curSpeed;
	float m_curAcc;
	uint32 m_startTime;
};