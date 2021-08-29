#pragma once

#include <River.h>

struct AutoFire : public River::ECS::Component {

	// The time in this "fire" sequence
	float time = 0;
	
	// Time between firing (plus direction delay * number of missiles)
	float frequency = 1.0f;

	// Time between each direction
	float delay = 0.0f;

	// Number of missiles to fire (with direction delay in between each)
	unsigned short numMissiles = 1;

	// Number of missiles fired (between 0 and numMissiles)
	unsigned short numMissileFired = 0;

	// Offset direction of first missile relative to Transform rotation
	float directionOffset = 0;

	// Direction increase between each missile
	float directionIncrease = 0;
};