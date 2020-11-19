#pragma once

#include <River.h>

#include "Components/Fade.h"

using namespace River::ECS;

class FadeSystem {
public:

	static void update(Domain* domain, double timeStep) {
		
		domain->forMatchingEntities<Fade, Sprite>([&](auto entity, Fade* fade, Sprite* sprite) {
			if( !fade->active ) return;
		
			// Check if finished
			double totalDuration = fade->duration + fade->delay;
			if( fade->time > totalDuration ) return;

			fade->time += timeStep;
			
			double fadeTime = fade->time - fade->delay;
			if( fadeTime <= 0 ) return;

			sprite->opacity = (float) (1.0 - fadeTime / fade->duration);
		});

	}

};

