#pragma once

#include "General.h"

using namespace River::ECS;

#include "Enemy.h"

const EnemyCreationData TEST_ENEMY =  {
	.width = 60,
	.height = 60,

	.texture = GlobalAssets::Textures::UFO_RED,
	
	.spawnVelocity = 2.5,

	.onInit = [](Entity* e){
		LOG("Enemy finished spawning");
	}
};