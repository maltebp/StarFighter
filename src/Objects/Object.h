#pragma once

#include <tuple>

#include <River.h>

#include "Components/BoxCollider.h"
#include "Components/Move.h"


using namespace River::ECS;

namespace Objects {
	
	struct Object {
		Entity* entity;
		Transform* transform;
		Sprite* sprite;
		Move* move;
		BoxCollider* collider;
	};

	inline Object create(Domain* domain) {

		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = 0;
		transform->y = 0;
		transform->width = 0;
		transform->height = 0;
		transform->depth = 0;
		transform->rotation = 0;

		auto sprite = entity->addComponent<Sprite>();
		sprite->texture = nullptr;
		sprite->xOffset = 0;
		sprite->yOffset = 0;
		sprite->rotationOffset = 0;

		auto move = entity->addComponent<Move>();
		move->velocityX = 0;
		move->velocityY = 0;
		move->accelerationX = 0;
		move->accelerationY = 0,
		move->resistance = 0;
		move->rotationVelocity = 0;

		auto collider = entity->addComponent<BoxCollider>();
		collider->enabled = true;
		collider->width = 0;
		collider->height = 0;
		collider->rotationOffset = 0;
		collider->type = ColliderTypes::UNKNOWN;
		collider->xOffset = 0;
		collider->yOffset = 0;

		return { entity, transform, sprite, move, collider };
	}
}
