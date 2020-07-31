#include "Player.h"
#include "Asteroid.h"
#include "Hostile.h"
#include "scene.h"
#include <iostream>
#include "projectile.h"
#include "AudioSystem.h"
#include "gamestate.h"



void Player::onCreate() {
	shape = zbe::shape(
		{ zbe::math::vector(0, 15),
		 zbe::math::vector(-7.5f, -7.5f),
		 zbe::math::vector( 0,  0),
		 zbe::math::vector( 7.5f, -7.5f)},
		 zbe::Color(1, 1, 1));

	transform.position = { 300, 400 };
	transform.rotation = 0;
	_collisionRadius = 8;
}

void Player::onUpdate(float dT) {
	wrap();
	zbe::math::vector force = { 0, Core::Input::IsPressed(Core::Input::KEY_UP) };
	force = zbe::math::vector::Rotate(force, transform.rotation);
	dPos += force * 4;
	dPos = zbe::math::vector::Min(zbe::math::vector::Normalise(dPos) * maxSpeed, dPos);
	
	dRot = (Core::Input::IsPressed(Core::Input::KEY_RIGHT) +
		    (Core::Input::IsPressed(Core::Input::KEY_LEFT ) * -1)) * 4;
	


	transform.position += dPos * dT;
	transform.rotation += dRot * dT;
	

	if (Core::Input::IsPressed(Core::Input::KEY_DOWN) && fireDelay <= 0) {
		scene->addActor(new projectile(transform, this));
		g_audio.PlayAudio("laser");
		fireDelay = .65;
	}
	if (fireDelay > 0) {
		fireDelay -= dT;
	}
}

void Player::onCollision(actor* other) {
	if (typeid(*other) == typeid(Asteroid) || typeid(*other) == typeid(Hostile)) {
		Destroy();
	}
}

void Player::onDestroy() {
	g_audio.PlayAudio("lose");
	gamestate = E_Gamestate::LOSE;
}

zbe::math::vector Player::getVelocity()
{
	return dPos;
}

