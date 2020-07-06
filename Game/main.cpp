#include "core.h"
#include "vector.h"
#include "shape.h"
#include "globals.h"


float timescale = 1;
float t = 0;

float r, g, b = 0;

zbe::Shape s = zbe::Shape(
	{ zbe::vector(0, 10),
	 zbe::vector(-5, -5),
	 zbe::vector(5, -5) },
	zbe::Color(0,0,0));

bool Update(float dt) {
	dt *= timescale;
	t += dt;
	if (t < 1) {
		r = 0;
		g = 0;
		b = 0;
	} else if (t < 2) {
		r = .5;
	} else if (t < 3) {
		r = 1;
	} else if (t < 4) {
		r = 0;
		g = .5;
	} else if (t < 5) {
		g = 1;
	} else if (t < 6) {
		g = 0;
		b = .5;
	} else if (t < 7) {
		b = 1;
	} else if (t < 8) {
		r = 1;
		g = 1;
		b = 1;
	}
	else {
		t = 0;
	}
	s.setColor(zbe::Color(r, g, b));
	return false;

}

void Draw(Core::Graphics& graphics) {
	s.Draw(graphics, zbe::vector(200, 200));
}


int main() {
	char name[] = "Victor Antonio - Graphics";


	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}