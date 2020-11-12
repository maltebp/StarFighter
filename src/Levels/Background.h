#pragma once

#include <River.h>

//#include "Assets.h"
#include "Domains.h"


using namespace River::ECS;

class Background {
public:
	


	Background(River::Layer* parentLayer, Domain* domain) {
		primaryLayer = parentLayer->pushLayer();

		backgroundColor = domain->createEntity();
		auto transform = backgroundColor->addComponent<Transform>();
		transform->width = 1280;
		transform->height = 720;

		auto sprite = backgroundColor->addComponent<Sprite>();
		//sprite->texture = Textures::BACKGROUND;


	}
	


private:
	Entity* backgroundColor;



	River::Layer* parentLayer;
	River::Layer* primaryLayer;

};
