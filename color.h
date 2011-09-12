#ifndef __COLOR_H__
#define __COLOR_H__

// #include "object.h"
// #include "ray.h"

class Color {
	float r, g, b;
public:
	Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	};
	Color(float red, float green, float blue){
		r = red;
		g = green;
		b = blue;
	}
	float red();
	float green();
	float blue();
	Color times(Color color);
	Color times(float scalar);
	Color add(Color color);
	Color sub(Color color);
};
#endif