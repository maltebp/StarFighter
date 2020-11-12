#pragma once

#include <River.h>

#include "Components/Move.h"
#include "Components/Target.h"

using namespace River::ECS;

#define PI 3.14159265

class TargetSystem {
private:
	static double getAngle(double x, double y) {
		if( y > 0 ) return acos(x / sqrt(x * x + y * y)) * 180 / PI;
		return 360 - acos(x / sqrt(x * x + y * y)) * 180 / PI;
	}

public:

	static void update(Domain* domain) {


		domain->forEachEntity<Transform, Target>([](Entity* entity, Transform* transform, Target* target) {
			if( target->target == nullptr ) return;

			auto targetTransform = target->target->getComponent<Transform>();


			auto angleDifference = getAngle(targetTransform->x, targetTransform->y) - transform->rotation;

			auto direction = angleDifference > 0 ? 1 : -1;

			auto absoluteDifference = angleDifference * direction;

			if( absoluteDifference > 180 )
				direction *= -1;

			auto angleMovement = (target->velocity > absoluteDifference ? absoluteDifference : target->velocity) * direction;

			transform->rotation += angleMovement;

			// Do "double" modolu
			transform->rotation = ((int)transform->rotation) % 360;
			if( transform->rotation < 0 )
				transform->rotation += 360;
		});
	

	}

};

