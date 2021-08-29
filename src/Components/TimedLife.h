#pragma once

#include <River.h>

struct TimedLife : public River::ECS::Component {
	bool active = true;
	double duration = 0;
};

