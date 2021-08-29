#pragma once

#include <River.h>

#include "Levels/Levels/Level1.h"
#include "Levels/Level.h"

#include "Objects/GUI.h"

#include "General.h"


class MainMenu : public River::Layer {
public:



protected:


	void onCreate() override {


		auto title = Objects::GUI::createText(domain, "Star Fighter", GlobalAssets::Fonts::PRIMARY, 100, WHITE, 0, 250);


		auto option1 = new Objects::GUI::SelectableText(domain, "Start", 20, WHITE, 0, 100, [this](Objects::GUI::Selectable* item){
			LOG("Item 1");
			getParent()->removeLayer(this);
			getParent()->pushLayer<Level<Level1>>(1);
		});


		auto option2 = new Objects::GUI::SelectableText(domain, "Menu item 2", 20, WHITE, 0, 0, [](Objects::GUI::Selectable* item){
			
		});

		auto option3 = new Objects::GUI::SelectableText(domain, "Menu item 3", 20, WHITE, 0, -100, [](Objects::GUI::Selectable* item){
			LOG("Item 3");
		});

		menu.addItems(
			option1, option2, option3
		);
	}


	void onUpdate() {
		domain->clean();
		River::TextRenderingSystem::render(domain, camera);
	}


	void onDestroy() override {
		delete domain;
	}


	void onKeyEvent(River::KeyEvent& e) override {
		if( e.action == River::KeyEvent::Action::DOWN ){
			if( e.key == River::Key::DOWN )
				menu.focusNext();
			if( e.key == River::Key::UP )
				menu.focusPrevious();
			if( e.key == River::Key::ENTER )
				menu.select();
		}
	}
	


private:

	Objects::GUI::Menu menu;
	
	River::Camera* camera = new River::Camera(1280, 720);
	River::ECS::Domain* domain = new River::ECS::Domain();

};