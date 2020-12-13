#pragma once

#include "General.h"

using namespace River::ECS;

class LevelData {
public:

	LevelData(Domain* domain, Entity* player){
		this->domain = domain;
		this->player = player;
	}

	// Construct debris, start enemy timers etc..
	virtual void onStart() {};

	// If you need to update stuff
	virtual void onUpdate() {}


private:
	Domain* domain;
	Entity* player;

};
