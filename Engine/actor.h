#pragma once
#include "Transform.h"
#include "shape.h"

namespace zbe {
	class scene;

	class actor {
	
	public:

		virtual void onUpdate(float dT) = 0;

		virtual void onDraw(Core::Graphics& g) {
			shape.Draw(g, transform.position, transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(-600,0), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(600,0), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(0,-800), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(0,800), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(-600,800), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(600,-800), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(-600,-800), transform.scale, transform.rotation);
			shape.Draw(g, transform.position + zbe::math::vector(600,800), transform.scale, transform.rotation);
		}

		virtual void onCreate() = 0;

		void setScene(scene* scene) {
			this->scene = scene;
		}

		zbe::math::transform getTransform() {
			return transform;
		}

		float collisionRadius() {
			return _collisionRadius * transform.scale;
		}

		virtual void onCollision(actor* other) {};

		virtual void onDestroy() {};

		void Destroy() {
			onDestroy();
			_destroy = true;
		};

		bool destroy() { return _destroy; }
	protected:
		void wrap() {
			if (transform.position.x > 600)
				transform.position.x = 1;
			if (transform.position.x < 0)
				transform.position.x = 599;
			if (transform.position.y > 800)
				transform.position.y = 1;
			if (transform.position.y < 0)
				transform.position.y = 799;
		}


		float _collisionRadius = 0;
		zbe::math::transform transform;
		zbe::shape shape;
		scene* scene = nullptr;
		bool _destroy = false;
	};
}

