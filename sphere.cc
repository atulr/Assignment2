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

float Sphere::Ka(){
	return ka;
}

float Sphere::Kd(){
	return kd;
}

float Sphere::get_x() {
	return x;
}

float Sphere::get_y() {
	return y;
}

float Sphere::get_z() {
	return z;
}

Vector Sphere::normal_to_sphere(Vector intersection) {
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
	oprime = ray.get_origin().sub(center);
	a = ray.get_direction().dot(ray.get_direction());
	b = (float)2* oprime.dot(center);
	c = (float)oprime.dot(oprime) - (radius * radius);
	if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
		return true;
	else
		return false;
}

bool Sphere::intersects(Ray ray, Sphere other_spheres[]) {
	float a, b, c;
	Vector oprime;
	for(int i = 0; i < sizeof(other_spheres); i++) {
		Vector center(other_spheres[i].x, other_spheres[i].y, other_spheres[i].z);
		oprime = ray.get_origin().sub(center);
		a = ray.get_direction().dot(ray.get_direction());
		b = (float)2* oprime.dot(center);
		c = (float)oprime.dot(oprime) - (other_spheres[i].radius * other_spheres[i].radius);
		if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
			return true;
	}
	return false;
}

Color Sphere::lambertian_shader(Ray ray, PointLight lights[], Vector intersection, Color ambient_light, Sphere other_spheres[]){
	float costheta, cosphi, distance;
	Vector normal = intersection;
	normal_to_sphere(normal).normalize();
	Ray ray_to_light_source;
	Vector L, Ln, tmp;
	Color light, result, point_light_color;
	light = ambient_light.times(Ka());
	costheta = normal.dot(ray.get_direction());
	if (costheta < 0.0f)
		normal = normal.scmult(-1.f);

	for (int i=0; i < sizeof(lights); i++){
		point_light_color = lights[i].get_color();
		distance = L.length();
		Ln = L.normalize();
		cosphi = normal.dot(Ln);
		ray_to_light_source.set_origin(intersection);
		ray_to_light_source.set_direction(lights[i].get_position());
		if (cosphi > 0) {
			if (!intersects (ray_to_light_source, other_spheres)) {
				light = light.add(point_light_color.times(Kd() * cosphi));
			}else {
				//it's a shadow with ambient lighting :D:D:D
			}
		}
	}
	result = light.times(surface_color());
	return result;
}