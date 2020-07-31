#include <stdexcept>
#include "core.h"
#include "input.h"
#pragma once

namespace zbe {
	struct Color {
		~Color() {

		}

		float r, g, b;

		Color() {
			r = 0;
			g = 0;
			b = 0;
		}

		Color(float r, float g, float b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}


		void SetRGB(float r, float g, float b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

#pragma region Array Accessors

		float& operator[](size_t index) {
			switch (index) {
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			default:
				throw std::out_of_range("Max index: 2");
			}
		}
		const float& operator[](size_t index) const {
			switch (index) {
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			default:
				throw std::out_of_range("Max index: 2");
			}
		}
#pragma endregion

#pragma region Arithmetic
		Color operator+(const Color& c) const {
			return Color(
				r + c.r,
				g + c.g,
				b + c.b);
		}
		Color operator-(const Color& c) const {
			return Color(
				r - c.r,
				g - c.g,
				b - c.b);
		}
		Color operator*(const Color& c) const {
			return Color(
				r * c.r,
				g * c.g,
				b * c.b);
		}
		Color operator/(const Color& c) const {
			return Color(
				r / c.r,
				g / c.g,
				b / c.b);
		}
		Color operator+(const float s) const {
			return Color(
				r + s,
				g + s,
				b + s);
		}
		Color operator-(const float s) const {
			return Color(
				r - s,
				g - s,
				b - s);
		}
		Color operator*(const float s) const {
			return Color(
				r * s,
				g * s,
				b * s);
		}
		Color operator/(const float s) const {
			return Color(
				r / s,
				g / s,
				b / s);
		}

		Color operator+=(const Color c) {
			r += c.r;
			g += c.g;
			b += c.b;

			return *this;
		}
		Color operator-=(const Color c) {
			r -= c.r;
			g -= c.g;
			b -= c.b;

			return *this;
		}
		Color operator*=(const Color c) {
			r *= c.r;
			g *= c.g;
			b *= c.b;

			return *this;
		}
		Color operator/=(const Color c) {
			r /= c.r;
			g /= c.g;
			b /= c.b;

			return *this;
		}

#pragma endregion


#pragma region IO
		/*
		std::ifstream& read(std::ifstream& in) {
			std::string data = zbe::input::getLine(in);
			r = zbe::input::getInt(data, ',');
			g = zbe::input::getInt(data, ',');
			b = zbe::input::getInt(data, '}');
			return in;
		}

		std::ofstream& write(std::ofstream& out) {
			
			out << "{"
				<< r << ", "
				<< g << ", "
				<< b << "}"
				<< "\n";
			return out;
		}
		*/
#pragma endregion




		COLORREF pack888() const {

			int r_ = (int) floorf(r * 255.0f);
			int g_ = (int) floorf(g * 255.0f);
			int b_ = (int) floorf(b * 255.0f);

			return ((COLORREF)(((BYTE)(r_) | ((WORD)((BYTE)(g_)) << 8)) | (((DWORD)(BYTE)(b_)) << 16)));
		}
		operator COLORREF() const {

			int r_ = (int) floor((double)r * 255);
			int g_ = (int) floor((double)g * 255);
			int b_ = (int) floor((double)b * 255);

			return ((COLORREF)(((BYTE)(r_) | ((WORD)((BYTE)(g_)) << 8)) | (((DWORD)(BYTE)(b_)) << 16)));
		}
	};



}