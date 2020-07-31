#pragma once
#include "scene.h"
#include "random.h"
#include "vector.h"

namespace zbe {
	class spawner {
	public:
		virtual void Update(float dT) {
			if (timer > 0)
				timer -= dT;
			else {
				spawn();
				timer = zbe::math::Random::getInt(5, 10);
			}
		};

		virtual void Init(zbe::scene* _scene, int initialSpawns = 3, float _delayMin = 5, float _delayMax = 10) {
			scene = _scene;
			delayMin = _delayMin;
			delayMax = _delayMax;
			timer = zbe::math::Random::getFloat(delayMin, delayMax);
			for (int i = 0; i < initialSpawns; i++) {
				spawn();
			}
		}
	
	protected:
		virtual void spawn() = 0;


		float delayMin;
		float delayMax;
		float timer = 0;
		zbe::scene* scene;
	};


}