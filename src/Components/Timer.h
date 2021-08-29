#pragma once

#include <River.h>


struct Timer : public River::ECS::Component {
	bool active = true;
	bool periodic = false;
	
	double time = 1.0;
	double remainingTime = 0;
	
	std::function<void(River::ECS::Entity* e)> onFinish;

	Entity* startTimer(Domain* domain, double time, std::function<void(River::ECS::Entity* e, Timer* t)> action, bool periodic = false ){
		auto entity = domain->createEntity(); 
	}
};

