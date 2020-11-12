#pragma once

#include <River.h>

#include "Components/Health.h"

using namespace River::ECS;

class HealthSystem {
public:


	static void update(Domain* domain) {

		domain->forMatchingEntities<Health>([&domain](Entity* entity, Health* health) {
		
			if( health->amount <= 0 )
				domain->destroyEntity(entity);
		
			// TODO: Update from Level
		});

	}

};

