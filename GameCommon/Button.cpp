#include "Button.h"
#include "GuiMgr.h"
#include "StrMgr.h"
#include <boost/lexical_cast.hpp>

using namespace cocos2d;

Button::Button()
{
	m_pBgImage = NULL;
}

Button* Button::itemWithId(const char* btnId, SelectorProtocol* target, cocos2d::SEL_MenuHandler selector)
{
	if (!btnId) {
		return NULL;
	}

	CCSprite* btn_bg = CCSprite::spriteWithFile(GuiMgr::instance().getStr(btnId, "bg-image").c_str());
	CCLabelBMFont* label_play = CCLabelBMFont::labelWithString(LOAD_STRING(GuiMgr::instance().getStr(btnId, "text")),
																GuiMgr::instance().getStr(btnId, "font").c_str());
	Button* btn = Button::itemWithLabel(label_play, target, selector);
	float width = boost::lexical_cast<float>(GuiMgr::instance().getStr(btnId, "width"));
	float height = boost::lexical_cast<float>(GuiMgr::instance().getStr(btnId, "height"));

	// 背景缩放
	CCSize sizeBg = btn_bg->getContentSize();
	btn_bg->setScaleX(width / sizeBg.width);
	btn_bg->setScaleY(height / sizeBg.height);

	// 调整按钮实际大小
	btn->setContentSize(CCSize(width, height));

	// 背景居中
	CCPoint pos = btn->getPosition();
	btn_bg->setAnchorPoint(ccp(0.5f, 0.5f));
	btn_bg->setPosition(ccp(pos.x + width / 2, pos.y + height / 2));
	btn_bg->setIsVisible(true);

	// 文字居中
	label_play->setAnchorPoint(ccp(0.5f, 0.5f));
	label_play->setPosition(ccp(pos.x + width / 2, pos.y + height / 2));

	btn->setBgImage(btn_bg);
	btn->setId(btnId);

	int x = GuiMgr::instance().getData(btnId, "x");
	int y = GuiMgr::instance().getData(btnId, "y");

	if (x != 0) {
		pos.x = (float)x;
	}

	if (y != 0) {
		pos.y = (float)y;
	}

	btn->setPosition(pos);
	
	return btn;
}

void Button::setId(const char* btnId)
{
	m_btnId = btnId;
}

Button * Button::itemWithLabel(CCNode*label, SelectorProtocol* target, SEL_MenuHandler selector)
{
	Button *pRet = new Button();
	pRet->initWithLabel(label, target, selector);
	pRet->autorelease();
	return pRet;
}

void Button::setBgImage(CCNode* var)
{
	if (var) {
		addChild(var, -1);
	}

	if (m_pBgImage) {
		removeChild(m_pBgImage, true);
	}
	m_pBgImage = var;
}


bool MoveableMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return CCMenu::ccTouchBegan(touch, event);
}
void MoveableMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (m_pSelectedItem) {
		CCPoint pt = m_pSelectedItem->getPosition();
		CCLOG("btn%d: %f  %f", m_pSelectedItem->getTag(), pt.x, pt.y);
	}
	CCMenu::ccTouchEnded(touch, event);
}
void MoveableMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CCMenu::ccTouchCancelled(touch, event);
}
void MoveableMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (m_pSelectedItem) {
		CCPoint touchLocation = touch->locationInView(touch->view());
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
		touchLocation = this->convertToNodeSpace(touchLocation);

		m_pSelectedItem->setPosition(touchLocation);
		return;
	}
	CCMenu::ccTouchMoved(touch, event);
}

MoveableMenu * MoveableMenu::menuWithItems(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	MoveableMenu *pRet = new MoveableMenu();
	if (pRet && pRet->initWithItems(item, args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet)
	return NULL;
}