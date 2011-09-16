#include "trax.hpp"
#include "sphere.h"
// #include "ray.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

Color Sphere::surface_color() {
	return material.get_color();
}

Color Sphere::Ka(){
	return ka;
}

Color Sphere::Kd(){
	return kd;
}

Vector Sphere::normal(Vector intersection) {
	float xnorm, ynorm, znorm;
	xnorm = (float)(x - intersection.getx());
	ynorm = (float)(y - intersection.gety());
	znorm = (float)(z - intersection.getz());
	Vector normal(xnorm, ynorm, znorm);
	return normal;
}

//change this method
bool Sphere::intersects(Ray ray) {
	float a, b, c;
	Vector center(x,y,z);
	Vector oprime;
	oprime = ray.return_origin().sub(center);
	a = ray.return_direction().dot(ray.return_direction());
	b = (float)2* oprime.dot(center);
	c = (float)oprime.dot(oprime) - (radius * radius);
	if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
		return true;
	else
		return false;
}

bool Sphere::intersects(Ray ray, Sphere other_spheres[]) {
	float a, b, c;
	Vector center(x,y,z);
	Vector oprime;
	for(int i = 0; i < sizeof(spheres); i++) {
		oprime = ray.return_origin().sub(spheres[i].center);
		a = ray.return_direction().dot(ray.return_direction());
		b = (float)2* oprime.dot(spheres[i].center);
		c = (float)oprime.dot(oprime) - (spheres[i].radius * spheres[i].radius);
		if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
			return true;
	}
	return false;
}

Color Sphere::lambertian_shader(Ray ray, PointLight lights[], Vector intersection, Color ambient_light, Sphere other_spheres[]){
	float costheta, cosphi, distance, t;
	Vector normal = normal(intersection).normalize();
	Ray ray_to_light_source;
	Vector L, Ln;
	Color light, result;
	light = ambient_light.times(Ka());
	costheta = normal.dot(ray.get_direction());
	if (costheta < 0.0f)
		normal = -normal;

	for (int i=0; i < sizeof(lights), i++){
		point_light_color = lights[i].get_color();
		distance = L.length();
		Ln = L.normalize();
		cosphi = normal.dot(Ln)
		if (cosphi > 0){
			if (!intersects(ray_to_light_source(intersection, lights[i].get_position()), other_spheres)) { //some condition 
				light += point_light_color.times(Kd() * cosphi)
			}else {
				//it's a shadow with ambient lighting :D:D:D
			}
		}
	}
	result = light * surface_color();
	return result;
}