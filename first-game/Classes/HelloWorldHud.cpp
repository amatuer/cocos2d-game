/*
 *  HelloWorldHud.cpp
 *  TileBasedGame
 *
 *  Created by Clawoo on 8/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "stdafx.h"
#include "HelloWorldHud.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool HelloWorldHud::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_label = CCLabelTTF::labelWithString("0", CCSizeMake(50, 20), CCTextAlignmentRight, "Verdana-Bold", 18.0);
	_label->setColor(ccc3(0, 0, 0));
	
	int margin = 10;
	
	_label->setPosition(ccp(winSize.width - (_label->getContentSize().width / 2) - margin, 
							_label->getContentSize().height / 2 + margin));
	
	this->addChild(_label);
	
	CCMenuItem *on = CCMenuItemImage::itemFromNormalImage("projectile-button-on.png", "projectile-button-on.png", NULL, NULL);
	CCMenuItem *off = CCMenuItemImage::itemFromNormalImage("projectile-button-off.png", "projectile-button-off.png", NULL, NULL);
	
	CCMenuItemToggle *toggleItem = CCMenuItemToggle::itemWithTarget(this, menu_selector(HelloWorldHud::projectileButtonTapped), off, on, NULL);
	
	CCMenu *toggleMenu = CCMenu::menuWithItems(toggleItem, NULL);
	toggleMenu->setPosition(ccp(100, 32));
	this->addChild(toggleMenu);
	
	return true;
}

void HelloWorldHud::numCollectedChanged(int numCollected)
{
	char *str = (char *)malloc(sizeof(str) * 10);
	sprintf(str, "%d", numCollected);
	_label->setString(str);
	free(str);
}

void HelloWorldHud::projectileButtonTapped(CCObject *sender)
{
	if (_gameLayer->getMode() == 0)
	{
		_gameLayer->setMode(1);
	}
	else {
		_gameLayer->setMode(0);
	}

}