#pragma once

#include <River.h>

struct Move : public River::ECS::Component {
	double velocityX = 0;
	double velocityY = 0;
};