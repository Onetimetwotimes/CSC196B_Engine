#include "Hostile.h"
#include "scene.h"
#include "Player.h"
#include "projectile.h"
#include "constants.h"
#include "scoreboard.h"
#include "AudioSystem.h"
#include <algorithm>

void Hostile::onCreate() {
	shape_a = zbe::shape(
		{
			//Quadrant 1	
			zbe::math::vector(
				zbe::math::Random::getFloat(15,18),
				zbe::math::Random::getFloat(12,15)),
			zbe::math::vector(
				zbe::math::Random::getFloat(12,15),
				zbe::math::Random::getFloat(15,18)),
		//Quadrant 2
			zbe::math::vector(
				zbe::math::Random::getFloat(-12,-15),
				zbe::math::Random::getFloat(15,18)),
			zbe::math::vector(
				zbe::math::Random::getFloat(-15,-18),
				zbe::math::Random::getFloat(12,15)),
		//Quadrant 3
			zbe::math::vector(
				zbe::math::Random::getFloat(-15,-18),
				zbe::math::Random::getFloat(-12,-15)),
			zbe::math::vector(
				zbe::math::Random::getFloat(-12,-15),
				zbe::math::Random::getFloat(-15,-18)),
		//Quadrant 4
			zbe::math::vector(
				zbe::math::Random::getFloat(12,15),
				zbe::math::Random::getFloat(-15,-18)),
			zbe::math::vector(
				zbe::math::Random::getFloat(15,18),
				zbe::math::Random::getFloat(-12,-15)),
		},	zbe::Color(1, 1, 1));
}

void Hostile::onUpdate(float dT) {
	Player* player = nullptr;
	player = static_cast<Player*>(scene->findActors(typeid(Player).name())[0]);
	zbe::math::vector pPosition = player->getTransform().position;


	std::vector<zbe::math::vector> virtualPositions
	{
		 pPosition,
		{pPosition.x - 600, pPosition.y + 000},
		{pPosition.x + 600, pPosition.y + 000},
		{pPosition.x + 000, pPosition.y - 800},
		{pPosition.x + 000, pPosition.y - 800},
		{pPosition.x - 600, pPosition.y + 800},
		{pPosition.x + 600, pPosition.y - 800},
		{pPosition.x - 600, pPosition.y - 800},
		{pPosition.x + 600, pPosition.y + 800}
	};

	std::sort(virtualPositions.begin(), virtualPositions.end());
	pPosition = virtualPositions.front() + (player->getVelocity() * zbe::math::vector::Distance(transform.position, pPosition) * .005);
	gRot = (transform.position - pPosition).rotation() - (zbe::math::PI / 2.);

	if (fireDelay < 0) {
		projectile* p = new projectile(zbe::math::transform(transform.position, 1, gRot), this, false);
		scene->addActor(p);
		fireDelay = 2.325;
	}
	else
		fireDelay -= dT;

	if (!onScreen) {
		onScreen = transform.position.x < 550 && transform.position.x > 50
			&& transform.position.y < 750 && transform.position.y > 50;
	}
	else wrap();

	transform.position += dPos * dT;
	transform.rotation += dRot * dT;

}

void Hostile::onDestroy() {
	g_audio.PlayAudio("break");
	sb.gameScore += 20;
}

void Hostile::onDraw(Core::Graphics& g) {
	if (onScreen) {
		shape = shape_a;
		actor::onDraw(g);

		shape = shape_b;
		actor::onDraw(g);

		float rot = transform.rotation;
		transform.rotation = gRot;

		shape = shape_c;
		actor::onDraw(g);

		transform.rotation = rot;
	}
	else {
		shape_a.Draw(g, transform);
		shape_b.Draw(g, transform);
		shape_c.Draw(g, transform);
	}

}
