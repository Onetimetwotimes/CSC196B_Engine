#include "projectile.h"
#include "scene.h"
#include "Asteroid.h"
#include "Hostile.h"
#include "Player.h"

void projectile::onCreate() {
	shape = zbe::shape({ zbe::math::vector(0,-3), zbe::math::vector(0,3) }, zbe::Color(1, friendly, friendly));
	_collisionRadius = 3;
}

void projectile::onUpdate(float dT) {
	wrap();
	lifetime -= dT;

	transform.position += direction * speed * dT;


	if (lifetime < 0)
		Destroy();
}

void projectile::onCollision(actor* other) {
	if (other == creator)
		return;
	if (typeid(*other) == typeid(Asteroid) || typeid(*other) == typeid(Hostile)) {
		other->Destroy();
		Destroy();
	}
	if (typeid(*other) == typeid(Player) && !friendly) {
		other->Destroy();
		Destroy();
	}
}
