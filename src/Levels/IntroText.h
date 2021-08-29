#pragma once

#include <functional>

#include "General.h"
#include "Objects/Text.h"

class IntroText : public River::Layer {
public:

	IntroText( const std::string& name ) {
		this->name = name;
	}


protected:
	
	void onCreate() override {
		LOG("Intro create");
		Objects::Texts::create(&domain, name, 0, 75, 35, River::Colors::WHITE);
		Objects::Texts::create(&domain, "Press 'space' to start!", 0, -25, 20, River::Colors::WHITE);

		domain.clean();
	}

	void onUpdate() override {
		River::TextRenderingSystem::render(&domain, &camera);
	}
	
	void onKeyEvent(River::KeyEvent& e) override {
		if( e.key == River::Key::SPACE && e.action == River::KeyEvent::Action::DOWN ) {
			onStart();
			e.consume();
		}
	}

	
public:
	std::function<void()> onStart;

private:
	River::Camera camera = River::Camera(1280, 720);
	std::string name;
	River::ECS::Domain domain;
};