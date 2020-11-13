#pragma once

#include <River.h>

#include "Utility/Math.h"

#include "Components/Move.h"
#include "Components/BoundaryBounce.h"

using namespace River::ECS;

class MovementSystem {
public:

	static void update(River::ECS::Domain* domain) {

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
			move->velocityX += (move->accelerationX - move->resistance * move->velocityX);
			move->velocityY += (move->accelerationY - move->resistance * move->velocityY);

			transform->x += move->velocityX;
			transform->y += move->velocityY;

			transform->rotation += move->rotationVelocity;


			if( move->destroyWhenOutOfBounds )
				if( transform->x < -700 || transform->x > 700 || transform->y < -350 || transform->y > 350 )
					entity->destroy();
		});

		

	}

};

