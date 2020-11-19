#include <iostream>

#include <River.h>

#include "Systems/CollisionSystem.h"

#include "GlobalAssets.h"
#include "Levels/Level.h"




River::Layer* primaryLayer = nullptr;

namespace Domains {
	River::ECS::Domain* domain;
}


void setup() {
	
}



void update() {


}



int main(){

	River::Game::setTitle("Star Fighter");
	River::Game::setWindowSize(1280, 720);
	River::Game::setClearColor(River::Colors::BLACK);

	River::Game::start([]() {

		std::cout << "Loading global assets... "; std::cout.flush();
		GlobalAssets::COLLECTION->load();
		std::cout << "Done!" << std::endl;

		std::cout << "Initializing systems... "; std::cout.flush();
		River::TextRenderingSystem::initialize(River::Game::getWindow());
		River::SpriteRenderingSystem::initialize(River::Game::getWindow());
		std::cout << "Done!" << std::endl;


		//Domains::domain = new River::ECS::Domain();
		std::cout << "Started game" << std::endl;
		
		primaryLayer = River::Game::pushLayer();
		primaryLayer->onKeyEvent([](River::KeyEvent& e) {
			if( e.key == River::Key::ESCAPE ) River::Game::exit();
		});

		auto level = new Level(primaryLayer);


	});
}