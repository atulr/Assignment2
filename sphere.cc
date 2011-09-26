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

float Sphere::get_x() {
	return x;
}

float Sphere::get_y() {
	return y;
}

float Sphere::get_z() {
	return z;
}

float Sphere::Ka(){
	return material.Ka();
}

float Sphere::Kd(){
	return material.Kd();
}

float Sphere::closer_point(float a, float b, float c, float disc) {
	float t1, t2;
	t1 = (float)((- b + sqrt(disc))/ (2 * a));
	t2 = (float)((- b - sqrt(disc))/ (2 * a));
	if (t1 < t2)
		return t1;
	return t2;
}


Vector Sphere::normal(Vector intersection_point){
	Vector center(x, y, z);
	return (center.sub(intersection_point));
}

float Sphere::intersects(Ray ray) {
	float a, b, c, t, disc;
	Vector center(x,y,z);
	Vector oprime;
	oprime = ray.get_origin().sub(center);
	a = ray.get_direction().dot(ray.get_direction());
	b = (float)2* (oprime.dot(ray.get_direction()));
	c = (float)oprime.dot(oprime) - (radius * radius);
	disc = discriminant(a, b, c);
	if (disc > 0.f) {
		t = closer_point(a, b, c ,disc);
		if (t > 0.0000001f)
			return t ;
	}
	return 0.f;
	
}

bool Sphere::intersects(Ray ray, Sphere other_spheres[], float distance) {
	float a, b, c, t, disc;
	Vector oprime;
	for(int i = 0; i <  4 ; i++) {
		Vector center(other_spheres[i].x, other_spheres[i].y, other_spheres[i].z);
		oprime = ray.get_origin().sub(center);
		a = ray.get_direction().dot(ray.get_direction());
		b = (float)2* (oprime.dot(ray.get_direction()));
		c = (float)oprime.dot(oprime) - (other_spheres[i].radius * other_spheres[i].radius);
		disc = discriminant(a,b,c);
		if (disc > 0.f)
			t = closer_point(a, b, c, disc);
			if ( t < distance && t > 0.0000001f){
				return true;
			}
		}
	return false;
}

Color Sphere::lambertian_shader(Ray ray, float t, PointLight lights[], Color ambient_light, Sphere other_spheres[]) {
	float costheta, cosphi;
	Ray ray_to_light_source;
	Vector hit_position = ray.get_origin().add((ray.get_direction().scmult(t)));
	Vector N = normal(hit_position).normalize();
	costheta = N.dot(ray.get_direction().normalize());
	if (costheta > 0.f)
		N = N.scmult(-1.f);
		
	Color light = ambient_light.times(Ka());
	
	for (int i = 0; i < 2 ; i++) {
		Vector L = lights[i].get_position().sub(hit_position);
		Vector Ln = L.normalize();
		cosphi = N.dot(Ln);
		ray_to_light_source.set_origin(hit_position);
		ray_to_light_source.set_direction(L);
		if (cosphi > 0.f) {
			 if (!intersects(ray_to_light_source, other_spheres, L.length())) {
				light = light.add(lights[i].get_color().times((float)(Kd() * cosphi)));
			 }else{
			 	//it's a shadow with ambient lighting :D:D:D
			 }
		}
	}
	light = light.times(surface_color());
	return light;
}
