#pragma once

#include <River.h>

using River::Texture;
using River::Image;

namespace GlobalAssets {

	River::AssetCollection* COLLECTION = new River::AssetCollection();


	namespace Textures {

		Texture* PLAYER = Texture::create(
			Image::create("assets/player.png")
			.setPartiallyTransparent(true)
			.finish()
		, true)
			.setAssetCollection(COLLECTION)
			.finish();


		Texture* SQUARE = Texture::create(Image::create("assets/white_square.png").finish(), true)
			.setAssetCollection(COLLECTION)
			.finish();

		/*const River::Texture* BACKGROUND = new River::Texture(
			"assets/black_background.png", false, 0, 0, 0, 0
		);*/

	}

}






