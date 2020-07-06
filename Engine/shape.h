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
				g.DrawLine(m_points[i].x    + pos.x, m_points[i].y +           pos.y,
					m_points[(i + 1) % s].x + pos.x, m_points[(i + 1) % s].y + pos.y);
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