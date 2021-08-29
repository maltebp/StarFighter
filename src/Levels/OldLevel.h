//#pragma once
//
//
//#include <math.h>
//
//#include <River.h>
//
//#include "Log.h"
//
//#include "IntroText.h"
//
//#include "Objects/Debris.h"
//#include "Objects/Player.h"
//#include "Objects/Enemy.h"
//#include "Objects/Text.h"
//
//#include "Systems/CollisionSystem.h"
//#include "Systems/TargetSystem.h"
//#include "Systems/HealthSystem.h"
//#include "Systems/MovementSystem.h"
//#include "Systems/TimerSystem.h"
//#include "Systems/EnemyFireSystem.h"
//#include "Systems/FadeSystem.h"
//
//
//using namespace River::ECS;
//
//
//class MainMenu;
//
//
//// Used to create invisible borders around the map, for the player and missiles to
//// crash in to
//inline Entity* createBoundary(Domain* domain, double width, double height, double centerX, double centerY) {
//	auto entity = domain->createEntity();
//
//	auto transform = entity->addComponent<Transform>();
//	transform->width = width;
//	transform->height = height;
//	transform->x = centerX;
//	transform->y = centerY;
//
//	auto collider = entity->addComponent<BoxCollider>();
//	collider->width = width;
//	collider->height = height;
//	collider->type = ColliderTypes::IMPENETRABLE;
//	
//	return entity;
//}
//
//
//inline Entity* createMouseBlock(Domain* domain) {
//	auto entity = domain->createEntity();
//	auto transform = entity->addComponent<Transform>();
//	transform->width = 50;
//	transform->height = 50;
//
//	auto sprite = entity->addComponent<Sprite>();
//	sprite->texture = GlobalAssets::Textures::SQUARE;
//
//	auto boxCollider = entity->addComponent<BoxCollider>();
//	boxCollider->width = 50;
//	boxCollider->height = 50;
//	boxCollider->type = ColliderTypes::DEBRIS;
//	boxCollider->xOffset = 0;
//	boxCollider->yOffset = 0;
//	boxCollider->enabled = true;
//
//	return entity;
//}
//
//
//
//class Level : public River::Layer {
//public:
//
//
//
//	Level() {
//		
//		// Display intro text
//		introText = pushLayer<IntroText>("Level X", [](auto layer){ LOG("Starting level")});
//
//		objectDomain = new Domain();
//		camera = new River::Camera(1280, 720);
//		camera->setPosition(0, 0, 0);
//
//		objectLayer = pushLayer();
//		objectLayer->onCreate([this]() {
//
//			{	// Create mouzuse entity
//				mouse = objectDomain->createEntity();
//				auto transform = mouse->addComponent<Transform>();
//				transform->x = 0;
//				transform->y = 0;
//			}
//
//			player = Objects::Player::create(objectDomain, mouse, [this](auto player){
//				this->controlsEnabled = false;
//				getParent()->removeLayer(this);
//				getParent()->pushLayer<MainMenu>();
//			});
//
//			//Objects::Texts::create(objectDomain, "Hello World!", 0, 0);
//
//			Objects::Debris::createMeteor(objectDomain, -100, -100, 30);
//			Objects::Debris::createMeteor(objectDomain,  100,  100, 30);
//			Objects::Debris::createMeteor(objectDomain, -100,  100, 30);
//			Objects::Debris::createMeteor(objectDomain,  100, -100, 30);
//			Objects::Debris::createMeteor(objectDomain,   90,   -40, 30);
//			Objects::Debris::createMeteor(objectDomain,  -25,  150, 30);
//			Objects::Debris::createMeteor(objectDomain,    0, -100, 30);
//
//			// Create impenetrable boundaries
//			createBoundary(objectDomain, 2000, 2000, -1000 - 1280/2.0,				 0 ); // Left
//			createBoundary(objectDomain, 2000, 2000,  1000 + 1280/2.0,				 0 ); // Right
//			createBoundary(objectDomain, 2000, 2000,				0, -1000 - 720/2.0 ); // Top
//			createBoundary(objectDomain, 2000, 2000,				0,  1000 + 720/2.0 ); // Bottom
//		});
//
//
//		objectLayer->onUpdate([this]() {
//			objectDomain->clean();   
//
//
//			if( playerFireCooldown > 0 )
//				playerFireCooldown -= 0.01;
//
//			LOG("FPS: " << River::Game::getFps() << "  Entities: " << objectDomain->getNumEntities());
//
//			FadeSystem::update(objectDomain, 0.016);
//			TargetSystem::update(objectDomain);
//			MovementSystem::update(objectDomain);
//			CollisionSystem::update(objectDomain);
//			HealthSystem::update(objectDomain);
//			TimerSystem::update(objectDomain, 0.016);
//			EnemyFireSystem::update(objectDomain);
//			River::SpriteAnimationSystem::update(objectDomain, 0.016);
//			River::SpriteRenderingSystem::render(objectDomain, camera);
//			River::TextRenderingSystem::render(objectDomain, camera);
//		});
//
//		objectLayer->onMouseMoveEvent([this](River::MouseMoveEvent& e) {
//			auto transform = mouse->getComponent<Transform>();
//			transform->x = e.positionX;
//			transform->y = e.positionY;
//		});
//
//
//		objectLayer->onKeyEvent([this](River::KeyEvent& e) {
//			if( !controlsEnabled ) return;
//			if( e.key == River::Key::SPACE ) {
//				if( e.action == River::KeyEvent::Action::PRESSED ) {
//					auto move = player->getComponent<Move>();
//					auto transform = player->getComponent<Transform>();
//					auto rotationRadians = DEG_TO_RADIANS(transform->rotation);
//					move->accelerationX = cos(rotationRadians) * 0.6;
//					move->accelerationY = sin(rotationRadians) * 0.6;
//				}else
//				if( e.action == River::KeyEvent::Action::UP ) {
//					auto move = player->getComponent<Move>();
//					move->accelerationX = 0;
//					move->accelerationY = 0;
//				}
//			}
//
//			if( e.key == River::Key::D ) {
//				if( e.action == River::KeyEvent::Action::DOWN ) {
//					Objects::Enemy::createUfo(objectDomain, Random::getInt(-600, 600), Random::getInt(-300, 300), Random::getInt(0, 359), 3, 0.75);
//				}
//			}
//		});
//
//
//		objectLayer->onMouseButtonEvent([this](River::MouseButtonEvent& e) {
//			if( !controlsEnabled ) return;
//
//			if( e.button == River::MouseButtons::LEFT ) {
//				if( e.action == River::MouseButtonAction::PRESSED ) {
//					if( playerFireCooldown <= 0 ) {
//						Objects::Player::createMissile(objectDomain, player);
//						playerFireCooldown += 0.05;
//					}
//				}
//			}
//			if( e.button == River::MouseButtons::RIGHT ) {
//				if( e.action == River::MouseButtonAction::DOWN ) {
//					auto mouseTransform = mouse->getComponent<Transform>();
//					Objects::Player::createRocket(objectDomain, player, mouseTransform->x, mouseTransform->y);
//				}
//			}
//		});
//
//	}
//
//
//
//private:
//	double playerFireCooldown = 0.0;
//
//	River::Layer* primaryLayer;
//	River::Layer* backgroundLayer;
//	River::Layer* objectLayer;
//	River::Layer* hudLayer;
//
//	IntroText* introText;
//
//	Domain* objectDomain;
//
//	Entity* player;
//
//	Entity* mouse;
//
//	River::Camera* camera;
//
//	bool controlsEnabled = true;
//
//};