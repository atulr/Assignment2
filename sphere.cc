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
	return material.Ka();
}

float Sphere::Kd(){
	return material.Kd();
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
	xnorm = (float)(intersection.getx() - x);
	ynorm = (float)(intersection.gety() - y);
	znorm = (float)(intersection.getz() - z);
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
	b = (float)2* oprime.dot(ray.get_direction());
	c = (float)oprime.dot(oprime) - (radius * radius);
	if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
		return true;
	else
		return false;
}

bool Sphere::intersects(Ray ray, Sphere other_spheres[]) {
	float a, b, c;
	Vector oprime;
	for(int i = 0; i < 4; i++) {
		Vector center(other_spheres[i].x, other_spheres[i].y, other_spheres[i].z);
		oprime = ray.get_origin().sub(center);
		a = ray.get_direction().dot(ray.get_direction());
		b = (float)2* oprime.dot(ray.get_direction());
		c = (float)oprime.dot(oprime) - (other_spheres[i].radius * other_spheres[i].radius);
		if (discriminant(a,b,c) > 0.0001f) // hard coded epsilon value
			return true;
	}
	return false;
}

Color Sphere::lambertian_shader(Ray ray, PointLight lights[], Vector intersection, Color ambient_light, Sphere other_spheres[]){
	float costheta, cosphi, distance;
	Vector normal;
	normal = normal_to_sphere(intersection).normalize();
	Ray ray_to_light_source;
	Vector L, Ln;
	Color light, result, point_light_color;
	light = ambient_light.times(Ka());
	costheta = normal.dot(intersection.sub(ray.get_direction()));
	if (costheta > 0.0f)
		normal = normal.scmult(-1.f);

	for (int i=0; i < 2; i++){ //set L. find some way to find the length of object array
		point_light_color = lights[i].get_color();
		
		L = lights[i].get_position().sub(intersection);
		Ln = L.normalize();
		cosphi = normal.dot(Ln);
		ray_to_light_source.set_origin(intersection);
		ray_to_light_source.set_direction(lights[i].get_position());
		if (cosphi > 0.f) {
			if (!intersects (ray_to_light_source, other_spheres)) {
				light = light.add(point_light_color.times((float)(Kd() * cosphi)));
			}else {
				//it's a shadow with ambient lighting :D:D:D
			}
		}
	}
	result = light.times(surface_color());
	return result;
}