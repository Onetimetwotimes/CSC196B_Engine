#pragma once
#include <actor.h>
class projectile :	public zbe::actor {
public:
	projectile(zbe::math::transform transform, actor* creator, bool friendly = true) {
		this->transform = transform;
		this->direction = zbe::math::vector::Rotate({0,1}, transform.rotation);
		this->friendly = friendly;
		this->creator = creator;
	}

	void onCreate() override;
	void onUpdate(float dT) override;
	void onCollision(actor* other) override;

	bool isFriendly() {
		return friendly;
	}

private:
	actor* creator = nullptr;
	bool friendly = true;
	float lifetime = 4;
	float speed = 180;
	zbe::math::vector direction = 0;
};

