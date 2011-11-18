#include "GameConfig.h"
#include "Sky.h"

using namespace cocos2d;

Sky* Sky::skyWithTextureSize(int ts)
{
	Sky* sky = new Sky(ts);
	if (sky) {
		sky->autorelease();
		return sky;
	}

	return NULL;
}

Sky::Sky(int ts)
{
	textureSize = ts;

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	screenW = (int)screenSize.width;
	screenH = (int)screenSize.height;

	sprite_ = this->generateSprite();
	this->addChild(sprite_);
}

Sky::~Sky()
{
	sprite_ = NULL;
}

CCSprite* Sky::generateSprite()
{
	
	CCTexture2D *texture = this->generateTexture();
	
	float w = (float)screenW/(float)screenH * textureSize;
	float h = (float)textureSize;
	CCRect rect = CCRectMake(0, 0, w, h);
	
	CCSprite *sprite = CCSprite::spriteWithTexture(texture, rect);
	ccTexParams tp = {GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT};
	sprite->getTexture()->setTexParameters(&tp);
	sprite->setAnchorPoint(ccp(1.0f/8.0f, 0));
	sprite->setPosition(ccp(screenW/8, 0));
	
	return sprite;
}

CCTexture2D* Sky::generateTexture()
{
	CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(textureSize, textureSize);
	
	ccColor3B c = {140, 205, 221};
	ccColor4F cf = ccc4FFromccc3B(c);
	
	rt->beginWithClear(cf.r, cf.g, cf.b, cf.a);
	
	// layer 1: gradient
	
	float gradientAlpha = 0.3f;
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	CCPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;
	
	vertices[nVertices] = ccp(0, 0);
	ccColor4F color = {1.0f, 1.0f, 1.0f, 0.0f};
	colors[nVertices++] = color;
	vertices[nVertices] = ccp(textureSize, 0);
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.a = 0.0f;
	colors[nVertices++] = color;
	
	vertices[nVertices] = ccp(0, textureSize);

	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.a = gradientAlpha;
	colors[nVertices++] = color;
	vertices[nVertices] = ccp(textureSize, textureSize);

	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.a = gradientAlpha;
	colors[nVertices++] = color;
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
	
	// layer 2: noise
	
	CCSprite *s = CCSprite::spriteWithFile("texture/noise.png");

	ccBlendFunc f;
	f.src = GL_DST_COLOR;
	f.dst = GL_ZERO;
	s->setBlendFunc(f);
	s->setPosition(ccp(textureSize/2, textureSize/2));
	s->setScale((float)textureSize/512.0f);
	glColor4f(1,1,1,1);
	s->visit();	
	rt->end();

	return rt->getSprite()->getTexture();
}

void Sky::setOffsetX(float offsetX)
{
	if (offsetX_ != offsetX) {
		offsetX_ = offsetX;
		CCSize size = sprite_->getTextureRect().size;
		sprite_->setTextureRect(CCRectMake(offsetX_, 0, size.width, size.height));
	}
}

void Sky::setScale(float scale)
{
	if (scale_ != scale) {
		const float minScale = (float)screenH / (float)textureSize;
		if (scale < minScale) {
			scale_ = minScale;
		} else {
			scale_ = scale;
		}
		sprite_->setScale(scale_);
	}
}

