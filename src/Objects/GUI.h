#pragma once

#include <River.h>

#include <functional>

#include "General.h"

namespace Objects::GUI {

	using namespace River::ECS;


	Entity* createText(Domain* domain, const std::string& text, River::Font* font, unsigned int size, Color color, double x, double y) {
		auto entity = domain->createEntity();

		auto transform = entity->addComponent<Transform>();
		transform->x = x;
		transform->y = y;

			
		auto textComp = entity->addComponent<Text>();
		textComp->font = GlobalAssets::Fonts::PRIMARY;
		textComp->text = text;
		textComp->size = size;
		textComp->color = color;	
	
		return entity;
	}



	class Selectable {
	public:
		virtual void focus(bool toggle) = 0;
		virtual void select() = 0;
	};


	class Menu {
	public:

		~Menu() {
			for( auto item : items )
				delete item;
		}

		/**
		 * @brief	They are automatically deleted, when the Menu is deleted
		*/
		template <typename ... Item>
		void addItems(Item* ... newItems) {
			static_assert( (std::is_convertible<Item*, Selectable*>::value && ... && true), "Item must inherit publicly from Selectable");

			bool first = items.size() == 0;

			( items.push_back(newItems), ...);
			
			if( first )
				focusNext();
		}


		void focusPrevious() {
			if( items.size() == 0 ) throw new River::InvalidStateException("Menu has no items");
			int oldIndex = currentIndex;
			if( --currentIndex < 0 ) currentIndex = items.size()-1;

			if( oldIndex != currentIndex ) {
				if( oldIndex >= 0 ) items[oldIndex]->focus(false);
				items[currentIndex]->focus(true);
			}
		}


		void focusNext() {
			if( items.size() == 0 ) throw new River::InvalidStateException("Menu has no items");
			int oldIndex = currentIndex;
			currentIndex = (currentIndex+1) % (int)items.size();

			if( oldIndex != currentIndex ) {
				if( oldIndex >= 0 ) items[oldIndex]->focus(false);
				items[currentIndex]->focus(true);
			}
		}

		
		void select() {
			if( items.size() == 0 ) throw new River::InvalidStateException("Menu has no items");
			items[currentIndex]->select();
		}


	private:

		int currentIndex = -1;

		std::vector<Selectable*> items;

	};


	
	class SelectableText : public Selectable {
	public:


		SelectableText(Domain* domain, const std::string& text, unsigned int size, River::Color color, int x, int y, std::function<void(SelectableText*)> onSelect ) {
			this->normalSize = size;
			this->onSelect = onSelect;
			
			entity = domain->createEntity();

			auto transform = entity->addComponent<Transform>();
			transform->x = x;
			transform->y = y;

			
			auto textComp = entity->addComponent<Text>();
			textComp->font = GlobalAssets::Fonts::PRIMARY;
			textComp->text = text;
			textComp->size = size;
			textComp->color = color;		
		}


		void focus(bool toggle) override {
			focused = toggle;
			entity->getComponent<Text>()->size = toggle ? normalSize * 1.25 : normalSize;
		}


		void select() override {
			onSelect(this);
		}



	private:
		std::function<void(SelectableText*)> onSelect = nullptr;
		Entity* entity = nullptr;
		bool focused = false;;

		unsigned normalSize = 0;
	};

}

