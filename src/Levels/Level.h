#pragma once


#include <math.h>

#include <River.h>

#include "Log.h"

#include "IntroText.h"
#include "LevelData.h"

#include "Objects/Debris.h"
#include "Objects/Player.h"
#include "Objects/Enemy.h"
#include "Objects/Text.h"

#include "Systems/CollisionSystem.h"
#include "Systems/TargetSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/TimerSystem.h"
#include "Systems/EnemyFireSystem.h"
#include "Systems/FadeSystem.h"
#include <Levels/Logic.h>

using namespace River::ECS;

template<typename L>
class Level : public River::Layer {
public:


	Level(int levelCount) {
	
		// Display intro text

		// Logic layer
		logic = pushLayer<Logic<L>>();

		logic->onPlayerInPosition = [this, levelCount]() {
			LOG("Player in position");
			introText = pushLayer<IntroText>("Level " + std::to_string(levelCount));
			introText->onStart = [this]() {
				LOG("Starting level");
				removeLayer(introText);
				logic->start();
			};
		};
	}



private:
	Logic<L>* logic;
	IntroText* introText;
	Domain* objectDomain;
};