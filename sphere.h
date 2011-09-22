#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector.h"
#include "ray.h"
#include "color.h"
#include "material.h"
#include "point_light.h"
#include "math.h"

class Sphere {
	float x, y, z, radius;
	Material material;
	bool intersects(Ray ray, Sphere spheres[], float distance); //more parameters might be required
	float closer_point(float a, float b, float c, float disc); //more parameters might be required
	Color surface_color();
	float Ka();
	float Kd();
	float discriminant(float a, float b, float c) {
		float val = (float) (b * b - 4 * a * c);
		return val;
	}
	Vector normal(Vector intersection);	
public:
	Sphere(float xval, float yval, float zval, float r, Material mat) {
		x = xval;
		y = yval;
		z = zval;
		radius = r;
		material = mat;
	}
	float get_x();
	float get_y();
	float get_z();
	float intersects(Ray ray);
	Color lambertian_shader(Ray ray, float t, PointLight lights[], Color ambient_light, Sphere other_spheres[]);
};

#endif