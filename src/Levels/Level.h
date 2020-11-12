#pragma once

#include <River.h>

#include <math.h>

#include "Systems/CollisionSystem.h"
#include "Systems/TargetSystem.h"
#include "Log.h"
#include "Objects/Player.h"
#include "Systems/MovementSystem.h"


using namespace River::ECS;

#define DEG_TO_RADIANS(x) (x) * 3.14159265 / 180

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

			player = Player::create(objectDomain, mouse);
			
		});


		objectLayer->onUpdate([this]() {
			objectDomain->clean();   
			

			//LOG(River::Game::getFps());

			//LOG(getAngle(mouseX, mouseY));


			//LOG("Radians: " << rotationRadians);
			//LOG("Degrees: " << playerSprite->rotation);

			auto playerMove = player->getComponent<Move>();
			/*playerMove->velocityX = (mouseX - playerTransform->x) / 25;
			playerMove->velocityY = (mouseY - playerTransform->y) / 25;*/

			TargetSystem::update(objectDomain);
			MovementSystem::update(objectDomain);
			CollisionSystem::update(objectDomain);
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


	}



private:

	River::Layer* primaryLayer;
	River::Layer* backgroundLayer;
	River::Layer* objectLayer;

	Domain* objectDomain;

	Entity* player;

	Entity* mouse;

	River::Camera* camera;

};