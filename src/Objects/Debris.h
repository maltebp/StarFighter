#pragma once
#pragma once

#include <cstdlib>

#include "Utility/Math.h"

#include "GlobalAssets.h"
#include "Objects/Object.h"

#include "Components/Health.h"
#include "Components/TimedLife.h"
#include "Components/Fade.h"


namespace Objects::Debris {


	/**
	 * @brief	Constructs a small meteor on a particular position moving in a direction with a timed life. The shard has no collision
	*/
	inline Entity* createMeteorShard(Domain* domain, double x, double y, double size, double direction, double duration) {

		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;
		transform->width = size;
		transform->height = size;

		auto sprite = entity->addComponent<Sprite>();
		sprite->texture = GlobalAssets::Textures::METEOR_BROWN_TINY_1;

		auto move = entity->addComponent<Move>();

		auto rotationRadians = DEG_TO_RADIANS(direction);
		move->velocityX = cos(rotationRadians) * 1 * duration;
		move->velocityY = sin(rotationRadians) * 1 * duration;

		move->resistance = 0.020;
		move->rotationVelocity = 1.5;

		auto timedLife = entity->addComponent<TimedLife>();
		timedLife->active = true;
		timedLife->duration = duration;

		auto fade = entity->addComponent<Fade>();
		fade->delay = duration < 1.0 ? 0 : duration - 1.0;
		fade->duration = duration < 1.0 ? duration : 1.0;
		fade->active = true;

		return entity;
	}


	inline void createMeteorExplosion(Domain* domain, double x, double y) {

		unsigned int numShards = 7;
		float rotationPerShard = 360.0f / 7.0f;

		float rotation = 0;

		for( unsigned int i = 0; i < numShards; i++ ) {

			float direction = rotation + (rand() % 60 - 30);
			float duration = 1.5f + ((rand() % 200 - 100.0f) / 100.0f);
			float size = 8.0f + (rand() % 6 - 3.0f);

			createMeteorShard(
				domain,
				x, y,
				size,
				direction,
				duration
			);

			rotation += rotationPerShard;
		}


	}


	inline Entity* createMeteor(Domain* domain, double x, double y, double size) {
		auto object = Objects::create(domain);

		object.transform->x = x;
		object.transform->y = y;

		object.sprite->texture = GlobalAssets::Textures::METEOR_BROWN_MEDIUM_1;
		object.transform->width = size;
		object.transform->height = size;

		object.collider->type = ColliderTypes::DEBRIS;
		object.collider->width = object.transform->width;
		object.collider->height = object.transform->height;

		object.move->rotationVelocity = 1;

		auto health = object.entity->addComponent<Health>();
		health->amount = 50;
		health->invulnerable = false;
		health->onDeathCallback = [domain](Entity* meteor) {
			auto transform = meteor->getComponent<Transform>();
			createMeteorExplosion(domain, transform->x, transform->y);
		};


		return object.entity;
	}


	

}