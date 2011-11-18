#pragma once
#include "cocos2d.h"

#define kMaxHillKeyPoints 101
#define kMaxHillVertices 1000
#define kMaxBorderVertices 5000
#define kHillSegmentWidth 15

class b2World;
class b2Body;

struct GLPoint {
	float x;
	float y;
};

inline GLPoint makeGLPoint(float x, float y)
{
	GLPoint pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

class Terrain : public cocos2d::CCNode {
public:
	static Terrain* terrainWithWorld(b2World* w);
	Terrain(b2World* w);
	~Terrain();

	void reset();
	void draw();
	void setOffsetX(float offsetX);
private:
	GLPoint hillKeyPoints[kMaxHillKeyPoints];
	int nHillKeyPoints;
	int fromKeyPointI;
	int toKeyPointI;
	GLPoint hillVertices[kMaxHillVertices];
	GLPoint hillTexCoords[kMaxHillVertices];
	int nHillVertices;
	GLPoint borderVertices[kMaxBorderVertices];
	int nBorderVertices;
	cocos2d::CCSprite *stripes_;
	float offsetX_;
	b2World *world;
	b2Body *body_;
	int screenW;
	int screenH;
	int textureSize;

	cocos2d::CCSprite* generateStripesSprite();
	cocos2d::CCTexture2D* generateStripesTexture();
	void renderStripes();
	void renderGradient();
	void renderHighlight();
	void renderTopBorder();
	void renderNoise();
	void generateHillKeyPoints();
	void generateBorderVertices();
	void createBox2DBody();
	void resetHillVertices();
	cocos2d::ccColor4F randomColor();
};