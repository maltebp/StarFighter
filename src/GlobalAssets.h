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
				.finish(), true)
			.addToCollection(COLLECTION)
			.finish();


		Texture* SQUARE = Texture::create(Image::create("assets/white_square.png").finish(), true)
			.addToCollection(COLLECTION)
			.finish();


		Texture* LASER_BLUE = Texture::create(
			Image::create("assets/laser_blue.png")
				.setPartiallyTransparent(true)
				.finish(), true)
			.addToCollection(COLLECTION)
			.finish();

		Texture* LASER_RED = Texture::create(
			Image::create("assets/laser_red.png")
			.setPartiallyTransparent(true)
			.finish(), true)
			.addToCollection(COLLECTION)
			.finish();

		Texture* UFO_RED = Texture::create(
			Image::create("assets/ufo_red.png")
			.setPartiallyTransparent(true)
			.finish(), true)
			.addToCollection(COLLECTION)
			.finish();



		Texture* METEOR_BROWN_MEDIUM_1 = Texture::create(
			Image::create("assets/meteor_brown_medium1.png")
				.setPartiallyTransparent(true)	
				.finish(), true)
			.addToCollection(COLLECTION)
			.finish();


		Texture* METEOR_BROWN_TINY_1 = Texture::create(
			Image::create("assets/meteor_brown_tiny1.png")
			.setPartiallyTransparent(true)
			.finish(), true)
			.addToCollection(COLLECTION)
			.finish();





		/*const River::Texture* BACKGROUND = new River::Texture(
			"assets/black_background.png", false, 0, 0, 0, 0
		);*/

	}

}






 