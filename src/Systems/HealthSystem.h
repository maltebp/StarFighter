#pragma once

#include <River.h>

#include "Objects/Debris.h"
#include "Components/Health.h"

using namespace River::ECS;

class HealthSystem {
public:


	static void update(Domain* domain) {

		domain->forMatchingEntities<Health>([&domain](Entity* entity, Health* health) {
			
			if( health->amount <= 0 ) {
				bool destroy = true;
				if( health->onDeathCallback != nullptr )
					destroy = health->onDeathCallback(entity);
				if( destroy )
					domain->destroyEntity(entity);
			}
		
			// TODO: Update from Level
		});

	}

};

