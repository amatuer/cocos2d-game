#include "GameConfig.h"

#include "TerrainLayer.h"
#include "../GameCommon/Button.h"
#include "../GameCommon/GuiMgr.h"
#include <boost/lexical_cast.hpp>

using namespace cocos2d;
#define kXMinStep 160.0f
#define kYMinStep 60.0f
#define kXStepRange 80
#define kYStepRange 40

#define kTopPadding 20.0f
#define kButtomPadding 20.0f

#define kHillSegmentWidth 10.0f

bool TerrainLayer::init()
{
	CCLayer::init();

	m_fromKeyPointIndex = 0;
	m_toKeyPointIndex = 0;
	m_offsetX = 0;

	genHillKeyPoints(500);
	resetHillVertices();
	return true;
}

void TerrainLayer::menuCallbackStage(CCObject* pSender)
{
}

void TerrainLayer::setOffsetX(int offsetX)
{
	if (m_offsetX == offsetX) {
		return;
	}

	m_offsetX = offsetX;

	setPosition(ccp(-m_offsetX * getScale(), 0));
	resetHillVertices();
}

void TerrainLayer::genHillKeyPoints(int maxNumber)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float x = -kXMinStep;
	float y = winSize.height / 2 - kYMinStep;
	int flag = 1;

	for (int i = 0; i < maxNumber; ++i) {
		m_hillKeyPoints.push_back(ccp(x, y));

		if (i == 0) {
			x = 0;
			y = winSize.height / 2;
		} else {
			x += kXMinStep + rand()% kXStepRange;
			float dy = 0.0f;
			while (true) {
				dy = y + (kYMinStep + rand() % kYStepRange) * flag;
				if (dy < winSize.height - kTopPadding && dy > kButtomPadding) {
					break;
				}
			}
			y = dy;
		}

		flag = -flag;
	}
}

void TerrainLayer::draw()
{
	int amount = m_hillKeyPoints.size();
	for (int i = __max(m_fromKeyPointIndex, 1); i <= __min(m_toKeyPointIndex, amount); ++i) {
		glColor4f(1.0f, 0, 0, 1.0f);

		CCPoint p0 = m_hillKeyPoints[i - 1];
		CCPoint p1 = m_hillKeyPoints[i];
		ccDrawLine(p0, p1);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		int hSegments = (int)floorf((p1.x - p0.x) / kHillSegmentWidth);
		float dx = (p1.x - p0.x) / hSegments;
		float da = (float)M_PI / hSegments;
		float ymid = (p0.y + p1.y) / 2;
		float ampl = (p0.y - p1.y) / 2;

		CCPoint pt0, pt1;
		pt0 = p0;
		for (int j = 0; j < hSegments + 1; ++j) {
			pt1.x = p0.x + j * dx;
			pt1.y = ymid + ampl * cosf(da * j);
			ccDrawLine(pt0, pt1);
			pt0 = pt1;
		}
	}
}

void TerrainLayer::resetHillVertices()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	static int prevFromKeyPointIndex = -1;
	static int preToKeyPointIndex = -1;

	while (m_hillKeyPoints[m_fromKeyPointIndex + 1].x < m_offsetX - winSize.width / 8 / getScale()) {
		++m_fromKeyPointIndex;
	}

	while (m_hillKeyPoints[m_toKeyPointIndex + 1].x < m_offsetX + winSize.width * 3 / 2 / getScale()) {
		++m_toKeyPointIndex;
	}
}
