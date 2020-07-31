#pragma once
#include "actor.h"

class Player :
	public zbe::actor {
public:

	void onCreate() override;
	void onUpdate(float dT) override;
	void onCollision(actor* other) override;

	void onDestroy() override;
	
	zbe::math::vector getVelocity();

private:
	zbe::math::vector dPos = 0;
	float dRot = 0;
	float maxSpeed = 180;
	float fireDelay = 0;
};

