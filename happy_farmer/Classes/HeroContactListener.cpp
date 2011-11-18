#include "GameConfig.h"
#include "HeroContactListener.h"
#include "Hero.h"

HeroContactListener::HeroContactListener(Hero* hero) {
	hero_ = hero;
}

HeroContactListener::~HeroContactListener() {
}

void HeroContactListener::BeginContact(b2Contact* contact) {}

void HeroContactListener::EndContact(b2Contact* contact) {}

void HeroContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	b2WorldManifold wm;
	contact->GetWorldManifold(&wm);
	b2PointState state1[2], state2[2];
	b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());
	if (state2[0] == b2_addState) {
		const b2Body *b = contact->GetFixtureB()->GetBody();
		b2Vec2 vel = b->GetLinearVelocity();
		float va = atan2f(vel.y, vel.x);
		float na = atan2f(wm.normal.y, wm.normal.x);
//		NSLog(@"na = %.3f",na);
		if (na - va > kMaxAngleDiff) {
			hero_->hit();
		}
	}
}

void HeroContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
