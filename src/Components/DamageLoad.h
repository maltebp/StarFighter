#pragma once

#include <River.h>

struct DamageLoad : public River::ECS::Component {
	double amount = 0;
};