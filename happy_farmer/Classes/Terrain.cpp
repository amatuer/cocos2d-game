#include "GameConfig.h"
#include "Terrain.h"
#include "Box2d/Box2D.h"
#include "GameConfig.h"

using namespace cocos2d;
#pragma warning(disable:4244)

Terrain* Terrain::terrainWithWorld(b2World* w)
{
	Terrain* t = new Terrain(w);
	if (t) {
		t->autorelease();
		return t;
	}

	return NULL;
}

Terrain::Terrain(b2World* w)
{
	world = w;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	screenW = (int)size.width;
	screenH = (int)size.height;
		
	textureSize = 512;
	stripes_ = this->generateStripesSprite();
	stripes_->setIsVisible(false);
	this->addChild(stripes_);

	this->generateHillKeyPoints();
	this->generateBorderVertices();
	this->createBox2DBody();

	offsetX_ = 0;
}

Terrain::~Terrain()
{
	stripes_ = NULL;
}

CCSprite* Terrain::generateStripesSprite()
{
	CCTexture2D *texture = this->generateStripesTexture();
	CCSprite *sprite = CCSprite::spriteWithTexture(texture);
	ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
	sprite->getTexture()->setTexParameters(&tp);

	return sprite;
}

CCTexture2D* Terrain::generateStripesTexture()
{	
	CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(textureSize, textureSize);

	rt->begin();
	this->renderStripes();
	this->renderGradient();
	this->renderHighlight();
	this->renderTopBorder();
	this->renderNoise();
	rt->end();
	
	return rt->getSprite()->getTexture();
}

void Terrain::renderStripes()
{	
	const int minStripes = 4;
	const int maxStripes = 30;
	
	// random even number of stripes
	int nStripes = rand()%(maxStripes-minStripes)+minStripes;
	if (nStripes%2) {
		nStripes++;
	}
//	NSLog(@"nStripes = %d", nStripes);
	
	GLPoint *vertices = (GLPoint*)malloc(sizeof(GLPoint) * nStripes * 6);
	ccColor4F *colors = (ccColor4F*)malloc(sizeof(ccColor4F) * nStripes * 6);
	int nVertices = 0;
	
	float x1, x2, y1, y2, dx, dy;
	ccColor4F c;
	
	if (rand() % 2) {
		
		// diagonal stripes
		
		dx = (float)textureSize*2 / (float)nStripes;
		dy = 0;
		
		x1 = (float)-textureSize;
		y1 = 0.0f;
		
		x2 = 0.0f;
		y2 = (float)textureSize;
		
		for (int i=0; i<nStripes/2; i++) {
			c = this->randomColor();
			for (int j=0; j<2; j++) {
				for (int k=0; k<6; k++) {
					colors[nVertices+k] = c;
				}
				vertices[nVertices++] = makeGLPoint(x1+j*textureSize, y1);
				vertices[nVertices++] = makeGLPoint(x1+j*textureSize+dx, y1);
				vertices[nVertices++] = makeGLPoint(x2+j*textureSize, y2);
				vertices[nVertices++] = vertices[nVertices-2];
				vertices[nVertices++] = vertices[nVertices-2];
				vertices[nVertices++] = makeGLPoint(x2+j*textureSize+dx, y2);
			}
			x1 += dx;
			x2 += dx;
		}
		
	} else {
		
		// horizontal stripes
		
		dx = 0;
		dy = (float)textureSize / (float)nStripes;
		
		x1 = 0;
		y1 = 0;
		
		x2 = (float)textureSize;
		y2 = 0;
		
		for (int i=0; i<nStripes; i++) {
			c = this->randomColor();
			for (int k=0; k<6; k++) {
				colors[nVertices+k] = c;
			}
			vertices[nVertices++] = makeGLPoint(x1, y1);
			vertices[nVertices++] = makeGLPoint(x2, y2);
			vertices[nVertices++] = makeGLPoint(x1, y1+dy);
			vertices[nVertices++] = vertices[nVertices-2];
			vertices[nVertices++] = vertices[nVertices-2];
			vertices[nVertices++] = makeGLPoint(x2, y2+dy);
			y1 += dy;
			y2 += dy;
		}
		
	}
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glColor4f(1, 1, 1, 1);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
	
	free(vertices);
	free(colors);
}

void Terrain::renderGradient()
{	
	float gradientAlpha = 0.5f;
	float gradientWidth = (float)textureSize;
	
	GLPoint vertices[6];
	ccColor4F colors[6];

	int nVertices = 0;

	vertices[nVertices] = makeGLPoint(0, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = makeGLPoint((float)textureSize, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	
	vertices[nVertices] = makeGLPoint(0, gradientWidth);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
	vertices[nVertices] = makeGLPoint((float)textureSize, (float)gradientWidth);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
	
	if (gradientWidth < textureSize) {
		vertices[nVertices] = makeGLPoint(0, (float)textureSize);
		colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
		vertices[nVertices] = makeGLPoint((float)textureSize, (float)textureSize);
		colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
	}
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
}

void Terrain::renderHighlight()
{	
	float highlightAlpha = 0.5f;
	float highlightWidth = (float)textureSize/4;
	
	GLPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;
	
	vertices[nVertices] = makeGLPoint(0, 0);
	colors[nVertices++] = ccc4f(1.0f, 1.0f, 0.5f, highlightAlpha); // yellow
	vertices[nVertices] = makeGLPoint((float)textureSize, 0);
	colors[nVertices++] = ccc4f(1.0f, 1.0f, 0.5f, highlightAlpha);
	
	vertices[nVertices] = makeGLPoint(0, highlightWidth);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = makeGLPoint((float)textureSize, (float)highlightWidth);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
}

void Terrain::renderTopBorder()
{	
	float borderAlpha = 0.5f;
	float borderWidth = 2.0f;
	
	GLPoint vertices[2];
	int nVertices = 0;
	
	vertices[nVertices++] = makeGLPoint(0, borderWidth/2);
	vertices[nVertices++] = makeGLPoint(textureSize, borderWidth/2);
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	glLineWidth(borderWidth);
	glColor4f(0, 0, 0, borderAlpha);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)nVertices);
}

void Terrain::renderNoise()
{	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	
	CCSprite *s = CCSprite::spriteWithFile("texture/noise.png");

	ccBlendFunc f;
	f.src = GL_DST_COLOR;
	f.dst = GL_ZERO;
	s->setBlendFunc(f);
	s->setPosition(ccp(textureSize/2, textureSize/2));
	s->setScale((float)textureSize/512.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	s->visit();
//	s->visit(); // more contrast
}

void Terrain::generateHillKeyPoints()
{
	nHillKeyPoints = 0;
	
	float x, y, dx, dy, ny;
	
	x = (float)-screenW/4;
	y = (float)screenH*3/4;
	hillKeyPoints[nHillKeyPoints++] = makeGLPoint(x, y);

	// starting point
	x = 0;
	y = (float)screenH/2;
	hillKeyPoints[nHillKeyPoints++] = makeGLPoint(x, y);
	
	int minDX = 160, rangeDX = 80;
	int minDY = 60,  rangeDY = 60;
	float sign = -1.0f; // +1 - going up, -1 - going  down
	float maxHeight = (float)screenH;
	float minHeight = 20;
	while (nHillKeyPoints < kMaxHillKeyPoints-1) {
		dx = float(rand()%rangeDX+minDX);
		x += dx;
		dy = float(rand()%rangeDY+minDY);
		ny = y + dy*sign;
		if(ny > maxHeight) ny = maxHeight;
		if(ny < minHeight) ny = minHeight;
		y = ny;
		sign *= -1;
		hillKeyPoints[nHillKeyPoints++] = makeGLPoint(x, y);
	}

	// cliff
	x += minDX+rangeDX;
	y = 0;
	hillKeyPoints[nHillKeyPoints++] = makeGLPoint(x, y);
	
	fromKeyPointI = 0;
	toKeyPointI = 0;
}

void Terrain::generateBorderVertices()
{
	nBorderVertices = 0;
	GLPoint p0, p1, pt0, pt1;
	p0 = hillKeyPoints[0];
	for (int i=1; i<nHillKeyPoints; i++) {
		p1 = hillKeyPoints[i];
		
		float hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
		float dx = (p1.x - p0.x) / hSegments;
		float da = float(M_PI / hSegments);
		float ymid = (p0.y + p1.y) / 2;
		float ampl = (p0.y - p1.y) / 2;
		pt0 = p0;
		borderVertices[nBorderVertices++] = pt0;
		for (int j=1; j<hSegments+1; j++) {
			pt1.x = p0.x + j*dx;
			pt1.y = ymid + ampl * cosf(da*j);
			borderVertices[nBorderVertices++] = pt1;
			pt0 = pt1;
		}
		
		p0 = p1;
	}
//	NSLog(@"nBorderVertices = %d", nBorderVertices);
}

void Terrain::createBox2DBody()
{
	b2BodyDef bd;
	bd.position.Set(0, 0);
	
	body_ = world->CreateBody(&bd);
	
	b2PolygonShape shape;

	int nVertices = 0;
	b2Vec2 p1, p2;
	for (int i=0; i<nBorderVertices - 1; i++) {
		p1 = b2Vec2(borderVertices[i].x / PTM_RATIO, borderVertices[i].y / PTM_RATIO);
		p2 = b2Vec2(borderVertices[i + 1].x / PTM_RATIO, borderVertices[i + 1].y / PTM_RATIO);
		shape.SetAsEdge(p1, p2);
		body_->CreateFixture(&shape, 0);
	}
}

void Terrain::resetHillVertices()
{
	static int prevFromKeyPointI = -1;
	static int prevToKeyPointI = -1;
	
	// key points interval for drawing
	
	float leftSideX = offsetX_-screenW/8/ getScale();
	float rightSideX = offsetX_+screenW*7/8/ getScale();
	
	while (hillKeyPoints[fromKeyPointI+1].x < leftSideX) {
		fromKeyPointI++;
		if (fromKeyPointI > nHillKeyPoints-1) {
			fromKeyPointI = nHillKeyPoints-1;
			break;
		}
	}
	while (hillKeyPoints[toKeyPointI].x < rightSideX) {
		toKeyPointI++;
		if (toKeyPointI > nHillKeyPoints-1) {
			toKeyPointI = nHillKeyPoints-1;
			break;
		}
	}
	
	if (prevFromKeyPointI != fromKeyPointI || prevToKeyPointI != toKeyPointI) {
		
//		NSLog(@"building hillVertices array for the visible area");

//		NSLog(@"leftSideX = %f", leftSideX);
//		NSLog(@"rightSideX = %f", rightSideX);
		
//		NSLog(@"fromKeyPointI = %d (x = %f)",fromKeyPointI,hillKeyPoints[fromKeyPointI].x);
//		NSLog(@"toKeyPointI = %d (x = %f)",toKeyPointI,hillKeyPoints[toKeyPointI].x);
		
		// vertices for visible area
		nHillVertices = 0;
		GLPoint p0, p1, pt0, pt1;
		p0 = hillKeyPoints[fromKeyPointI];
		for (int i=fromKeyPointI+1; i<toKeyPointI+1; i++) {
			p1 = hillKeyPoints[i];
			
			// triangle strip between p0 and p1
			float hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
			int vSegments = 1;
			float dx = (p1.x - p0.x) / hSegments;
			float da = float(M_PI / hSegments);
			float ymid = (p0.y + p1.y) / 2;
			float ampl = (p0.y - p1.y) / 2;
			pt0 = p0;
			for (int j=1; j<hSegments+1; j++) {
				pt1.x = p0.x + j*dx;
				pt1.y = ymid + ampl * cosf(da*j);
				for (int k=0; k<vSegments+1; k++) {
					hillVertices[nHillVertices] = makeGLPoint(pt0.x, pt0.y-(float)textureSize/vSegments*k);
					hillTexCoords[nHillVertices++] = makeGLPoint(pt0.x/(float)textureSize, (float)(k)/vSegments);
					hillVertices[nHillVertices] = makeGLPoint(pt1.x, pt1.y-(float)textureSize/vSegments*k);
					hillTexCoords[nHillVertices++] = makeGLPoint(pt1.x/(float)textureSize, (float)(k)/vSegments);
				}
				pt0 = pt1;
			}
			
			p0 = p1;
		}
		
//		NSLog(@"nHillVertices = %d", nHillVertices);
		
		prevFromKeyPointI = fromKeyPointI;
		prevToKeyPointI = toKeyPointI;
	}
}

ccColor4F Terrain::randomColor()
{
	const int minSum = 450;
	const int minDelta = 150;
	int r, g, b, min, max;
	while (true) {
		r = rand()%256;
		g = rand()%256;
		b = rand()%256;
		min = MIN(MIN(r, g), b);
		max = MAX(MAX(r, g), b);
		if (max-min < minDelta) continue;
		if (r+g+b < minSum) continue;
		break;
	}

	return ccc4FFromccc3B(ccc3(r, g, b));
}

void Terrain::draw()
{
	CCTexture2D* texture = stripes_->getTexture();
	glBindTexture(GL_TEXTURE_2D, texture->getName());
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	glColor4f(1, 1, 1, 1);
	glVertexPointer(2, GL_FLOAT, 0, hillVertices);
	glTexCoordPointer(2, GL_FLOAT, 0, hillTexCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nHillVertices);
	
	glEnableClientState(GL_COLOR_ARRAY);

#ifdef DRAW_BOX2D_WORLD

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	world->DrawDebugData();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
#endif	
}

void Terrain::setOffsetX(float offsetX)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	offsetX_ = offsetX;
	setPosition(ccp(winSize.width / 8 - offsetX_ * getScale(), 0));
	this->resetHillVertices();
}

void Terrain::reset()
{
	stripes_->removeFromParentAndCleanup(true);
	stripes_ = this->generateStripesSprite();
	this->addChild(stripes_);
	stripes_->setIsVisible(false);

	fromKeyPointI = 0;
	toKeyPointI = 0;
}
