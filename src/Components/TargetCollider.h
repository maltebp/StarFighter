#pragma once

#include <River.h>

#include <functional>



struct TargetCollider : public River::ECS::Component {

	// The distance to collide with
	double distance = 1;

	std::function<void(River::ECS::Entity*)> onCollision = nullptr;
};