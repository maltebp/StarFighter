#pragma once

#include <cstdint>

#include <River.h>

struct ColliderType {

	using Id = uint8_t;

	static inline Id nextId = 0;

	static ColliderType define() {
		return ColliderType(nextId++);
	}

	Id id;

	ColliderType() : id(0) {}

	const ColliderType& operator=(const ColliderType& other) {
		id = other.id;
		return *this;
	}

	bool operator==(const ColliderType& other) const {
		return id == other.id;
	}


	bool operator!=(const ColliderType& other) const {
		return id != other.id;
	}

private:
	ColliderType(Id id) : id(id) {}

};

namespace ColliderTypes {
	const ColliderType	UNKNOWN			= ColliderType::define();
	const ColliderType	PLAYER			= ColliderType::define();
	const ColliderType	PLAYER_MISSILE	= ColliderType::define();
	const ColliderType	ENEMY			= ColliderType::define();
	const ColliderType	ENEMY_MISSILE   = ColliderType::define();
	const ColliderType	DEBRIS			= ColliderType::define();
	const ColliderType	ROCKET			= ColliderType::define();
	const ColliderType	IMPENETRABLE	= ColliderType::define();
}

 // Hash for ColliderType
namespace std {
	template<>
	struct hash<ColliderType> {
		inline size_t operator()(const ColliderType& x) const {
			return std::hash<uint8_t>()(x.id);
		}
	};
}


struct BoxCollider : public River::ECS::Component {

	ColliderType type = ColliderTypes::UNKNOWN;

	bool enabled = true;

	// Not expecting to require high precision in updates, so we use floats
	float xOffset = 0;
	float yOffset = 0;
	float rotationOffset = 0;
	float width = 0;
	float height = 0;
};

