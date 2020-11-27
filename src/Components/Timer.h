#pragma once

#include <River.h>



struct Timer : public River::ECS::Component {
	bool active = true;
	double time = 1.0;
	std::function<void(River::ECS::Entity* e, Timer* timer)> onFinish;
};

