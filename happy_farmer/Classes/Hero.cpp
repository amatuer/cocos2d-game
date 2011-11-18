#include "GameConfig.h"
#include "GameLayer.h"
#include "Hero.h"
#include "HeroContactListener.h"
#include "Box2d/Box2D.h"
#include "GameConfig.h"

using namespace cocos2d;

Hero* Hero::heroWithGame(GameLayer* game)
{
	Hero* hero = new Hero(game);
	if (hero) {
		hero->autorelease();
		return hero;
	}

	return NULL;
}

Hero::Hero(GameLayer* game)
{
	game_ = game;
		
	CCSprite* sprite = CCSprite::spriteWithFile("texture/hero.png");
	this->addChild(sprite);

	body_ = NULL;
	radius_ = 14.0f;

	contactListener_ = new HeroContactListener(this);
	game_->getB2World()->SetContactListener(contactListener_);

	this->reset();
}

Hero::~Hero()
{
	game_ = NULL;
	CC_SAFE_DELETE(contactListener_);
}

void Hero::createBox2DBody()
{
	CCPoint startPosition = ccp(0, 300);
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.linearDamping = 0.05f;
	bd.fixedRotation = true;
	bd.position.Set(startPosition.x / PTM_RATIO, startPosition.y / PTM_RATIO);
	body_ = game_->getB2World()->CreateBody(&bd);
	
	b2CircleShape shape;
	shape.m_radius = radius_ / PTM_RATIO;
	
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.5f; // bounce
	fd.friction = 0.2f;
	
	body_->CreateFixture(&fd);
}

void Hero::reset()
{
	flying_ = FALSE;
	diving_ = FALSE;
	nPerfectSlides_ = 0;
	if (body_) {
		game_->getB2World()->DestroyBody(body_);
	}

	this->createBox2DBody();
	this->updateNode();
	this->sleep();
}

void Hero::sleep()
{
	awake_ = FALSE;
	body_->SetActive(false);
}

void Hero::wake()
{
	awake_ = TRUE;
	body_->SetActive(true);
	body_->ApplyLinearImpulse(b2Vec2(1,2), body_->GetPosition());
}

void Hero::updatePhysics()
{
	// apply force if diving
	if (diving_) {
		if (!awake_) {
			this->wake();
			diving_ = TRUE;
		} else {
			body_->ApplyForce(b2Vec2(0,-40), body_->GetPosition());
		}
	}
	
	// limit velocity
	const float minVelocityX = 3;
	const float minVelocityY = -40;
	b2Vec2 vel = body_->GetLinearVelocity();
	if (vel.x < minVelocityX) {
		vel.x = minVelocityX;
	}
	if (vel.y < minVelocityY) {
		vel.y = minVelocityY;
	}
	body_->SetLinearVelocity(vel);
}

void Hero::updateNode()
{
	float x = body_->GetPosition().x * PTM_RATIO;
	float y = body_->GetPosition().y * PTM_RATIO;
	this->setPosition(ccp(x, y));

	// CCNode position and rotation
	b2Vec2 vel = body_->GetLinearVelocity();
	float angle = atan2f(vel.y, vel.x);

	body_->SetTransform(body_->GetPosition(), angle);
	this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
	
	// collision detection
	b2Contact *c = game_->getB2World()->GetContactList();
	if (c) {
		if (flying_) {
			this->landed();
		}
	} else {
		if (!flying_) {
			this->tookOff();
		}
	}
	
	// TEMP: sleep if below the screen
	if (y < - radius_ && awake_) {
		this->sleep();
	}
}

void Hero::landed()
{
//	NSLog(@"landed");
	flying_ = TRUE;
}

void Hero::tookOff()
{
//	NSLog(@"tookOff");
	flying_ = TRUE;
	b2Vec2 vel = body_->GetLinearVelocity();
//	NSLog(@"vel.y = %f",vel.y);
	if (vel.y > kPerfectTakeOffVelocityY) {
//		NSLog(@"perfect slide");
		nPerfectSlides_++;
		if (nPerfectSlides_ > 1) {
			if (nPerfectSlides_ == 4) {
				game_->showFrenzy();
			} else {
				game_->showPerfectSlide();
			}
		}
	}
}

void Hero::hit()
{
//	NSLog(@"hit");
	nPerfectSlides_ = 0;
	game_->showHit();
}

void Hero::setDiving(BOOL diving)
{
	if (diving_ != diving) {
		diving_ = diving;
		// TODO: change sprite image here
	}
}
