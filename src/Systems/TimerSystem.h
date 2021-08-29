#pragma once

#include "Components/Timer.h"
#include "Components/TimedLife.h"


using namespace River::ECS;


class TimerSystem {
public:


	static void update(Domain* domain, double timeStep) {
		
		domain->forMatchingEntities<Timer>([timeStep](Entity* entity, Timer* timer) {

			// This can be optimized
			if( timer->active && timer->remainingTime <= 0 ) timer->remainingTime = timer->time;
			if( !timer->active || timer->remainingTime <= 0 ) return;

			timer->remainingTime -= timeStep;
			if( timer->remainingTime <= 0 ) {
				if( timer->periodic ) {
					timer->active = true;
					timer->remainingTime += timer->time;
				} else {
					timer->active = false;
					timer->remainingTime = 0;
				}
				timer->onFinish(entity);
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