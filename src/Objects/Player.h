#pragma once

#include <River.h>

#include "Objects/Missile.h"

#include "Components/BoxCollider.h"
#include "Components/Move.h"
#include "Components/Target.h"
#include "GlobalAssets.h"
#include "Domains.h"

using namespace River::ECS;

namespace Objects::Player {
		

	Entity* create(Domain* domain, Entity* mouseEntity) {

		auto object = Objects::create(domain);

		object.transform->width = 50 * GlobalAssets::Textures::PLAYER->getAspectRatio();
		object.transform->height = 50;
		object.transform->depth = 10;

		object.move->resistance = 0.05;

		object.sprite->rotationOffset = 90;
		object.sprite->texture = GlobalAssets::Textures::PLAYER;

		object.collider->width = 40;
		object.collider->height = 40;
		object.collider->type = ColliderTypes::PLAYER;

		auto target = object.entity->addComponent<Target>();
		target->target = mouseEntity;
		target->velocity = 6;

		return object.entity;
	}




	inline Entity* createMissile(Domain* domain, Entity* player) {
		auto playerTransform = player->getComponent<Transform>();
		
		auto object = Objects::Missile::create(domain, playerTransform->x, playerTransform->y, playerTransform->rotation, 20.0);

		object.sprite->texture = GlobalAssets::Textures::LASER_BLUE;
		object.sprite->rotationOffset = -90;
		
		object.transform->width = 30 * GlobalAssets::Textures::LASER_BLUE->getAspectRatio();
		object.transform->height = 30;

		object.collider->type = ColliderTypes::PLAYER_MISSILE;
		object.collider->width = object.transform->width;
		object.collider->height = object.transform->height;

		object.damage->amount = 30;

		return object.entity;
	}


	inline void createRocket(Domain* domain, Entity* player) {
		
		auto rocket = Objects::Missile::

	}
}