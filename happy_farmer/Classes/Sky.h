#pragma once
#include "cocos2d.h"

class Sky : public cocos2d::CCNode {
public:
	static Sky* skyWithTextureSize(int ts);
	Sky(int ts);
	~Sky();

	void setOffsetX(float offsetX);
	void setScale(float scale);
private:
	cocos2d::CCSprite *sprite_;
	float offsetX_;
	float scale_;
	int textureSize;
	int screenW;
	int screenH;

	cocos2d::CCSprite* generateSprite();
	cocos2d::CCTexture2D* generateTexture();
};