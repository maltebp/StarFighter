#pragma once

#include <River.h>

#include "Components/Move.h"
#include "Components/TimedLife.h"
#include "Components/Fade.h"

#include "Utility/Math.h"
#include "Utility/Random.h"


namespace Objects::Particle {

	using River::Texture;
	using namespace River::ECS;

	inline void createParticle(
		Domain* domain,
		Texture* texture,
		double x, double y,
		double size,
		double velocity, double rotationVelocity,
		double direction,
		double duration)
	{

		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;
		transform->width = size;
		transform->height = size / texture->getAspectRatio();

		auto sprite = entity->addComponent<Sprite>();
		sprite->texture = texture;

		auto move = entity->addComponent<Move>();

		auto rotationRadians = DEG_TO_RADIANS(direction);
		move->velocityX = cos(rotationRadians) * velocity;
		move->velocityY = sin(rotationRadians) * velocity;

		move->rotationVelocity = rotationVelocity;

		auto timedLife = entity->addComponent<TimedLife>();
		timedLife->active = true;
		timedLife->duration = duration;

		auto fade = entity->addComponent<Fade>();
		double fadeDuration = 0.5;
		fade->delay = duration < fadeDuration ? 0 : duration - fadeDuration;
		fade->duration = duration < fadeDuration ? duration : fadeDuration;
		fade->active = true;
	}


	inline void emit(
		Domain* domain,
		Texture* texture,
		double x, double  y,
		unsigned int countMin, unsigned int countMax,
		double sizeMin, double sizeMax,
		double velocityMin, double velocityMax,
		double rotationVelocityMin, double rotationVelocityMax,
		double directionMin, double directionMax,
		double durationMin, double durationMax
	) {

		unsigned int count = Random::getInt(countMin, countMax);
		for( int i = 0; i < count; i++ ) {

			createParticle(
				domain,
				texture,
				x, y,
				Random::getDouble(sizeMin, sizeMax),
				Random::getDouble(velocityMin, velocityMax),
				Random::getDouble(rotationVelocityMin, rotationVelocityMax),
				Random::getDouble(directionMin, directionMax),
				Random::getDouble(durationMin, durationMax)
			);
		}
	}


	inline void emit(
		Domain* domain,
		std::vector<Texture*>& textures,
		double x, double  y,
		unsigned int countMin, unsigned int countMax,
		double sizeMin, double sizeMax,
		double velocityMin, double velocityMax,
		double rotationVelocityMin, double rotationVelocityMax,
		double directionMin, double directionMax,
		double durationMin, double durationMax
		)
	{
		emit(
			domain,
			textures.at(Random::getInt(0, textures.size() - 1)),
			x, y,
			countMin, countMax,
			sizeMin, sizeMax,
			velocityMin, velocityMax,
			rotationVelocityMin, rotationVelocityMax,
			directionMin, directionMax,
			durationMin, durationMax

		);
	}


}