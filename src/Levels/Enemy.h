#pragma once

// Utility
#include "General.h"
#include "Utility/Math.h"

// Components
#include "Components/Move.h"
#include "Components/Target.h"

using namespace River::ECS;


// Data pack for creating an enemy
struct EnemyCreationData {

	double width;
	double height;
	
	// Sprite
	Texture* texture;

	// Collision width and height as a factor of width and height
	double collsionWidth = 1.0;
	double collisionHeight = 1.0;

	// Spawn
	double spawnVelocity;

	// Stats
	double health;
	
	// This might be up for change
	std::function<void(Entity*)> onInit;
};

static std::tuple<double, double> computeSpawnPos(double targetX, double targetY) {

	// TODO: Fix this with correct screen size when that is available
	double screenWidth = 1280;
	double screenHeight = 720;

	double spawnRadius = screenWidth / 2.0 + 50;

	auto [dirX, dirY] = Util::Math::normalize(targetX, targetY);

	// Distance from center that it spawns 
	auto x = dirX * spawnRadius;
	auto y = dirY * spawnRadius;

	// Clamp x and y
	double maxXDistance = screenWidth/2.0 + 75;
	if( x > maxXDistance ) x = maxXDistance;
	if( x < -maxXDistance ) x = -maxXDistance;

	double maxYDistance = screenHeight/2.0 + 75;
	if( y > maxYDistance ) y = maxYDistance;
	if( y < -maxYDistance ) y = -maxYDistance;

	return {x, y};
}



/**
 * @brief	Spawns a new enemy
 * @param domain ..
 * @param data ..
 * @param spawnTargetX	The target x of its spawn procedure
 * @param spawnTargetY	The target y of its spawn procedure
 * @return 
*/
Entity* spawnEnemy(Domain* domain, const EnemyCreationData& data, double spawnTargetX, double spawnTargetY) {

	auto entity = domain->createEntity();

	auto transform = entity->addComponent<Transform>();
	auto [spawnX, spawnY] = computeSpawnPos(spawnTargetX, spawnTargetY);
	transform->x = spawnX;
	transform->y = spawnY;
	transform->width = data.width;
	transform->height = data.height;
	transform->rotation = Util::Math::reverseAngle(Util::Math::getAngle(spawnX, spawnY));

	auto sprite = entity->addComponent<Sprite>();
	sprite->texture = data.texture;
	
	auto move = entity->addComponent<Move>();
	move->velocityX = data.spawnVelocity;
	move->forwardVelocity = true;
	
	auto target = entity->addComponent<Target>();
	target->targetX = spawnTargetX;
	target->targetY = spawnTargetY;
	target->triggerRange = 10;
	target->triggerAction = [&data](Entity* e) {

		// Movement is reset, and should be properly set
		// in the init callback
		auto move = e->getComponent<Move>();
		move->velocityX = 0;
		move->velocityY = 0;
		move->forwardVelocity = false;


		data.onInit(e);
	};

	return entity;
}