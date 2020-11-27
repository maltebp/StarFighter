#pragma once

#include <River.h>

struct Move : public River::ECS::Component {
	double resistance = 0;
	double velocityX = 0;
	double velocityY = 0;
	double accelerationX = 0;
	double accelerationY = 0;

	double rotationVelocity = 0;

	// Whether or not to update velocity direction according to transform rotation
	bool forwardVelocity = false;


	bool destroyWhenOutOfBounds = false;
};