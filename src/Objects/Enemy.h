#pragma once

#include <River.h>

#include "Utility/Math.h"

#include "GlobalAssets.h"

#include "Objects/Missile.h"
#include "Objects/Effects.h"

#include "Components/Health.h"
#include "Components/Move.h"
#include "Components/AutoFire.h"
#include "Components/BoxCollider.h"
#include "Components/BoundaryBounce.h"


using namespace River::ECS;

namespace Objects::Enemy {


	inline Entity* createUfo(Domain* domain, double x, double y, double direction, double velocity, double rotationVelocity) {

		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;
		transform->width = 50;
		transform->height = 50;

		auto sprite = entity->addComponent<Sprite>();
		sprite->texture = GlobalAssets::Textures::UFO_RED;

		auto move = entity->addComponent<Move>();

		auto rotationRadians = DEG_TO_RADIANS(direction);
		move->velocityX = cos(rotationRadians) * velocity;
		move->velocityY = sin(rotationRadians) * velocity;
		move->rotationVelocity = rotationVelocity;

		entity->addComponent<BoundaryBounce>();

		auto collider = entity->addComponent<BoxCollider>();
		collider->width = 40;
		collider->height = 40;
		collider->type = ColliderTypes::ENEMY;


		auto health = entity->addComponent<Health>();
		health->amount = 250;
		health->onDeathCallback = [domain](Entity* e) {
			auto transform = e->getComponent<Transform>();
			Effects::createShipExplosion(domain, transform->x, transform->y, 100);
		};

		auto autoFire = entity->addComponent<AutoFire>();
		autoFire->frequency = 0.25;
		autoFire->numMissiles = 4;
		autoFire->directionIncrease = 90;

	
		return entity;
	}


	inline Entity* createMissile(Domain* domain, double x, double y, double direction, double velocity) {
		
		auto object = Objects::Missile::create(domain, x, y, direction, velocity);

		object.sprite->texture = GlobalAssets::Textures::LASER_RED;
		object.sprite->rotationOffset = -90;

		object.transform->width = 30 * GlobalAssets::Textures::LASER_RED->getAspectRatio();
		object.transform->height = 30;

		object.collider->type = ColliderTypes::ENEMY_MISSILE;
		object.collider->width = object.transform->width;
		object.collider->height = object.transform->height;

		object.damage->amount = 30;

		return object.entity;
	}

}