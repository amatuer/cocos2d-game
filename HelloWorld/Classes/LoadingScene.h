#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class CLoadingScene : public CCScene
{
public:
	CLoadingScene(void);
	~CLoadingScene(void);

	virtual void onEnter();
	virtual void StartGameCallback(CCObject* pSender);
};
