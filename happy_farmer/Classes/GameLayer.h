#include "cocos2d.h"

class Sky;
class Terrain;
class Hero;
class GLESDebugDraw;
class b2World;

class GameLayer : public cocos2d::CCLayer {
public:
	GameLayer();
	~GameLayer();

	static cocos2d::CCScene* scene();
	SCENE_NODE_FUNC(GameLayer);

	void showPerfectSlide();
	void showFrenzy();
	void showHit();

	int getWidth() const;
	int getHeight() const;

	b2World* getB2World() const;

	bool ccTouchBegan(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event);
private:
	int screenW_;
	int screenH_;
	b2World *world_;
	Sky *sky_;
	Terrain *terrain_;
	Hero *hero_;
	GLESDebugDraw *render_;
	cocos2d::CCSprite * resetButton_;

	void createBox2DWorld();
	void reset();
	void registerWithTouchDispatcher();
	void removeLabel(cocos2d::CCNode* node, void* data);
	void update(cocos2d::ccTime dt);
};

