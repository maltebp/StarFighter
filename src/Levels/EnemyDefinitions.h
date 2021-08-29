#pragma once

#include "General.h"
#include "Components/BoundaryBounce.h"

#include "Utility/Math.h"

using namespace River::ECS;

#include "Enemy.h"

const EnemyCreationData TEST_ENEMY =  {
	.width = 60,
	.height = 60,

	.texture = GlobalAssets::Textures::UFO_RED,
	
	.spawnVelocity = 2.5,
	.health = 1000,

	.onInit = [](Entity* e){
		LOG("Enemy finished spawning");
		 
		auto transform = e->getComponent<Transform>();
		auto move = e->getComponent<Move>();

		auto rotationRadians = DEG_TO_RADIANS(transform->rotation);
		move->velocityX = cos(rotationRadians) * 2.5;
		move->velocityY = sin(rotationRadians) * 2.5;
		move->rotationVelocity = 10;

		e->addComponent<BoundaryBounce>();
	},

	.onDeath = [](Entity* e) {
		return true;
	}
};