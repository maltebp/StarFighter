#pragma once

#pragma once


#include <math.h>

#include <River.h>

#include "Log.h"

#include "IntroText.h"

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


using namespace River::ECS;


class MainMenu;


// Used to create invisible borders around the map, for the player and missiles to
// crash in to
inline Entity* createBoundary(Domain* domain, double width, double height, double centerX, double centerY) {
	auto entity = domain->createEntity();

	auto transform = entity->addComponent<Transform>();
	transform->width = width;
	transform->height = height;
	transform->x = centerX;
	transform->y = centerY;

	auto collider = entity->addComponent<BoxCollider>();
	collider->width = width;
	collider->height = height;
	collider->type = ColliderTypes::IMPENETRABLE;
	
	return entity;
}


inline Entity* createMouseBlock(Domain* domain) {
	auto entity = domain->createEntity();
	auto transform = entity->addComponent<Transform>();
	transform->width = 50;
	transform->height = 50;

	auto sprite = entity->addComponent<Sprite>();
	sprite->texture = GlobalAssets::Textures::SQUARE;

	auto boxCollider = entity->addComponent<BoxCollider>();
	boxCollider->width = 50;
	boxCollider->height = 50;
	boxCollider->type = ColliderTypes::DEBRIS;
	boxCollider->xOffset = 0;
	boxCollider->yOffset = 0;
	boxCollider->enabled = true;

	return entity;
}



class Logic : public River::Layer {
public:

	Logic() {
		domain = new Domain();
		camera = new River::Camera(1280, 720);
		camera->setPosition(0, 0, 0);
	}


	void onCreate() override {

		{	// Create mouzuse entity
			mouse = domain->createEntity();
			auto transform = mouse->addComponent<Transform>();
			transform->x = 0;
			transform->y = 0;
		}


		{
			player = Objects::Player::create(domain, mouse, [this](auto e){ this->onPlayerDeath(); });
			auto transform = player->getComponent<Transform>();
			transform->x = 0;
			transform->y = -800; 
			transform->rotation = 90;

			auto movement = player->getComponent<Move>();
			movement->resistance = 0;
			movement->velocityX = 0;
			movement->velocityY = 5;

			player->getComponent<Target>()->active = false;
		}	

		////Objects::Texts::create(objectDomain, "Hello World!", 0, 0);

		//Objects::Debris::createMeteor(domain, -100, -100, 30);
		//Objects::Debris::createMeteor(domain,  100,  100, 30);
		//Objects::Debris::createMeteor(domain, -100,  100, 30);
		//Objects::Debris::createMeteor(domain,  100, -100, 30);
		//Objects::Debris::createMeteor(domain,   90,   -40, 30);
		//Objects::Debris::createMeteor(domain,  -25,  150, 30);
		//Objects::Debris::createMeteor(domain,    0, -100, 30);

		//// Create impenetrable boundaries
		//createBoundary(domain, 2000, 2000, -1000 - 1280/2.0,				 0 ); // Left
		//createBoundary(domain, 2000, 2000,  1000 + 1280/2.0,				 0 ); // Right
		//createBoundary(domain, 2000, 2000,				0, -1000 - 720/2.0 ); // Top
		//createBoundary(domain, 2000, 2000,				0,  1000 + 720/2.0 ); // Bottom
	}


	void onUpdate() override {
		domain->clean();   

		{ // Player intro movement (sliding in from bottom)
			if( !playerInPosition ) {
				const double TARGET = -150;
				
				auto transform = player->getComponent<Transform>();
				auto movement = player->getComponent<Move>();
				auto targetDistance = TARGET - transform->y;
				if( abs(targetDistance) < 5) {
					onPlayerInPosition();
					playerInPosition = true;
					movement->velocityY = 0;
				} else {
					auto move = player->getComponent<Move>();
					move->velocityY = 0.50 + (targetDistance)/50.0;
				}
			}
			
		}		

		//if( playerFireCooldown > 0 )
			//playerFireCooldown -= 0.01;

		//LOG("FPS: " << River::Game::getFps() << "  Entities: " << domain->getNumEntities());

		FadeSystem::update(domain, 0.016);
		TargetSystem::update(domain);
		MovementSystem::update(domain);
		CollisionSystem::update(domain);
		HealthSystem::update(domain);
		TimerSystem::update(domain, 0.016);
		EnemyFireSystem::update(domain);
		River::SpriteAnimationSystem::update(domain, 0.016);
		River::SpriteRenderingSystem::render(domain, camera);
		River::TextRenderingSystem::render(domain, camera);
	}


	// Starts the level
	void start() {

		// Allow player to fly around
		controlsEnabled = true;



	}


	void onPlayerDeath() {
		LOG("Player died!");
	}


public:
	// Function to call when player is in position
	std::function<void()> onPlayerInPosition = nullptr;


private:
	double playerFireCooldown = 0.0;

	River::Layer* primaryLayer;
	River::Layer* backgroundLayer;
	River::Layer* objectLayer;
	River::Layer* hudLayer;

	IntroText* introText;

	Domain* domain;

	Entity* player;

	Entity* mouse;

	
	River::Camera* camera;

	bool controlsEnabled = true;


	bool playerInPosition = false;
};

