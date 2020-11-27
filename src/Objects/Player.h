#pragma once

#include "General.h"

#include "Utility/ECS.h"


#include "Components/HomingMove.h"
#include "Components/BoxCollider.h"
#include "Components/Move.h"
#include "Components/Target.h"
#include "Components/Timer.h"

#include "Objects/Effects.h"
#include "Objects/Missile.h"


using namespace River::ECS;


namespace Objects::Player {


	// Constructs a player entity
	Entity* create(Domain* domain, Entity* mouseEntity, std::function<void(Entity* player)> onDeath) {
		auto player = domain->createEntity();

		auto transform = player->addComponent<Transform>();
		transform->width = 50 * GlobalAssets::Textures::PLAYER->getAspectRatio();
		transform->height = 50;
		transform->depth = 10;

		auto sprite = player->addComponent<Sprite>();
		sprite->texture = GlobalAssets::Textures::PLAYER;
		sprite->rotationOffset = 90;

		auto move = player->addComponent<Move>();
		move->resistance = 0.05;

		auto collider = player->addComponent<BoxCollider>();
		collider->width = 40;
		collider->height = 40;
		collider->type = ColliderTypes::PLAYER;

		auto target = player->addComponent<Target>();
		target->targetEntity = mouseEntity;
		target->velocity = 6;

		auto health = player->addComponent<Health>();
		health->amount = Settings::Player::HEALTH;
		health->type = HealthType::PLAYER;
		health->onDeathCallback = [onDeath, domain](Entity* e) {
			auto transform = e->getComponent<Transform>();
			Effects::createShipExplosion(domain, transform->x, transform->y, 80);
			onDeath(e);
			return true;
		};


		return player;
	}


	inline Entity* createMissile(Domain* domain, Entity* player) {
		auto playerTransform = player->getComponent<Transform>();
		
		auto object = Objects::Missile::create(domain, playerTransform->x, playerTransform->y, playerTransform->rotation, 22.0);

		object.sprite->texture = GlobalAssets::Textures::LASER_BLUE;
		object.sprite->rotationOffset = -90;
		
		object.transform->width = 30 * GlobalAssets::Textures::LASER_BLUE->getAspectRatio();
		object.transform->height = 30;

		object.collider->type = ColliderTypes::PLAYER_MISSILE;
		object.collider->width = object.transform->width;
		object.collider->height = object.transform->height;

		object.damage->amount = 30;

		return object.entity;
	}


	inline Entity* createRocket(Domain* domain, Entity* player, double targetX, double targetY) {

		auto playerTransform = player->getComponent<Transform>();

		auto rocket = Objects::Missile::create(domain, playerTransform->x, playerTransform->y, playerTransform->rotation, 12);
		
		rocket.sprite->texture = GlobalAssets::Textures::ROCKET_BLUE;
		rocket.sprite->rotationOffset = -90;

		rocket.transform->width = 25 * GlobalAssets::Textures::ROCKET_BLUE->getAspectRatio();
		rocket.transform->height = 25;

		rocket.collider->type = ColliderTypes::ROCKET;
		rocket.collider->width = rocket.transform->width;
		rocket.collider->height = rocket.transform->height;	

		rocket.move->forwardVelocity = true;

		auto target = rocket.entity->addComponent<Target>();
		target->targetX = targetX;
		target->targetY = targetY;
		target->velocity = 6;

		auto targetCollider = rocket.entity->addComponent<TargetCollider>();
		targetCollider->distance = 10;
		targetCollider->onCollision = [](Entity* e) { e->getComponent<Health>()->amount = 0; };

		auto timer = rocket.entity->addComponent<Timer>();
		timer->active = true;
		timer->time = (360.0 / target->velocity) * 0.016; 
		timer->onFinish = [](Entity* e, Timer* t) { e->getComponent<Target>()->active = false; };

		// Health / On death explosion
		auto health = rocket.entity->addComponent<Health>();
		health->onDeathCallback = [domain, player](Entity* e) {
			auto transform = e->getComponent<Transform>();
			Effects::createExplosion(domain, transform->x, transform->y, 80);
			Util::ECS::forEntitiesInRange(domain, transform->x, transform->y, 50, [domain, player](Entity* e) {
				auto health = e->getComponent<Health>();
				if( health != nullptr && (health->type == HealthType::ENEMY || health->type == HealthType::DEBRIS) )
					// TODO: Add approriate damage here
					health->amount -= 10000;
			});
			return true;
		};

		return rocket.entity;
		

	}
}