#pragma once
#include "EntityComponentSystem.h"
#include <string>

class HealthComponent : public Component
{
private:
	int health;
	int maxHealth = 100;
	int minHealth = 0;
	bool isDead = false;

public:
	HealthComponent() {}

	HealthComponent(int maxHealth, int minHealth) {
		SetMaxHealth(maxHealth);
		SetMinHealth(minHealth);
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
	void OnDeath() {
		std::cout << "entity is dead" << std::endl;
		this->entity->Destroy();
	}
};

