#include "trax.hpp"
#include "ray.h"
// #include "vector.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void Ray::set_origin(Vector new_origin) {
	origin = new_origin;
}

void Ray::set_direction(Vector new_direction) {
	direction = new_direction;
}

Vector Ray::get_origin(){
	return origin;
}

Vector Ray::get_direction(){
	return direction;
}
