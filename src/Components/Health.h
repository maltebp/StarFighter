#pragma once

#include <River.h>

struct Health : public River::ECS::Component {
	bool invulnerable = false;
	double amount = 0;
};