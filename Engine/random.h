#include <time.h>
#include <stdlib.h>
#pragma once

namespace zbe {
	namespace math {
		struct Random {
			//returns an integer between min and max inclusive
			static int getInt(int min, int max) {
				if (min == max) {
					return max;
				}
				return (rand() % (max - min)) + min;
			}

			//Returns a floating point integer between 0 and 1 inclusive
			static float getFloat() {
				return (float)rand() / (float) RAND_MAX;
			}

			//Returns a floating point integer between min and max inclusive
			static float getFloat(float min, float max) {
				return ((float)rand() / (float) RAND_MAX) * (max - min) + min;
			}

			static int next() {
				return (rand());
			}

			static void setSeed(unsigned int seed = time(NULL)) {
				srand(seed);
			}
		};
	}
}