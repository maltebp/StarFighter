#pragma once

#include "Components/TimedLife.h"


using namespace River::ECS;


class TimedLifeSystem {
public:


	static void update(Domain* domain) {
		domain->forMatchingEntities<TimedLife>([](Entity* entity, TimedLife* timedLife) {
			if( !timedLife->active || timedLife->duration <= 0 ) return;
			timedLife->duration -= 0.016;
			if( timedLife->duration <= 0 ) {
				entity->destroy();
			}
			});
	}


};