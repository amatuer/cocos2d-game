//
//  HelloWorldScene.cpp
//  TileBasedGame
//
//  Created by Clawoo on 8/17/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#include "stdafx.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <string>

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	HelloWorldHud *hud = HelloWorldHud::node();
	hud->retain();
	scene->addChild(hud);
	layer->setHud(hud);
	hud->setGameLayer(layer);

	// return the scene
	return scene;
}

HelloWorld::~HelloWorld()
{
	CC_SAFE_RELEASE_NULL(_tileMap);
	CC_SAFE_RELEASE_NULL(_background);
	CC_SAFE_RELEASE_NULL(_foreground);
	CC_SAFE_RELEASE_NULL(_player);
	CC_SAFE_RELEASE_NULL(_meta);
	CC_SAFE_RELEASE_NULL(_hud);
	CC_SAFE_RELEASE_NULL(_enemies);
	CC_SAFE_RELEASE_NULL(_projectiles);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	SimpleAudioEngine::sharedEngine()->preloadEffect("pickup.caf");
	SimpleAudioEngine::sharedEngine()->preloadEffect("hit.caf");
	SimpleAudioEngine::sharedEngine()->preloadEffect("move.caf");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TileMap.caf");
	
	_enemies = new CCMutableArray<CCSprite *>;
	_projectiles = new CCMutableArray<CCSprite *>;
	
	_tileMap = CCTMXTiledMap::tiledMapWithTMXFile("TileMap.tmx");
    _tileMap->retain();
    
	_background = _tileMap->layerNamed("Background");
    _background->retain();
    
	_foreground = _tileMap->layerNamed("Foreground");
    _foreground->retain();
	
	_meta = _tileMap->layerNamed("Meta");
	_meta->retain();
	
	CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Objects");
	CCAssert(objects != NULL, "'Objects' object group not found");
	
	CCStringToStringDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
	CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
	int x = spawnPoint->objectForKey("x")->toInt();
	int y = spawnPoint->objectForKey("y")->toInt();
	
    this->addChild(_tileMap);

	_player = CCSprite::spriteWithFile("Player.png");
	_player->retain();
	_player->setPosition(ccp (x, y));
	this->addChild(_player);
	
	this->setViewpointCenter(_player->getPosition());
	
	CCMutableArray<CCStringToStringDictionary*> *allObjects = objects->getObjects();
	CCMutableArray<CCStringToStringDictionary*>::CCMutableArrayIterator it;
	for (it = allObjects->begin(); it != allObjects->end(); ++it)
	{
		if ((*it)->objectForKey(std::string("Enemy")) != NULL)
		{
			int x = (*it)->objectForKey("x")->toInt();
			int y = (*it)->objectForKey("y")->toInt();
			this->addEnemyAt(x, y);
		}
	}
	
	this->setIsTouchEnabled(true);
	
	_numCollected = 0;
	
	_mode = 0;
	
	this->schedule(schedule_selector(HelloWorld::testCollisions));
	
	return true;
}

void HelloWorld::setViewpointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width/2);
	x = MIN(x, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
	
	CCPoint actualPosition = ccp(x, y);
	
	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	
	this->setPosition(viewPoint);
}

void HelloWorld::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	return true;
}

void HelloWorld::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	if (_mode == 0)
	{
		CCPoint touchLocation = touch->locationInView(touch->view());
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
		touchLocation = this->convertToNodeSpace(touchLocation);
		
		CCPoint playerPos = _player->getPosition();
		CCPoint diff = ccpSub(touchLocation, playerPos);
		
		// using fabs because using abs throws a "abs in ambiguous" error
		if (fabs(diff.x) > fabs(diff.y)) {
			if (diff.x > 0) {
				playerPos.x += _tileMap->getTileSize().width;
			} else {
				playerPos.x -= _tileMap->getTileSize().width; 
			}    
		} else {
			if (diff.y > 0) {
				playerPos.y += _tileMap->getTileSize().height;
			} else {
				playerPos.y -= _tileMap->getTileSize().height;
			}
		}
		
		if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
			playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
			playerPos.y >= 0 &&
			playerPos.x >= 0 ) 
		{
			this->setPlayerPosition(playerPos);
		}
		
		this->setViewpointCenter(_player->getPosition());
	}
	else {
		// Find where the touch is
		CCPoint touchLocation = touch->locationInView(touch->view());
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
		touchLocation = this->convertToNodeSpace(touchLocation);
		
		// Create a projectile and put it at the player's location
		CCSprite *projectile = CCSprite::spriteWithFile("Projectile.png");
		projectile->setPosition(_player->getPosition());
		this->addChild(projectile);
		
		// Determine where we wish to shoot the projectile to
		int realX;
		
		// Are we shooting to the left or right?
		CCPoint diff = ccpSub(touchLocation, _player->getPosition());
		if (diff.x > 0)
		{
			realX = (_tileMap->getMapSize().width * _tileMap->getTileSize().width) +
				(projectile->getContentSize().width/2);
		} else {
			realX = -(_tileMap	->getMapSize().width * _tileMap->getTileSize().width) -
				(projectile->getContentSize().width/2);
		}
		float ratio = (float) diff.y / (float) diff.x;
		int realY = ((realX - projectile->getPosition().x) * ratio) + projectile->getPosition().y;
		CCPoint realDest = ccp(realX, realY);
		
		
		// Determine the length of how far we're shooting
		int offRealX = realX - projectile->getPosition().x;
		int offRealY = realY - projectile->getPosition().y;
		float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
		float velocity = 480/1; // 480pixels/1sec
		float realMoveDuration = length/velocity;
		
		// Move projectile to actual endpoint
		CCFiniteTimeAction *actionMoveTo = CCMoveTo::actionWithDuration(realMoveDuration, realDest);
		CCCallFuncN *actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::projectileMoveFinished));
		projectile->runAction(CCSequence::actionOneTwo(actionMoveTo, actionMoveDone));
		
		_projectiles->addObject(projectile);
	}

}

void HelloWorld::setPlayerPosition(cocos2d::CCPoint position)
{
	CCPoint tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		CCDictionary<std::string, CCString*> *properties = _tileMap->propertiesForGID(tileGid);
		if (properties)
		{
			CCString *collision = properties->objectForKey("Collidable");
			if (collision && (collision->toStdString().compare("True") == 0))
			{
				SimpleAudioEngine::sharedEngine()->playEffect("hit.caf");
				return;
			}
			
			CCString *collectable = properties->objectForKey("Collectable");
			if (collectable && (collectable->toStdString().compare("True") == 0))
			{
				_meta->removeTileAt(tileCoord);
				_foreground->removeTileAt(tileCoord);
				
				_numCollected++;
				_hud->numCollectedChanged(_numCollected);
				SimpleAudioEngine::sharedEngine()->playEffect("pickup.caf");
				
				if (_numCollected == 2) {
					this->win();
				}
			}
		}
	}
	SimpleAudioEngine::sharedEngine()->playEffect("move.caf");
	_player->setPosition(position);
}

CCPoint HelloWorld::tileCoordForPosition(cocos2d::CCPoint position)
{
	int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

void HelloWorld::addEnemyAt(int x, int y)
{
	CCSprite *enemy = CCSprite::spriteWithFile("enemy1.png");
	enemy->retain();
	enemy->setPosition(ccp(x, y));
	this->addChild(enemy);
	// Use our animation method and
	// start the enemy moving toward the player
	this->animateEnemy(enemy);
	_enemies->addObject(enemy);
}

// callback. starts another iteration of enemy movement.
void HelloWorld::enemyMoveFinished(cocos2d::CCNode *enemy)
{
	this->animateEnemy((cocos2d::CCSprite *)enemy);
}

// a method to move the enemy 10 pixels toward the player
void HelloWorld::animateEnemy(cocos2d::CCSprite *enemy)
{
	// speed of the enemy
	ccTime actualDuration = 0.3f;

	//rotate to face the player
	CCPoint diff = ccpSub(_player->getPosition(), enemy->getPosition());
	float angleRadians = atanf((float)diff.y / (float)diff.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees;
	if (diff.x < 0) {
		cocosAngle += 180;
	}
	enemy->setRotation(cocosAngle);
	
	CCPoint moveBy = ccpMult(ccpNormalize(ccpSub(_player->getPosition(),enemy->getPosition())), 10);
	
	// Create the actions
	CCFiniteTimeAction *actionMove = CCMoveBy::actionWithDuration(actualDuration, moveBy);
	CCCallFuncN *actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::enemyMoveFinished));
	enemy->runAction(CCSequence::actions(actionMove,
										 actionMoveDone,
										 NULL));
}

void HelloWorld::projectileMoveFinished(CCNode *sprite)
{
	this->removeChild(sprite, true);
	_projectiles->removeObject((cocos2d::CCSprite *)sprite, true);
}

void HelloWorld::testCollisions(ccTime dt)
{
	CCMutableArray<CCSprite*> *projectilesToDelete = new CCMutableArray<CCSprite*>;

	CCMutableArray<CCSprite *>::CCMutableArrayIterator it, jt;
	// iterate through projectiles
	for (it = _projectiles->begin(); it != _projectiles->end(); it++) {
		CCSprite *projectile = *it;
		CCRect projectileRect = CCRectMake(projectile->getPosition().x - (projectile->getContentSize().width/2),
										   projectile->getPosition().y - (projectile->getContentSize().height/2),
										   projectile->getContentSize().width,
										   projectile->getContentSize().height);
		
		CCMutableArray<CCSprite*> *targetsToDelete = new CCMutableArray<CCSprite*>;
		
		// iterate through enemies, see if any intersect with current projectile
		for (jt = _enemies->begin(); jt != _enemies->end(); jt++)
		{
			CCSprite *target = *jt;
			CCRect targetRect = CCRectMake(
										   target->getPosition().x - (target->getContentSize().width/2), 
										   target->getPosition().y - (target->getContentSize().height/2), 
										   target->getContentSize().width, 
										   target->getContentSize().height);
			
			if (CCRect::CCRectIntersectsRect(projectileRect, targetRect)) {
				targetsToDelete->addObject(target);
			}
		}
		
		// delete all hit enemies
		for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++) 
		{
			_enemies->removeObject(*jt);
			this->removeChild((*jt), true);
		}
		
		if (targetsToDelete->count() > 0)
		{
			projectilesToDelete->addObject(projectile);
		}
		
		targetsToDelete->release();
	}
	
	// remove all the projectiles that hit.
	for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++) {
		CCSprite *projectile = *it;
		_projectiles->removeObject(projectile, true);
		this->removeChild(projectile, true);
	}
	
	for (jt = _enemies->begin(); jt != _enemies->end(); jt++)
	{
		CCSprite *target = *jt;
		CCRect targetRect = CCRectMake(
									   target->getPosition().x - (target->getContentSize().width/2), 
									   target->getPosition().y - (target->getContentSize().height/2), 
									   target->getContentSize().width, 
									   target->getContentSize().height);
		
		if (CCRect::CCRectContainsPoint(targetRect, _player->getPosition())) {
			this->lose();
		}
	}
}

void HelloWorld::win()
{
}

void HelloWorld::lose()
{
}