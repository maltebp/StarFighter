#pragma once

#include <River.h>



struct MoveTarget : public River::ECS::Component {
	bool active;
	double x = 0;
	double y = 0;

	std::function<void(River::ECS::Entity*)> onHit = nullptr;
};

