#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId GetComponentTypeID() {
	static ComponentId lastId = 0;
	return lastId++;
}

template <typename T> inline ComponentId GetComponentTypeID() noexcept {
	static ComponentId typeId = GetComponentTypeID();
	return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

	virtual ~Component() {};
};

class Entity {
private:
	bool isActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
public:
	void Update() {
		for (auto& c : components)c->Update();
		for (auto& c : components)c->Draw();
	}
	void Draw();
	bool IsActive() { return isActive; };
	void Destroy() { isActive = false; };

	template <typename T> bool HasComponent() const
	{
		return componentBitset[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitset[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& GetComponent() const {
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};


class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
public:
	void Update() {
		for (auto& e : entities) e->Update();
	}
	void Draw() {
		for (auto& e : entities) e->Draw();
	}
	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->IsActive();
			}),
			std::end(entities));
	}

	Entity& AddEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{e};
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
};
