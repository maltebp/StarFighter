#pragma once

#include <River.h>

#include "GlobalAssets.h"

#include "Components/TimedLife.h"

#include "Utility/Random.h"

namespace Objects::Effects {

	using namespace River::ECS;


	/**
	 * @brief	Creates a simple animated explosion
	*/
	inline void createExplosion( Domain* domain, double x, double y, double size ) {
		
		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;
		transform->width = size;
		transform->height = size;
		transform->rotation = Random::getInt(0, 359);
		
		auto sprite = entity->addComponent<Sprite>();

		auto spriteAnimation = entity->addComponent<SpriteAnimation>();
		spriteAnimation->animation = GlobalAssets::Animations::EXPLOSION;

		auto timedLife = entity->addComponent<TimedLife>();
		timedLife->duration = spriteAnimation->animation->getTotalDuration() - 0.02;
		timedLife->active = true;	
	}


	inline void createShipExplosion(Domain* domain, double x, double y, double size) {
		Particle::emit(
			domain,
			GlobalAssets::Textures::SHIP_DEBRIS,
			x, y,		// Position
			3, 4,		// Count
			15, 25,		// Size
			2.0, 2.5,	// Velocity
			1.5, 2.5,	// Rotation velocity
			0, 360,		// Direction
			1.0, 1.5	// Duration
		);

		createExplosion(domain, x, y, size);
	}

}