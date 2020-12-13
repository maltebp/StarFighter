#pragma once

#include "General.h"

#include "Levels/LevelData.h"

class Level1 : public LevelData {
public:

	using LevelData::LevelData;

	void onStart() override {
		LOG("Started level 1!");
	}

};