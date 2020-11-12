#pragma once

#include <River.h>

#include "Components/Move.h"

using namespace River::ECS;

class MovementSystem {
public:

	static void update(River::ECS::Domain* domain) {

		
		domain->forEachEntity<Transform, Move>([](Entity* entity, Transform* transform, Move* move){
			
			transform->x += move->velocityX;
			transform->y += move->velocityY;
			
		});

		

	}

};

