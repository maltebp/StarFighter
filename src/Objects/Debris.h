#pragma once
#pragma once

#include "GlobalAssets.h"

#include "Components/Health.h"
#include "Utility/Math.h"
#include "Objects/Object.h"


namespace Objects::Debris {


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


		return object.entity;
	}

}