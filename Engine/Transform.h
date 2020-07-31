#include "vector.h"
#pragma once



namespace zbe {
	namespace math {
		struct transform {
			vector position;
			float scale;
			float rotation;

			transform() : position{ 0,0 }, scale{ 1 }, rotation{ 0 } {}
			transform(const vector position, const float scale = 1, const float rotation = 0) {
				this->position = position;
				this->scale = scale;
				this->rotation = rotation;
			}


		};

	}
}