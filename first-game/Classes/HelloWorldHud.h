/*
 *  HelloWorldHud.h
 *  TileBasedGame
 *
 *  Created by Clawoo on 8/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __HELLOWORLD_HUD_H__
#define __HELLOWORLD_HUD_H__

#include "cocos2d.h"

class HelloWorld;

class HelloWorldHud : public cocos2d::CCLayer
{
	cocos2d::CCLabelTTF *_label;
public:
	virtual bool init();
	void numCollectedChanged(int numCollected);
	void projectileButtonTapped(CCObject *sender);
	
	LAYER_NODE_FUNC(HelloWorldHud);

	CC_SYNTHESIZE(HelloWorld *, _gameLayer, GameLayer);
};

#endif