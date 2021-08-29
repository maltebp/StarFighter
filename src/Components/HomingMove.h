	#pragma once

#include <River.h>



/**
 * @brief	Simple "filter" component to find entities that should have their velocity
 *			updated according to 
*/
struct DirectionalMove : public River::ECS::Component {

	// If this is not null, this is the target (must have move component)
	River::ECS::Entity* targetEntity = nullptr;

	// Target point
	double x = 0;
	double y = 0;

	// How fast it adjusts it trajectory
	double homingSpeed = 1;

	std::function<void(River::ECS::Entity*)> onHit = nullptr;
};

