#include "trax.hpp"
#include "sphere.h"
// #include "ray.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif
//change this method
bool Sphere::intersects(Ray ray) {
	float a, b, c;
	Vector center(x,y,z);
	Vector oprime;
	oprime = ray.return_origin().sub(center);
	a = ray.return_direction().dot(ray.return_direction());
	b = (float)2* oprime.dot(center);
	c = (float)oprime.dot(oprime) - (radius * radius);
	if (discriminant(a,b,c) > 0)		
		return true;
	else
		return false;
}

Color Sphere::lambertian_shader(Ray ray, PointLight lights, Vector intersection, Color ambient_light){
	float costheta, cosphi, distance, t;
	Vector normal = normal(intersection).normalize();
	Vector L, Ln;
	Color light, result; // add color to light
	light = ambient_light.times(Ka);
	t = discriminant(); //check this
	costheta = normal.dot(ray.get_direction());
	if (costheta < 0.0f)
		normal = -normal;
	for (int i=0; i < sizeof(lights), i++){
		point_light_color = lights[i].get_color();
		distance = L.length();
		Ln = L.normalize();
		cosphi = normal.dot(Ln)
		if (cosphi > 0){
			if (!intersects(0 < t < distance)) { //some condition 
				light += point_light_color.times(Kd * cosphi)
			}else {
				//it's a shadow with ambient lighting :D:D:D
			}
		}
	}
	result = light * surface_color();//add surface_color method
	return result;
}