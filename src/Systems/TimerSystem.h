#pragma once

#include "Components/Timer.h"
#include "Components/TimedLife.h"


using namespace River::ECS;


class TimerSystem {
public:


	static void update(Domain* domain, double timeStep) {
		
		domain->forMatchingEntities<Timer>([timeStep](Entity* entity, Timer* timer) {
			if( !timer->active || timer->time <= 0 ) return;

			timer->time -= timeStep;
			if( timer->time <= 0 ) {
				timer->active = false;
				timer->onFinish(entity, timer);
			}
		});
		
		domain->forMatchingEntities<TimedLife>([](Entity* entity, TimedLife* timedLife) {
			if( !timedLife->active || timedLife->duration <= 0 ) return;
			timedLife->duration -= 0.016;
			if( timedLife->duration <= 0 ) {
				entity->destroy();
			}
			});
	}


};