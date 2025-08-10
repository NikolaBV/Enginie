#include "EntityComponentSystem.h"

void Entity::Draw() {
	for (auto& c : components) c->Draw();
}
