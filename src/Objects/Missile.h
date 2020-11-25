#pragma once

#include "Utility/Math.h"
#include "Objects/Object.h"

#include "Components/Move.h"
#include "Components/DamageLoad.h"
#include "Components/TimedLife.h"


namespace Objects::Missile {

	struct MissileObject {
		Entity* entity;
		Transform* transform;
		Sprite* sprite;
		Move* move;
		BoxCollider* collider;
		DamageLoad* damage;
	};

	inline MissileObject create(Domain* domain, double x, double y, double direction, double velocity) {
		auto object = Objects::create(domain);

		object.transform->rotation = direction;
		object.transform->x = x;
		object.transform->y = y;

		auto rotationRadians = DEG_TO_RADIANS(object.transform->rotation);
		object.move->velocityX = cos(rotationRadians) * velocity;
		object.move->velocityY = sin(rotationRadians) * velocity;
		object.move->destroyWhenOutOfBounds = true;

		auto damage = object.entity->addComponent<DamageLoad>();

		return { object.entity, object.transform, object.sprite, object.move, object.collider, damage };
	}



}