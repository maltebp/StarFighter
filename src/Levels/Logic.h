#pragma once

#pragma once


#include <math.h>

#include <River.h>

#include "Log.h"

#include "LevelData.h"
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


template<typename L> // Level data class
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


		{ // Player create
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


	void onMouseMoveEvent(River::MouseMoveEvent& e) override {

		{	// Update mouse entity position
			auto transform = mouse->getComponent<Transform>();
			transform->x = e.positionX;
			transform->y = e.positionY;
		}
	}

		
	void onKeyEvent(River::KeyEvent& e) override {
		if( !controlsEnabled ) return;
		
		
		// SPACE -> Accelerate
		if( e.key == River::Key::SPACE ) {
			if( e.action == River::KeyEvent::Action::PRESSED ) {
				auto move = player->getComponent<Move>();
				auto transform = player->getComponent<Transform>();
				auto rotationRadians = DEG_TO_RADIANS(transform->rotation);
				move->accelerationX = cos(rotationRadians) * 0.6;
				move->accelerationY = sin(rotationRadians) * 0.6;
			
			}else if( e.action == River::KeyEvent::Action::UP ) {
				auto move = player->getComponent<Move>();
				move->accelerationX = 0;
				move->accelerationY = 0;
			}
		}

		if( e.key == River::Key::D ) {
			if( e.action == River::KeyEvent::Action::DOWN ) {
				Objects::Enemy::createUfo(domain, Random::getInt(-600, 600), Random::getInt(-300, 300), Random::getInt(0, 359), 3, 0.75);
			}
		}
	
	}

	// Starts the level
	void start() {

		controlsEnabled = true;
		
		// Activate player components
		player->getComponent<Move>()->resistance = 0.05; // Reset player resistance (value should be same as in Player.h)
		player->getComponent<Target>()-> active = true;

		levelData = new L(domain, player);
		levelData->onStart();

	}


	void onPlayerDeath() {
		LOG("Player died!");
	}


public:
	// Function to call when player is in position
	std::function<void()> onPlayerInPosition = nullptr;


private:
	double playerFireCooldown = 0.0;
	LevelData* levelData;

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

	// Whether or not player has moved into position (starting "animation")
	bool playerInPosition = false;
};

