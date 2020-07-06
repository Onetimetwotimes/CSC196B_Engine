#include <vector>
#include "vector.h"
#include "color.h"

#pragma once
namespace zbe {
	class Shape {
	public:
		Shape() {

		}

		Shape(const std::vector<zbe::vector>& points, const Color& color) {
			m_points = points;
			m_color = color;
		}

		void Draw(Core::Graphics& g, zbe::vector pos, float scale = 1.0f, float rot = 0.0f) {
			g.SetColor(m_color);

			int s = m_points.size();

			for (int i = 0; i < s; i++) {
				zbe::vector g_a = m_points[i] + pos;
				zbe::vector g_b = m_points[(i + 1) % s];
				g.DrawLine(g_a.x, g_a.y,
						   g_b.x, g_b.y);
			}
		}

		void setColor(const Color color) {
			m_color = color;
		}

		const Color& getColor() const {
			return m_color;
		}

	private:
		std::vector<zbe::vector> m_points;
		Color m_color;
	};
}