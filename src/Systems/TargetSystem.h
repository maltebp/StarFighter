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


		// Rotate to target
		domain->forMatchingEntities<Transform, Target>([](Entity* entity, Transform* transform, Target* target) {
			if( !target->active ) return;

			// Determine target x, y (point or entity)
			double targetX, targetY;
			if( target->targetEntity != nullptr ) {
				// Note: We don't check if the target entity is valid (it may have been removed from the domain)
				auto targetTransform = target->targetEntity->getComponent<Transform>();
				targetX = targetTransform->x;
				targetY = targetTransform->y;
				// Not testing for nullptr and throwing exception, because it will crash anyway
			} else {
				targetX = target->targetX;
				targetY = target->targetY;
			}

			// Check if target is reached
			if( !target->triggered ) {
				if( Util::Math::distanceBetweenPoints(transform->x, transform->y, targetX, targetY) < target->triggerRange ) {
					target->triggered = true;
					if( target->triggerAction != nullptr ) target->triggerAction(entity);
				}
			}

			// Change rotation
			auto targetAngle = Util::Math::getAngle(targetX-transform->x, targetY-transform->y);
			auto angleDifference = targetAngle - transform->rotation;

			auto direction = angleDifference > 0 ? 1 : -1;

			auto absoluteDifference = angleDifference * direction;

			if( absoluteDifference > 180 )
				direction *= -1;

			auto angleMovement = (target->velocity > absoluteDifference ? absoluteDifference : target->velocity) * direction;

			transform->rotation += angleMovement;
			transform->rotation = Util::Math::clampAngle(transform->rotation);
		});
	

	}

};

