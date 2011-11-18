#pragma once
#include "cocos2d.h"

#define kPerfectTakeOffVelocityY 2.0f

class GameLayer;
class HeroContactListener;
class b2Body;

class Hero : public cocos2d::CCNode
{
public:
	Hero(GameLayer* game);
	~Hero();
	static Hero* heroWithGame(GameLayer* game);

	void reset();
	void sleep();
	void wake();
	void updatePhysics();
	void updateNode();
		 
	void landed();
	void tookOff();
	void hit();
	void setDiving(BOOL diving);
private:
	void createBox2DBody();

	GameLayer *game_;
	b2Body * body_;
	float radius_;
	BOOL awake_;
	BOOL flying_;
	BOOL diving_;
	HeroContactListener * contactListener_;
	int nPerfectSlides_;
};
