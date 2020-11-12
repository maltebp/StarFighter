#pragma once


#include <math.h>

#include <River.h>

#include "Log.h"

#include "Objects/Debris.h"
#include "Objects/Player.h"

#include "Systems/CollisionSystem.h"
#include "Systems/TargetSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/TimedLifeSystem.h"


using namespace River::ECS;


Entity* createMouseBlock(Domain* domain) {
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


class Level {
public:

	Level(River::Layer* parentLayer) {
		objectDomain = new Domain();
		camera = new River::Camera(1280, 720);
		camera->setPosition(0, 0, 0);

		primaryLayer = parentLayer->pushLayer();
		backgroundLayer = primaryLayer->pushLayer();

		objectLayer = primaryLayer->pushLayer();
		objectLayer->onCreate([this]() {

			{	// Create mouse entity
				mouse = objectDomain->createEntity();
				auto transform = mouse->addComponent<Transform>();
				transform->x = 0;
				transform->y = 0;
			}

			player = Objects::Player::create(objectDomain, mouse);


			Objects::Debris::createMeteor(objectDomain, -100, -100, 30);
			Objects::Debris::createMeteor(objectDomain,  100,  100, 30);
			Objects::Debris::createMeteor(objectDomain, -100,  100, 30);
			Objects::Debris::createMeteor(objectDomain,  100, -100, 30);
			Objects::Debris::createMeteor(objectDomain,   90,   -40, 30);
			Objects::Debris::createMeteor(objectDomain,  -25,  150, 30);
			Objects::Debris::createMeteor(objectDomain,    0, -100, 30);
			
		});


		objectLayer->onUpdate([this]() {
			objectDomain->clean();   

			if( playerFireCooldown > 0 )
				playerFireCooldown -= 0.01;

			

			LOG("FPS: " << River::Game::getFps() << "  Entities: " << objectDomain->getNumEntities());

			//LOG(getAngle(mouseX, mouseY));


			//LOG("Radians: " << rotationRadians);
			//LOG("Degrees: " << playerSprite->rotation);

			auto playerMove = player->getComponent<Move>();
			/*playerMove->velocityX = (mouseX - playerTransform->x) / 25;
			playerMove->velocityY = (mouseY - playerTransform->y) / 25;*/

			TargetSystem::update(objectDomain);
			MovementSystem::update(objectDomain);
			CollisionSystem::update(objectDomain);
			HealthSystem::update(objectDomain);
			TimedLifeSystem::update(objectDomain);
			River::SpriteRenderingSystem::render(camera, *objectDomain);
		});

		objectLayer->onMouseMoveEvent([this](River::MouseMoveEvent& e) {
			auto transform = mouse->getComponent<Transform>();
			transform->x = e.positionX;
			transform->y = e.positionY;
		});


		objectLayer->onKeyEvent([this](River::KeyEvent& e) {
			if( e.key == River::Key::SPACE ) {
				if( e.action == River::KeyEvent::Action::PRESSED ) {
					auto move = player->getComponent<Move>();
					auto transform = player->getComponent<Transform>();
					auto rotationRadians = DEG_TO_RADIANS(transform->rotation);
					move->accelerationX = cos(rotationRadians) * 0.6;
					move->accelerationY = sin(rotationRadians) * 0.6;
				}else
				if( e.action == River::KeyEvent::Action::UP ) {
					auto move = player->getComponent<Move>();
					move->accelerationX = 0;
					move->accelerationY = 0;
				}
			}
		});

		objectLayer->onMouseButtonEvent([this](River::MouseButtonEvent& e) {
			if( e.button == River::MouseButtons::LEFT ) {
				if( e.action == River::MouseButtonAction::PRESSED ) {
					if( playerFireCooldown <= 0 ) {
						Objects::Player::createMissile(objectDomain, player);
						playerFireCooldown += 0.05;
						LOG("FIRE!");
					}
				}
			}
		});

	}



private:

	double playerFireCooldown = 0.0;

	River::Layer* primaryLayer;
	River::Layer* backgroundLayer;
	River::Layer* objectLayer;

	Domain* objectDomain;

	Entity* player;

	Entity* mouse;

	River::Camera* camera;

};