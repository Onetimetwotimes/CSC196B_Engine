#pragma once
#include "actor.h"
#include "random.h"

class Asteroid :
	public zbe::actor {
public:
	Asteroid() {};
	Asteroid(zbe::math::transform t, zbe::math::vector _dPos, float _dRot) {
		transform = t;
		dPos = _dPos;
		dRot = _dRot;
		_collisionRadius = 40;
	}
	void onCreate() override;
	void onUpdate(float dT) override;
	

	void onDraw(Core::Graphics& g) override;
	void onDestroy() override;

private:

	zbe::math::vector dPos = 0;
	float dRot = 0;
	bool onScreen = false;
	

	
};

