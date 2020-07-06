#include <math.h>
#pragma once

namespace zbe {
	struct vector {
		vector() {
			x = 0;
			y = 0;
		}
		vector(int x, int y) {
			this->x = (float) x;
			this->y = (float) y;
		}
		vector(int p) {
			this->x = (float) p;
			this->y = (float) p;
		}
		vector(float x, float y) {
			this->x = x;
			this->y = y;
		}
		vector(float p) {
			this->x = p;
			this->y = p;
		}


#pragma region Arithmetic

		vector operator	      +(const vector v) const {
			return vector(v.x + x,
						  v.y + y);
		}
		vector operator	      -(const vector v) const {
			return vector(v.x - x,
						  v.y - y);
		}
		vector operator	      *(const vector v) const {
			return vector(v.x * x,
						  v.y * y);
		}					   
		vector operator	      /(const vector v) const {
			return vector(v.x / x,
						  v.y / y);
		}
		vector operator	      +(const float p) const {
			return vector(p + x,
						  p + y);
		}
		vector operator	      -(const float p) const {
			return vector(p - x,
						  p - y);
		}
		vector operator	      *(const float p) const {
			return vector(p * x,
						  p * y);
		}					   
		vector operator	      /(const float p) const {
			return vector(p / x,
						  p / y);
		}

		vector operator+=(const vector& v) {
					 x += v.x;
					 y += v.y;
		}
		vector operator-=(const vector& v) {
					 x -= v.x;
					 y -= v.y;
		}				
		vector operator*=(const vector& v) {
					 x *= v.x;
					 y *= v.y;
		}				
		vector operator/=(const vector& v) {
					 x /= v.x;
					 y /= v.y;
		}
		vector operator+=(const float p) {
					 x += p;
					 y += p;
		}
		vector operator-=(const float p) {
					 x -= p;
					 y -= p;
		}				
		vector operator*=(const float p) {
					 x *= p;
					 y *= p;
		}				
		vector operator/=(const float p) {
					 x /= p;
					 y /= p;
		}

#pragma endregion

		float Length() const {
			return hypot(x, y);
		}

		float Distance(const vector a, const vector b) {
			return (a - b).Length();

		}

		float x, y;
	};
}