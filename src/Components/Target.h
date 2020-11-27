#pragma once

#include <River.h>


struct Target : public River::ECS::Component {
	bool active = true;

	// If this is not null, this is the target (must have a transform component)
	// TODO: Change this to a Component reference when that has been introduced to River::ECS
	River::ECS::Entity* targetEntity = nullptr;

	// Target point (only used if targetEntity is nullptr
	double targetX = 0;
	double targetY = 0;

	// How fast it adjusts it rotation
	double velocity = 0;
};

