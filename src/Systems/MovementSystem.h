#pragma once

#include <River.h>

#include "Utility/Math.h"

#include "Components/HomingMove.h"
#include "Components/Move.h"
#include "Components/BoundaryBounce.h"

using namespace River::ECS;

class MovementSystem {
public:

	static void update(River::ECS::Domain* domain) {

		// Homing movement
		//domain->forMatchingEntities<Transform, Move, HomingMove>([&](Entity* entity, Transform* transform, Move* move, HomingMove* homing) {

		//	double targetX, targetY;
		//	if( homing->targetEntity != nullptr ) {
		//		// Note: We don't check if the target entity is valid (it may have been removed from the domain)
		//		auto targetTransform = domain->getEntityComponent<Transform>(homing->targetEntity);
		//		targetX = targetTransform->x;
		//		targetY = targetTransform->y;
		//		// Not testing for nullptr and throwing exception, because it will crash anyway
		//	} else {
		//		targetX = homing->x;
		//		targetY = homing->y;
		//	}

		//	// Direction to target*
		//	double targetDirection = Util::Math::getAngle(targetX-transform->x, targetY-transform->y);
		//	double currentDirection = Util::Math::getAngle(move->velocityX, move->velocityY);

		//	// Calculate (absolute) directiondifference
		//	double directionDifference = targetDirection - currentDirection;
		//	int directionSignFactor = (directionDifference < 0) ? -1 : 1;
		//	directionDifference *= directionSignFactor;
		//	
		//	// Adjusting current direction to new direction
		//	double newDirection;
		//	if( directionDifference < homing->homingSpeed ) {
		//		newDirection = targetDirection;
		//	} else {
		//		newDirection = currentDirection + (homing->homingSpeed*directionSignFactor);
		//	}
		//	
		//	// Update the velocity / direction)
		//	auto currentVelocity = Util::Math::vectorLength(move->velocityX, move->velocityY);
		//	auto [newVelocityX, newVelocityY] = Util::Math::vectorFromAngle(newDirection, currentVelocity);
		//	move->velocityX = newVelocityX;
		//	move->velocityY = newVelocityY;		

		//	// Rotate object to face velocity
		//	transform->rotation = newDirection;
		//});


		// Update boundary movement
		domain->forMatchingEntities<Transform, Move, BoundaryBounce>([](Entity* entity, Transform* transform, Move* move, BoundaryBounce* boundary) {

			double moveX = transform->x + move->velocityX;
			double moveY = transform->y + move->velocityY;

			// Up
			if( move->velocityX > 0 ) {
				if( moveX > 600 ) move->velocityX *= -1;
			} else
				if( moveX < -600 ) move->velocityX *= -1;

			if( move->velocityY > 0 ) {
				if( moveY > 300 ) move->velocityY *= -1;
			} else
				if( moveY < -300 ) move->velocityY *= -1;

		});


		// Update movement
 		domain->forMatchingEntities<Transform, Move>([](Entity* entity, Transform* transform, Move* move){
			transform->rotation += move->rotationVelocity;

			move->velocityX += (move->accelerationX - move->resistance * move->velocityX);
			move->velocityY += (move->accelerationY - move->resistance * move->velocityY);

			if( move->forwardVelocity ) {
				// Set velocity direction to same as transform rotation
				auto currentVelocity = Util::Math::vectorLength(move->velocityX, move->velocityY);
				auto [newVelocityX, newVelocityY] = Util::Math::vectorFromAngle(transform->rotation, currentVelocity);
				move->velocityX = newVelocityX;
				move->velocityY = newVelocityY;
			}

			transform->x += move->velocityX;
			transform->y += move->velocityY;


			if( move->destroyWhenOutOfBounds )
				if( transform->x < -700 || transform->x > 700 || transform->y < -350 || transform->y > 350 )
					entity->destroy();
		});

		

	}

};

