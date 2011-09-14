#include "trax.hpp"
#include "pin_hole_camera.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void PinHoleCamera::make_ray(Ray &ray, float x, float y) {
	ray.set_origin(look_at_point);
	Vector direction;
	
}