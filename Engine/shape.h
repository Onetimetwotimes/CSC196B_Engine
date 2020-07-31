#pragma once
#include <vector>
#include "vector.h"
#include "color.h"
#include "transform.h"

namespace zbe {
	class shape {
	public:
		shape() {

		}

		shape(const std::vector<zbe::math::vector>& points, const Color& color) {
			m_points = points;
			m_color = color;
		}

	

		void Draw(Core::Graphics& g, zbe::math::transform t) {
			Draw(g, t.position, t.scale, t.rotation);
		}

		void Draw(Core::Graphics& g, zbe::math::vector pos, float scale = 1.0f, float rot = 0.0f) {
			g.SetColor(m_color);

			int s = m_points.size();
			std::vector<zbe::math::vector> g_points = std::vector<zbe::math::vector>(m_points);
			
			for (int i = 0; i < s; i++) {
				g_points[i] *= scale;
				g_points[i] = zbe::math::vector::Rotate(g_points[i], rot);
				g_points[i] += pos;
			}

			for (int i = 0; i < s; i++) {

				zbe::math::vector g_a = g_points[i];
				zbe::math::vector g_b = g_points[(i + 1) % s];
				g.DrawLine(g_a.x, g_a.y,
						   g_b.x, g_b.y);
			}
			g.SetColor(zbe::Color(1, 1, 1));
		}

		void setColor(const Color color) {
			m_color = color;
		}

		const Color& getColor() const {
			return m_color;
		}
#pragma region IO
		/*
		std::ifstream& read(std::ifstream& in) {

		}

		std::ofstream& write(std::ofstream& out) {
			for (zbe::math::vector v : m_points) {
				v.write(out);
				out << '\n';
			}
		}
		std::ofstream& operator<<(std::ofstream& out) {
			write(out);
			return out;
		}*/
#pragma endregion

	

	private:
		std::vector<zbe::math::vector> m_points;
		Color m_color;
	};
}