#pragma once

#include <River.h>
#include <functional>


namespace Util::ECS {

	using namespace River::ECS;

	/**
	 * @brief	Finds all Transforms that are within range of a certain point
	*/
	inline void forEntitiesInRange(Domain* domain, double x, double y, double range, std::function<void(Entity*)> action) {

		domain->forMatchingEntities<Transform>([&](Entity* e, Transform* transform){

			// Filtering by distance
			double xDiff = (double)transform->x - x;
			double yDiff = (double)transform->y - y;
			double distance = sqrt(xDiff * xDiff + yDiff * yDiff);
			
			if( distance <= range ) {
				action(e);
			}
		});

	}
}