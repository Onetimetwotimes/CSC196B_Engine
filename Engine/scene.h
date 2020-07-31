#pragma once
#include <vector>
#include "actor.h"
#include <WinBase.h>


namespace zbe {

	class scene {
	public:
		void addActor(actor* actor) {
			actors.push_back(actor);
			actor->setScene(this);
			actor->onCreate();
		}
		void removeActor(actor* actor) {
			actor->Destroy();
		}
		std::vector<actor*> findActors(std::string p_typename) {
			std::vector<actor*> results;
			for (actor* a : actors) {
				if (p_typename.compare(typeid(a).name())) {
					results.push_back(a);
				}
			}

			return results;
		}

		void Close() {
			auto iter = actors.begin();
			while (iter != actors.end()) {
				delete(*iter);
				iter = actors.erase(iter);
			}
		}

		void Update(float dT) {
			std::vector<actor*> _actors = actors; //Copy actors to avoid access violations
			for (actor* actor : _actors) {
				actor->onUpdate(dT);
			}

		

			for (int i = 0; i < _actors.size(); i++) {
				for (int j = 0; j < _actors.size(); j++) {
					float distance = zbe::math::vector::Distance(_actors[i]->getTransform().position, _actors[j]->getTransform().position);
					if (distance <= _actors[i]->collisionRadius() + _actors[j]->collisionRadius()) {
						_actors[i]->onCollision(_actors[j]);
					}
				}
			}

			auto iter = actors.begin();
			while (iter != actors.end()) {
				if ((*iter)->destroy()) {
					delete(*iter);
					iter = actors.erase(iter);
				}
				else
					iter++;
			}
		}
		void Draw(Core::Graphics& g) {
			for (actor* actor : actors) {
				actor->onDraw(g);
			}
		}

		void Init() {
			for (actor* actor : actors) {
				actor->onCreate();
			}
		}
	private:
		std::vector<zbe::actor*> actors;
	};

}


