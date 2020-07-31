#pragma once
#include <actor.h>
#include "random.h"

class Hostile :
	public zbe::actor {
public:
	Hostile(zbe::math::transform t, zbe::math::vector dP, float dR) {
		transform = t;
		dPos = dP;
		dRot = dR;
		_collisionRadius = 15;
	}
	void onCreate() override;
	void onUpdate(float dT) override;
	void onDestroy() override;
	void onDraw(Core::Graphics& g) override;

private:

	zbe::shape shape_a;
	zbe::shape shape_b = zbe::shape({
		zbe::math::vector( 10, 10),
		zbe::math::vector(-10, 10),
		zbe::math::vector(-10,-10),
		zbe::math::vector( 10,-10)},
		zbe::Color(1, 1, 1));
	zbe::shape shape_c = zbe::shape({ zbe::math::vector(0, 5),
		 zbe::math::vector(-5, -5),
		 zbe::math::vector(0,  0),
		 zbe::math::vector(5, -5) },
		zbe::Color(1, 0, 0));

	zbe::math::vector dPos = 0;
	float dRot = 0;
	float gRot = 0;
	float fireDelay = 1;
	bool onScreen = false;
};

