#pragma once

#include <vector>
#include <unordered_map>

#include <River.h>
#include "Log.h"
#include "Objects/Enemy.h"
#include "Objects/Player.h"
#include "Components/AutoFire.h"

#define PI 3.14159265


using namespace River::ECS;


class EnemyFireSystem {
public:


	static void update(Domain* domain) {

		domain->forMatchingEntities<Transform, AutoFire>([&domain](Entity* e, Transform* transform, AutoFire* fire) {
			
			fire->time += 0.016;

			auto totalFrequency = fire->frequency + fire->delay * (fire->numMissiles-1);
			if( fire->time > totalFrequency ) {
				fire->time -= totalFrequency;
				fire->numMissileFired = 0;
			}


			for( unsigned int i = fire->numMissileFired; i < fire->numMissiles; i++ ) {
				if( fire->delay * i > fire->time ) break;
				Objects::Enemy::createMissile(
					domain,
					transform->x, transform->y,
					transform->rotation + fire->directionOffset + fire->directionIncrease * i,
					10
				);
				fire->numMissileFired++;
			}		
			

		});



	}

};
