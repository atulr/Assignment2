#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "color.h"

class PointLight {
	Vector position;
	Color color;
public:
	PointLight(Vector p, Color k){
		position = p;
		color = k;
	}
	Vector get_position();
	Color get_color();
};

#endif