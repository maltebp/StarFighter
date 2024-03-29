#pragma once

#include "River/Vendor/RiverECS/ECS.h"

#include "Texture.h"
#include "River/Primitives/Color.h"

namespace River::ECS {

	/**
	 * @brief	Component which contains information about drawing a texture to the screen.
     *			It doesn't contain a position, as this should be defined externally.
	*/
	struct Sprite : Component {

		const Texture* texture = nullptr;

		/**
		 * @brief	How many degrees the sprite should be rotated relative to the Transform position.
		 *			This rotation is performed before translating the offset
		*/
		double rotationOffset = 0;

		/**
		 * @brief	Where the sprite should be drawn relative to the transform position
		*/
		double xOffset, yOffset;
		float opacity = 1.0;
		Color tint;
		// Tint mode?

		bool isPartiallyTransparent() const {
			return texture->isPartiallyTransparent() || (opacity > 0.0 && opacity < 1.0);
		}
	};

}