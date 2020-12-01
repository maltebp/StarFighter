#pragma once

#include <functional>

#include "General.h"
#include "Objects/Text.h"

class LevelIntro : public River::Layer {
public:

	LevelIntro( const std::string& name, std::function<void(LevelIntro*)> startAction ) {
		this->startAction = startAction;
		this->name = name;
	}


protected:
	

	void onCreate() override {
		LOG("Intro create");
		Objects::Texts::create(&domain, name, 0, 100, 35, River::Colors::WHITE);
		Objects::Texts::create(&domain, "Press 'space' to start!", 0, -50, 20, River::Colors::WHITE);

		domain.clean();
	}

	void onUpdate() override {
		LOG("Intro update");
		River::TextRenderingSystem::render(&domain, &camera);
	}
	
	void onKeyEvent(River::KeyEvent& e) override {
		if( e.key == River::Key::SPACE && e.action == River::KeyEvent::Action::DOWN ) {
			startAction(this);
			e.consume();
		}
	}

	

private:
	River::Camera camera = River::Camera(1280, 720);
	std::string name;
	River::ECS::Domain domain;
	std::function<void(LevelIntro*)> startAction;
};