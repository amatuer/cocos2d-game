#pragma once

#include "cocos2d.h"

class Button : public cocos2d::CCMenuItemLabel
{
public:
	Button();

	static Button* itemWithId(const char* btnId, SelectorProtocol* target, cocos2d::SEL_MenuHandler selector);
	static Button * itemWithLabel(CCNode*label, SelectorProtocol* target, cocos2d::SEL_MenuHandler selector);

	void setId(const char* btnId);
	void setBgImage(cocos2d::CCNode* var);
protected:
	CCNode* m_pBgImage;
	std::string m_btnId;
};


class MoveableMenu : public cocos2d::CCMenu
{
public:
	static MoveableMenu* menuWithItems(cocos2d::CCMenuItem* item, ...);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};