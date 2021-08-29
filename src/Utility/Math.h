#pragma once

#include <cmath>
#include <tuple>

#define PI 3.14159265
#define DEG_TO_RADIANS(x) (x) * PI / 180

namespace Util::Math {


	/**
	 * @brief Clamps the angle to the [0-360) (360 excluded) range
	 */
	inline double clampAngle(double angle) {
		double newAngle = fmod(angle, 360);
		if( newAngle < 0 ) newAngle += 360;
		return newAngle;
	}


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



	/**
	 * @brief	Normalizes this vector
	*/
	inline std::tuple<double, double> normalize(double x, double y) {
		double length = sqrt(x*x+y*y);
		return { x / length, y / length };
	}


	inline double vectorLength(double x, double y) {
		return sqrt(x * x + y * y);
	}


	inline double distanceBetweenPoints( double x1, double y1, double x2, double y2 ) {
		return vectorLength(x1-x2, y1-y2);
	}


	/**
	 * @brief	Reverse the angle to clamped angle pointing opposite direction
	*/
	inline double reverseAngle(double angle) {
		return clampAngle(angle+180);
	}

}