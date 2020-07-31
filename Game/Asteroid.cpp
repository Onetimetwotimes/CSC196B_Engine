#include "Asteroid.h"
#include "scene.h"
#include "AudioSystem.h"
#include "constants.h"
#include "scoreboard.h"
#include <vector>

void Asteroid::onCreate() {
	shape = zbe::shape(
		
		{	
		//Quadrant 1	
					zbe::math::vector(
			zbe::math::Random::getFloat(30,40),
			zbe::math::Random::getFloat(20,30)),
		  zbe::math::vector(
			zbe::math::Random::getFloat(20,30),
			zbe::math::Random::getFloat(30,40)),
		//Quadrant 2
		  			zbe::math::vector(
			zbe::math::Random::getFloat(-30,-40),
			zbe::math::Random::getFloat(40,50)),
		  zbe::math::vector(
			zbe::math::Random::getFloat(-40,-50),
			zbe::math::Random::getFloat(20,30)), 
		//Quadrant 3
		zbe::math::vector(
			zbe::math::Random::getFloat(-30,-40),
			zbe::math::Random::getFloat(-20,-30)),
		zbe::math::vector(				
			zbe::math::Random::getFloat(-20,-30),
			zbe::math::Random::getFloat(-30,-40)),
		//Quadrant 4
		  zbe::math::vector(
			zbe::math::Random::getFloat(20,30),
			zbe::math::Random::getFloat(-30,-40)),
		zbe::math::vector(
			zbe::math::Random::getFloat(30,40),
			zbe::math::Random::getFloat(-20,-30)),


		}, zbe::Color(1, 1, 1));

}

void Asteroid::onUpdate(float dT) {
	if (!onScreen) {
		 onScreen = transform.position.x < 550 && transform.position.x > 50
			     && transform.position.y < 750 && transform.position.y > 50;
	} else wrap();

	transform.position += dPos * dT;
	transform.rotation += dRot * dT;
}



void Asteroid::onDraw(Core::Graphics& g) {
	if (onScreen)
		actor::onDraw(g);
	else
		shape.Draw(g,transform);
}

void Asteroid::onDestroy() {
	if (transform.scale < .5) {
		g_audio.PlayAudio("small_break");
		sb.gameScore += 1;
	}
	else {
		g_audio.PlayAudio("break");
		sb.gameScore += transform.scale < 1 ? 5 : 10;

		const int breaks = zbe::math::Random::getInt(2, 4);
		zbe::math::transform new_transform =
			zbe::math::transform(
				transform.position,
				transform.scale * .5,
				transform.rotation);

		for (int i = 0; i < breaks; i++) {

			Asteroid* a = new Asteroid(
				new_transform,
				zbe::math::vector::Rotate(
					{ 0, 1 },
					zbe::math::Random::getFloat(0, zbe::math::TWO_PI)) * zbe::math::Random::getFloat(20,80),
				zbe::math::Random::getFloat(-3,3));
			scene->addActor(a);
		}
	}


}
