#pragma once

#include <River.h>


struct Target : public River::ECS::Component {
	River::ECS::Entity* target = nullptr;
	double velocity = 0;
};

