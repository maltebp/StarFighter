#pragma once

#include "General.h"

#include "Levels/LevelData.h"

#include "Components/Timer.h"


using namespace River::ECS;


class Level1 : public LevelData {
public:
	 
	using LevelData::LevelData;

	void onStart() override {
		LOG("Started level 1!");

		{

			auto spawnTimer = domain->createEntity();
			auto timer = spawnTimer->addComponent<Timer>();
			timer->periodic = true;
			timer->time = 4.0;
			timer->onFinish = [this](Entity* e) {  
				LOG("Spawning enemy");
				spawnEnemy(domain, TEST_ENEMY, 500, -280);
			};

			
		}
		
		// Spawn timer
	}


};