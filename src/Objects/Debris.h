#pragma once
#pragma once

#include <cstdlib>

#include "Utility/Math.h"

#include "GlobalAssets.h"
#include "Objects/Object.h"
#include "Objects/Particle.h"

#include "Components/Health.h"
#include "Components/TimedLife.h"
#include "Components/Fade.h"


namespace Objects::Debris {

	inline void createMeteorExplosion(Domain* domain, double x, double y) {
		Particle::emit(
			domain,
			GlobalAssets::Textures::METEOR_BROWN_TINY_1,
			x, y,		// Position
			5, 9,		// Count
			5, 12,		// Size
			0.5, 1.5,	// Velocity
			0.5, 1.5,	// Rotation velocity
			0, 360,		// Direction
			1, 2		// Duration
		);
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