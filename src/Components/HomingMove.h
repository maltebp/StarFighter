#pragma once

#include <River.h>



struct MoveTarget : public River::ECS::Component {
	
	bool active;

	// If this is not null, this is the target (must have move component)
	River::ECS::Entity* targetEntity = nullptr;

	double x = 0;
	double y = 0;

	// How fast it adjusts it trajectory
	double homingSpeed = 1;

	std::function<void(River::ECS::Entity*)> onHit = nullptr;
};

