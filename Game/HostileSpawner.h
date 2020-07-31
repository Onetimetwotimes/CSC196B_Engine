#pragma once
#include "spawner.h"
#include "Hostile.h"

class HostileSpawner : public zbe::spawner {
	void spawn() override {
		int side = zbe::math::Random::getInt(0, 3);
		float a = zbe::math::Random::getFloat(0, side % 2 == 0 ? 600 : 800);
		zbe::math::vector offscreen;
		switch (side) {
		case 0:
			offscreen = { a, -100. };
			break;
		case 1:
			offscreen = { 700., a };
		case 2:
			offscreen = { 900., a };
		case 3:
			offscreen = { -100., a };
		};

		zbe::math::vector onScreen = {
			zbe::math::Random::getInt(100,500),
			zbe::math::Random::getInt(100,700) };


		zbe::math::vector dPos = zbe::math::vector::Normalise(offscreen - onScreen) * (float)zbe::math::Random::getInt(50, 80);
		float dRot = zbe::math::Random::getInt(-3, 3);
		Hostile* o = new Hostile(zbe::math::transform(offscreen), dPos, dRot);

		scene->addActor(o);
	}
};

