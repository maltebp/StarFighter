#pragma once

#include <River.h>

#include "Log.h"

#include "Components/Move.h"
#include "Components/Target.h"

using namespace River::ECS;

#define PI 3.14159265

class TargetSystem {
private:
	

public:

	static void update(Domain* domain) {


		domain->forMatchingEntities<Transform, Target>([](Entity* entity, Transform* transform, Target* target) {
			if( target->target == nullptr ) return;

			auto targetTransform = target->target->getComponent<Transform>();


			auto targetAngle = Util::Math::getAngle(targetTransform->x-transform->x, targetTransform->y-transform->y);
			auto angleDifference = targetAngle - transform->rotation;

			//LOG(targetAngle);


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

