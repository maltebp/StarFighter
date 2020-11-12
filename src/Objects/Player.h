#pragma once

#include <River.h>

#include "Components/BoxCollider.h"
#include "Components/Move.h"
#include "Components/Target.h"
#include "GlobalAssets.h"
#include "Domains.h"

using namespace River::ECS;

namespace Player {
		

	Entity* create(Domain* domain, Entity* mouseEntity) {

		auto player = domain->createEntity();

		auto transform = player->addComponent<Transform>();
		transform->height = 50;
		transform->width = transform->height * GlobalAssets::Textures::PLAYER->getAspectRatio();
		transform->x = 0;
		transform->y = 0;
		transform->depth = 10;

		auto move = player->addComponent<Move>();
		move->velocityX = 0.0;
		move->velocityY = 0;
		move->accelerationX = 0;
		move->accelerationY = 0;
		move->resistance = 0.05;

		auto sprite = player->addComponent<Sprite>();
		sprite->rotationOffset = 90;
		sprite->texture = GlobalAssets::Textures::PLAYER;

		auto collider = player->addComponent<BoxCollider>();
		collider->width = 40;
		collider->height = 40;
		collider->type = ColliderTypes::PLAYER;
		collider->xOffset = 0;
		collider->yOffset = 0;
		collider->enabled = true;

		auto target = player->addComponent<Target>();
		target->target = mouseEntity;
		target->velocity = 6;


		return player;
	}

}