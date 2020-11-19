#pragma once

#pragma once

#include <River.h>

struct Fade : public River::ECS::Component {
	bool active = true;
	double delay = 0;
	double duration = 1.0;
	double time = 0;
};