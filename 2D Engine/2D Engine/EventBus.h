#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include "EntityComponentSystem.h"

struct DiedEvent { Entity* entity; };

class EventBus {
public:
	template<typename T>
	void Subscribe(std::function<void(const T&)> fn) {
		auto& vec = listeners[typeid(T)];
		vec.emplace_back([fn](const void* e) { fn(*static_cast<const T*>(e)); });
	}
	template<typename T>
	void Publish(const T& e) {
		auto it = listeners.find(typeid(T));
		if (it == listeners.end()) return;
		for (auto& cb : it->second) cb(&e);
	}
private:
	std::unordered_map<std::type_index, std::vector<std::function<void(const void*)>>> listeners;
};