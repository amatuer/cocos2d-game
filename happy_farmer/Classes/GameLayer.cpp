#include "GameConfig.h"
#include "GameLayer.h"
#include "Sky.h"
#include "Terrain.h"
#include "Hero.h"

#include "Box2d/Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

CCScene* GameLayer::scene()
{
	CCScene* s = CCScene::node();
	s->addChild(GameLayer::node());
	return s;
}

GameLayer::GameLayer()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	screenW_ = (int)screenSize.width;
	screenH_ = (int)screenSize.height;

	this->createBox2DWorld();

	sky_ = Sky::skyWithTextureSize(1024);
	this->addChild(sky_);

	terrain_ = Terrain::terrainWithWorld(world_);
	this->addChild(terrain_);

	hero_ = Hero::heroWithGame(this);
	terrain_->addChild(hero_);

	resetButton_ = CCSprite::spriteWithFile("texture/resetButton.png");
	this->addChild(resetButton_);

	CCSize size = resetButton_->getContentSize();
	float padding = 8;
	resetButton_->setPosition(ccp(screenW_-size.width/2-padding, screenH_-size.height/2-padding));

	this->registerWithTouchDispatcher();
	this->setIsTouchEnabled(true);
	this->scheduleUpdate();
}

GameLayer::~GameLayer()
{
	sky_ = NULL;
	terrain_ = NULL;
	hero_ = NULL;
	resetButton_ = NULL;

#ifdef DRAW_BOX2D_WORLD
	delete render_;
	render_ = NULL;
#endif
	
	delete world_;
	world_ = NULL;
}

void GameLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, TRUE);
}

void GameLayer::reset()
{
    terrain_->reset();
    hero_->reset();
}

bool GameLayer::ccTouchBegan(CCTouch * touch, CCEvent *event)
{
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	CCPoint pos = resetButton_->getPosition();
	CCSize size = resetButton_->getContentSize();
	float padding = 8;
	float w = size.width+padding*2;
	float h = size.height+padding*2;
	CCRect rect = CCRectMake(pos.x-w/2, pos.y-h/2, w, h);
	if (CCRect::CCRectContainsPoint(rect, location)) {
		this->reset();
	} else {
		hero_->setDiving(TRUE);
	}

	return true;
}

void GameLayer::ccTouchEnded(CCTouch * touch, CCEvent * event)
{
	hero_->setDiving(FALSE);
}

void GameLayer::update(ccTime dt)
{
	hero_->updatePhysics();
	
	world_->Step(dt, 8, 3);
	
	hero_->updateNode();

	// terrain scale and offset
	float x = hero_->getPosition().x;
	float height = hero_->getPosition().y;
	const float minHeight = (float)screenH_*4/5;
	if (height < minHeight) {
		height = minHeight;
	}
	float scale = minHeight / height;
//  	terrain_->setScale(scale);
  	terrain_->setOffsetX(x);
 
 	sky_->setOffsetX(x * 0.2f);
 	sky_->setScale(1.0f-(1.0f- getScale())*0.75f);
}

void GameLayer::createBox2DWorld()
{
	
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
	
	world_ = new b2World(gravity, false);

#ifdef DRAW_BOX2D_WORLD
	
	render_ = new GLESDebugDraw(PTM_RATIO);
	world_->SetDebugDraw(render_);
	
	uint32 flags = 0;
	flags += GLESDebugDraw::e_shapeBit;
//	flags += b2Draw::e_jointBit;
//	flags += b2Draw::e_aabbBit;
//	flags += b2Draw::e_pairBit;
//	flags += b2Draw::e_centerOfMassBit;
	render_->SetFlags(flags);
#endif
}

void GameLayer::showPerfectSlide()
{
	CCLabelBMFont *label = CCLabelBMFont::labelWithString("perfect slide", "good_dog/good_dog_plain_32.fnt");
	label->setPosition(ccp(screenW_/2, screenH_/16));
	label->runAction(CCScaleTo::actionWithDuration(1.0f, 1.2f));
	label->runAction(CCSequence::actions(
					  CCFadeOut::actionWithDuration(1.0f),
					  CCCallFuncND::actionWithTarget(this, callfuncND_selector(GameLayer::removeLabel), (void*)label),
					  NULL));
	this->addChild(label);
}

void GameLayer::showFrenzy()
{
	CCLabelBMFont *label = CCLabelBMFont::labelWithString("FRENZY!", "good_dog/good_dog_plain_32.fnt");
	label->setPosition(ccp(screenW_/2, screenH_/16));
	label->runAction(CCScaleTo::actionWithDuration(2.0f, 1.4f));
	label->runAction(CCSequence::actions(
					  CCFadeOut::actionWithDuration(2.0f),
					  CCCallFuncND::actionWithTarget(this, callfuncND_selector(GameLayer::removeLabel), (void*)label),
					  NULL));
	this->addChild(label);
}

void GameLayer::showHit()
{
	CCLabelBMFont *label = CCLabelBMFont::labelWithString("hit", "good_dog/good_dog_plain_32.fnt");
	label->setPosition(ccp(screenW_/2, screenH_/16));
	label->runAction(CCScaleTo::actionWithDuration(1.0f, 1.2f));
	label->runAction(CCSequence::actions(
					  CCFadeOut::actionWithDuration(1.0f),
					  CCCallFuncND::actionWithTarget(this, callfuncND_selector(GameLayer::removeLabel), (void*)label),
					  NULL));
	this->addChild(label);
}

void GameLayer::removeLabel(CCNode* node, void* data)
{
	CCLabelBMFont* label = (CCLabelBMFont*)data;
	if (label) {
		label->removeFromParentAndCleanup(true);
	}
}

int GameLayer::getWidth() const
{
	return screenW_;
}

int GameLayer::getHeight() const
{
	return screenH_;
}

b2World* GameLayer::getB2World() const
{
	return world_;
}