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

	// How fast it adjusts its rotation
	double velocity = 0;

	// Whether or not its triggered in range. Will be set to false, BEFORE
	// calling the action, so you may reset it to true, in case you want
	// retrigger
	bool triggered = false;
	double triggerRange = 10;
	std::function<void(River::ECS::Entity*)> triggerAction= nullptr;
};

