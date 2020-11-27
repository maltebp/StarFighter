#pragma once

#include <vector>
#include <unordered_map>

#include <River.h>

#include "Objects/Effects.h"

#include "Utility/Math.h"

#include "Log.h"
#include "Components/Health.h"
#include "Components/DamageLoad.h"
#include "Components/BoxCollider.h"
#include "Components/Target.h"
#include "Components/TargetCollider.h"

#define PI 3.14159265


using namespace River::ECS;


class CollisionSystem {

	struct Point {
		double x, y;
	};

	struct CollisionEntity {
		Entity* entity;
		Transform* transform;
		BoxCollider* collider;

		// Distance to filter collisions with (two objects can't collide if they're not within distance of each other)
		double distance;
		
		CollisionEntity(Entity* entity, Transform* transform, BoxCollider* boxCollider, double distance)
			: entity(entity), transform(transform), collider(boxCollider), distance(distance)
		{ }
	};


	struct CollisionData {
		double halfWidth, halfHeight;
		double rotation;
		Point translation;
	};


	static inline bool testCollision(CollisionData& source, CollisionData& target) {
	
		Point sourceRawPoints[4] = {
			{ -source.halfWidth, -source.halfHeight }, // Bottom left
			{ -source.halfWidth, source.halfHeight }, // Top left
			{ source.halfWidth, source.halfHeight }, // Top right
			{ source.halfWidth, -source.halfHeight }, // Bottom right
		};


		// Calculating rotations/translation offsets
		double adjustedSourceRotation = (source.rotation) * PI / 180;
		double sourceCos = cos(adjustedSourceRotation);
		double sourceSin = sin(adjustedSourceRotation);

		// Calculating rotations/translation offsets
		double targetSourceRotation = -target.rotation * PI / 180;
		double targetCos = cos(targetSourceRotation);
		double targetSin = sin(targetSourceRotation);

		for( auto& sourcePoint : sourceRawPoints ) {

			// Transform using source transformation
			Point transformedPoint = {
				(sourcePoint.x * sourceCos - sourcePoint.y * sourceSin) + source.translation.x,
				(sourcePoint.y * sourceCos + sourcePoint.x * sourceSin) + source.translation.y
			};

			// Perform inverse target transformation
			auto translatedX = transformedPoint.x - target.translation.x;
			auto translatedY = transformedPoint.y - target.translation.y;
			Point targetTransformedPoint{
				translatedX * targetCos - translatedY * targetSin,
				translatedY * targetCos + translatedX * targetSin
			};

			// Test if point is within target raw rect
			if(
				targetTransformedPoint.x >= -target.halfWidth && targetTransformedPoint.x <= target.halfWidth &&
				targetTransformedPoint.y >= -target.halfHeight && targetTransformedPoint.y <= target.halfHeight
				)
				return true;
		}

		return false;
	}

	static inline std::unordered_map<ColliderType, std::vector<CollisionEntity>> typeMap;

public:


	


	static void checkCollisions(std::vector<CollisionEntity>& sources, std::vector<CollisionEntity>& targets, std::function<void (Entity* source, Entity*target)> callback) {
		
		for( auto source : sources ) {
			for( auto target : targets ) {

				// Filtering by distance
				double xDiff = ((double)source.transform->x) - ((double)target.transform->x);
				double yDiff = ((double)source.transform->y) - ((double)target.transform->y);
				double distance = sqrt(xDiff*xDiff + yDiff*yDiff);
				if( distance > source.distance + target.distance )
					continue;

				CollisionData sourceData = {
					source.collider->width/2.0, source.collider->height/2.0,
					source.collider->rotationOffset + source.transform->rotation,
					{ source.transform->x + source.collider->xOffset, source.transform->y + source.collider->yOffset }
				};

				CollisionData targetData = {
					target.collider->width/2.0, target.collider->height/2.0,
					target.collider->rotationOffset + target.transform->rotation,
					{ target.transform->x + target.collider->xOffset, target.transform->y + target.collider->yOffset },
				};

				// Test collision
				if( testCollision(sourceData, targetData) || testCollision(targetData, sourceData) )
					callback(source.entity, target.entity);
			}
		}
		
	}


	static void update(Domain* domain) {

		for( auto& pair : typeMap ) {
			pair.second.clear();
		} 

		// Testing simple target collider first
		domain->forMatchingEntities<Transform, Target, TargetCollider>([](Entity* e, Transform* transform, Target* target, TargetCollider* collider) {
			auto currentDistance = Util::Math::vectorLength(target->targetX - transform->x, target->targetY - transform->y);
			if( collider->distance > currentDistance ) {
				collider->onCollision(e);
			}
		});


		domain->forMatchingEntities<Transform, BoxCollider>([](Entity* e, Transform* transform, BoxCollider* collider) {
			if( !collider->enabled ) return;
			double offsetLength = sqrt(collider->xOffset * collider->xOffset + collider->yOffset * collider->yOffset);
			double diagonal = sqrt(collider->width * collider->width + collider->height * collider->height);
			typeMap[collider->type].emplace_back(e, transform, collider, diagonal/2.0 + offsetLength);
		});
		
		// Check collisions

		// Player - Debris
		checkCollisions(typeMap[ColliderTypes::PLAYER], typeMap[ColliderTypes::DEBRIS], [domain](Entity* player, Entity* debris) {
			auto debrisHealth = debris->getComponent<Health>();
			
			if( debrisHealth->amount > 0.0 ) {
				auto playerHealth = player->getComponent<Health>();
				auto debrisTransform = debris->getComponent<Transform>();
				playerHealth->amount -= debrisHealth->amount;
				debrisHealth->kill();
				Objects::Effects::createExplosion(domain, debrisTransform->x, debrisTransform->y, 40);
			}
		});

		// Player - Collectibles
		// Player - Enemies

		// Player Missiles - Debris
		checkCollisions(typeMap[ColliderTypes::PLAYER_MISSILE], typeMap[ColliderTypes::DEBRIS], [&domain](Entity* missile, Entity* debris) {
			auto missileTransform = missile->getComponent<Transform>();
			debris->getComponent<Health>()->amount -= missile->getComponent<DamageLoad>()->amount;
			missile->getComponent<BoxCollider>()->enabled = false;
			domain->destroyEntity(missile);
			Objects::Effects::createExplosion(domain, missileTransform->x, missileTransform->y, 20);
		});
		

		// Missiles - Enemies
		checkCollisions(typeMap[ColliderTypes::PLAYER_MISSILE], typeMap[ColliderTypes::ENEMY], [&domain](Entity* missile, Entity* enemy) {
			auto missileTransform = missile->getComponent<Transform>();
			enemy->getComponent<Health>()->amount -= missile->getComponent<DamageLoad>()->amount;
			missile->getComponent<BoxCollider>()->enabled = false;
			domain->destroyEntity(missile);
			Objects::Effects::createExplosion(domain, missileTransform->x, missileTransform->y, 20);
		});


		// Rockets (both player and enemies, as rocket logic is bound to the entity)
		checkCollisions(typeMap[ColliderTypes::ROCKET], typeMap[ColliderTypes::DEBRIS], [domain](Entity* rocket, Entity* debris){
			rocket->getComponent<Health>()->kill();
		});


		// Rockets (both player and enemies, as rocket logic is bound to the entity)
		checkCollisions(typeMap[ColliderTypes::ROCKET], typeMap[ColliderTypes::ENEMY], [domain](Entity* rocket, Entity* debris) {
			rocket->getComponent<Health>()->kill();
		});


		// Enemy Missiles - Player
		checkCollisions(typeMap[ColliderTypes::ENEMY_MISSILE], typeMap[ColliderTypes::PLAYER], [&domain](Entity* missile, Entity* player) {
			auto missileTransform = missile->getComponent<Transform>();
			player->getComponent<Health>()->amount -= missile->getComponent<DamageLoad>()->amount;
			missile->getComponent<BoxCollider>()->enabled = false;
			domain->destroyEntity(missile);
			Objects::Effects::createExplosion(domain, missileTransform->x, missileTransform->y, 20);
		});

	
		// Emissiles - Debris
		
	}

};
