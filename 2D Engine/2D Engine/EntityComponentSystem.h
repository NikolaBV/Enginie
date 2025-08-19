#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId GetNewComponentTypeID() {
	static ComponentId lastId = 0u;
	return lastId++;
}

template <typename T> inline ComponentId GetComponentTypeID() noexcept {
	static ComponentId typeId = GetNewComponentTypeID();
	return typeId;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
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
	Manager& manager;
	bool isActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitSet groupBitset;
public:
	Entity(Manager& mManager) : manager(mManager) {}
	void Update() {
		for (auto& c : components) c->Update();
	}
	void Draw() {
		for (auto& c : components) c->Draw();
	}
	bool IsActive() { return isActive; };
	void Destroy() { isActive = false; };
	bool HasGroup(Group mGroup) {
		return groupBitset[mGroup];
	}

	void AddGroup(Group mGroup);
	void DeleteGroup(Group mGroup) {
		groupBitset[mGroup] = false;
	}


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
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void Update() {
		for (auto& e : entities) e->Update();
	}
	void Draw() {
		for (auto& e : entities) e->Draw();
	}
	void refresh() {

		for (auto i(0u); i < maxGroups; i++) {
			auto& v(groupedEntities[i]);

			v.erase(
				std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
				{
					return !mEntity->IsActive() || !mEntity->HasGroup(i);
				}),
					std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->IsActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& GetGroup(Group mGroup) {
		return groupedEntities[mGroup];
	}

	Entity& AddEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
};
