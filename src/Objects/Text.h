#pragma once

#include <River.h>

#include "GlobalAssets.h"


namespace Objects::Texts {

	using namespace River::ECS;

	inline Entity* create(Domain* domain, const std::string& text, double x, double y) {
		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;

		auto textComp = entity->addComponent<Text>();
		textComp->font = GlobalAssets::Fonts::PRIMARY;
		textComp->color = River::Colors::WHITE;
		textComp->text = text;
		textComp->size = 50;

		return entity;
	}

}