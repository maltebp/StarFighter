#pragma once

#include "Utility/Math.h"
#include "Objects/Object.h"


namespace Objects::Missile {

	inline Objects::Object create(Domain* domain, double x, double y, double direction, double velocity) {
		auto object = Objects::create(domain);

		object.transform->rotation = direction;
		object.transform->x = x;
		object.transform->y = y;

		auto rotationRadians = DEG_TO_RADIANS(object.transform->rotation);
		object.move->velocityX = cos(rotationRadians) * velocity;
		object.move->velocityY = sin(rotationRadians) * velocity;
		
		return object;	
	}


}