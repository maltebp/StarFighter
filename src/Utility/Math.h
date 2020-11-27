#pragma once

#include <cmath>
#include <tuple>

#define PI 3.14159265
#define DEG_TO_RADIANS(x) (x) * PI / 180

namespace Util::Math {

	// Add stuff perhaps?

	/**
	 * @brief	Calculate the angle in degrees of this point relative to the origin. The angle is between 0 and 360, in counter clockwise direction where 0 is towards the x-axis
	*/
	inline double getAngle(double x, double y) {
		if( y > 0 ) return acos(x / sqrt(x * x + y * y)) * 180 / PI;
		return 360 - acos(x / sqrt(x * x + y * y)) * 180 / PI;
	}


	inline std::tuple<double, double> vectorFromAngle(double angle, double magnitude) {
		auto radianAngle = angle * PI / 180;
		return { cos(radianAngle) * magnitude, sin(radianAngle) * magnitude };
	}


	inline double vectorLength(double x, double y) {
		return sqrt(x * x + y * y);
	}

}