#pragma once
#include "EntityComponentSystem.h"
#include <string>
#include "EventBus.h"
#include "ColliderComponent.h"

class HealthComponent : public Component
{
private:
	int health;
	int maxHealth = 100;
	int minHealth = 0;
	bool isDead = false;
	EventBus* eventBus = nullptr;

public:
	HealthComponent() {}

	HealthComponent(int maxHealth, int minHealth, EventBus& bus)
		: maxHealth(maxHealth), minHealth(minHealth), eventBus(&bus)
	{
		SetHealth();
	}

	void Init() override {

		// std::cout << "Health init: " << health << std::endl;
	}
	void Update() override {
		if (!isDead && health <= minHealth) {
			isDead = true;
			OnDeath();
		}

	}
	void Draw() override {

	}

	void ApplyDamage(int amount, const std::string& tagOfSourceOfDamage) {
		if (amount <= 0 || isDead) {
			return;
		}
		this->health -= amount;
		if (this->health < minHealth) {
			this->health = minHealth;
		}
	}

	void Heal(int amount, const std::string& tagOfSourceOfHeal) {

		if (amount <= 0 || isDead) {
			return;
		}
		this->health += amount;
		if (this->health > maxHealth) {
			this->health = maxHealth;
		}
	}

	int GetHealth() const {
		return this->health;
	}
	int GetMaxHealth() const {
		return this->maxHealth;
	}
	int GetMinHealth() const {
		return this->minHealth;
	}

	bool GetIsDead()const {
		return this->isDead;
	}

	void SetHealth() {
		this->health = GetMaxHealth();
	}

	void SetMaxHealth(int amount) {
		this->maxHealth = amount;
		if (health > maxHealth) health = maxHealth;
	}
	void SetMinHealth(int amount) {
		this->minHealth = amount;
		if (health < minHealth) health = minHealth;
	}

	void SetIsDead() {
		if (GetHealth() == GetMinHealth()) {
			this->isDead = true;
		}
		else {
			this->isDead = false;
		}
	}

	void SetEventBus(EventBus& bus) { eventBus = &bus; }

	void OnDeath() {
		std::cout << "Entity: " << this->entity->GetComponent<ColliderComponent>().tag << " has died " << std::endl;

		if (eventBus) {
			eventBus->Publish(DiedEvent{ this->entity });

		}
		this->entity->Destroy();
	}
};

