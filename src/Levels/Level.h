#pragma once

#include <River.h>

#include <math.h>

#include "Systems/CollisionSystem.h"
#include "Log.h"
#include "Objects/Player.h"
#include "Systems/MovementSystem.h"

#define PI 3.14159265

using namespace River::ECS;


double getAngle(double x, double y) {
	if( y > 0 ) return acos(x / sqrt(x * x + y * y)) * 180 / PI;
	return 360 - acos(x / sqrt(x * x + y * y)) * 180 / PI;
}


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
			player = Player::create(objectDomain);
			mouseBlock = createMouseBlock(objectDomain);
		});


		objectLayer->onUpdate([this]() {
			objectDomain->clean();   

			{
				auto transform = mouseBlock->getComponent<Transform>();
				transform->x = mouseX;
				transform->y = mouseY;
			}
			
			auto playerTransform = player->getComponent<Transform>();

			auto angleDifference = getAngle(mouseX, mouseY) - playerTransform->rotation;
			
			auto direction = angleDifference > 0 ? 1 : -1;
			
			auto absoluteDifference = angleDifference * direction;

			if( absoluteDifference > 180 )
				direction *= -1;

			auto angleMovement = (5 > absoluteDifference ? absoluteDifference : 5) * direction;
			
			playerTransform->rotation += angleMovement;
			
			// Do "double" modolu
			playerTransform->rotation = ((int) playerTransform->rotation)%360;
			if( playerTransform->rotation < 0 )
				playerTransform->rotation += 360;
			

			auto playerSprite = player->getComponent<Sprite>();

			//auto rotationRadians = getAngle(mouseX, mouseY);// -atan((mouseY - playerTransform->y) / (mouseX - playerTransform->x));


			LOG(River::Game::getFps());

			//LOG(getAngle(mouseX, mouseY));


			//LOG("Radians: " << rotationRadians);
			//LOG("Degrees: " << playerSprite->rotation);

			auto playerMove = player->getComponent<Move>();
			/*playerMove->velocityX = (mouseX - playerTransform->x) / 25;
			playerMove->velocityY = (mouseY - playerTransform->y) / 25;*/

			MovementSystem::update(objectDomain);
			CollisionSystem::update(objectDomain);
			River::SpriteRenderingSystem::render(camera, *objectDomain);
		});

		objectLayer->onMouseMoveEvent([this](River::MouseMoveEvent& e) {
			mouseX = e.positionX;
			mouseY = e.positionY;
			//LOG(mouseX);
			//LOG(mouseY);
		});


	}



private:
	double mouseX = 0;
	double mouseY = 0;

	River::Layer* primaryLayer;
	River::Layer* backgroundLayer;
	River::Layer* objectLayer;

	Domain* objectDomain;

	Entity* player;
	Entity* mouseBlock;

	River::Camera* camera;

};