#include "trax.hpp"
#include "sphere.h"
// #include "ray.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

// bool Sphere::intersects(Ray ray) {
// 	float a, b, c;
// 	Vector center(x,y,z);
// 	Vector oprime;
// 	oprime = ray.return_origin().sub(center);
// 	a = ray.return_direction().dot(ray.return_direction());
// 	b = (float)2* oprime.dot(center);
// 	c = (float)oprime.dot(oprime) - (radius * radius);
// 	if (discriminant(a,b,c) > 0)		
// 		return true;
// 	else
// 		return false;
// }