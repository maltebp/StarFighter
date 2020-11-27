#pragma once

#include <River.h>

enum class HealthType {
	UNKNOWN,
	ENEMY,
	DEBRIS,
	PLAYER,
	ROCKET
};


struct Health : public River::ECS::Component {
	bool invulnerable = false;
	double amount = 1;
	HealthType type = HealthType::UNKNOWN;
	std::function<bool (River::ECS::Entity* e) > onDeathCallback = nullptr;

	inline void kill() {
		if( !invulnerable ) amount = -1;
	}
};