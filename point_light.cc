#include "trax.hpp"
#include "point_light.h"

// Only include stdio for printf on the non-trax version

#if TRAX==0
#include <stdio.h>
#endif

Vector PointLight::get_position(){
	return position;
}

Color PointLight::get_color(){
	return color;
}
