#include <cmath>
#include <fstream>
#include "input.h"
#pragma once

namespace zbe {
	namespace math {

		struct vector {
			vector() {
				x = 0;
				y = 0;
			}
			vector(int x, int y) {
				this->x = (float)x;
				this->y = (float)y;
			}
			vector(int p) {
				this->x = (float)p;
				this->y = (float)p;
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

			vector operator+(const vector v) const {
				return vector(v.x + x,
					          v.y + y);
			}
			vector operator-(const vector v) const {
				return vector(v.x - x,
					          v.y - y);
			}
			vector operator*(const vector v) const {
				return vector(v.x * x,
					          v.y * y);
			}
			vector operator/(const vector v) const {
				return vector(v.x / x,
					          v.y / y);
			}
			vector operator+(const float p) const {
				return vector(p + x,
					          p + y);
			}
			vector operator-(const float p) const {
				return vector(p - x,
					          p - y);
			}
			vector operator*(const float p) const {
				return vector(p * x,
					          p * y);
			}
			vector operator/(const float p) const {
				return vector(x / p,
					          y / p);
			}

			vector operator+=(const vector& v) {
				x += v.x;
				y += v.y;
				return *this;
			}
			vector operator-=(const vector& v) {
				x -= v.x;
				y -= v.y;
				return *this;
			}
			vector operator*=(const vector& v) {
				x *= v.x;
				y *= v.y;
				return *this;
			}
			vector operator/=(const vector& v) {
				x /= v.x;
				y /= v.y;
				return *this;
			}
			vector operator+=(const float p) {
				x += p;
				y += p;
				return *this;
			}
			vector operator-=(const float p) {
				x -= p;
				y -= p;
				return *this;
			}
			vector operator*=(const float p) {
				x *= p;
				y *= p;
				return *this;
			}
			vector operator/=(const float p) {
				x /= p;
				y /= p;
				return *this;
			}

#pragma endregion

#pragma region Comparison
			bool operator<(vector o) {
				return Length() < o.Length();
			}
			bool operator>(vector o) {
				return Length() > o.Length();
			}
			bool operator==(vector o) {
				return Length() == o.Length();
			}
#pragma endregion

			float Length() const {
				return hypot(x, y);
			}

			static float Distance(const vector a, const vector b) {
				return (a - b).Length();

			}

			static vector Normalise(const vector& v) {
				return vector(v / v.Length());
			}
				 
			static vector Rotate(const vector& v, float rad) {
				return vector(
					v.x * std::cosf(rad) - v.y * sinf(rad),
					v.x * sinf(rad) + v.y * cosf(rad)
				);
			}

			float rotation() {
				vector normal = vector::Normalise(*this);
				return std::atan2(normal.y, normal.x);
			}

			static vector Min(const vector& a, const vector& b) {
				return vector(a.Length() < b.Length() ? a : b);
			}
			static vector Max(const vector& a, const vector& b) {
				return vector(a.Length() > b.Length() ? a : b);
			}

#pragma region IO
			/*
			std::ifstream& read(std::ifstream& in) {
				zbe::input::getLine(in);

				std::string data = zbe::input::getLine(in);
				x = zbe::input::getInt(data, ',');
				y = zbe::input::getInt(data, '}');
			}

			std::ofstream& write(std::ofstream& out) {
				out << "{"
					<< x << ", "
					<< y << "}"
					<< "\n";
			}
			*/
#pragma endregion



			float x, y;
		};
	}
}