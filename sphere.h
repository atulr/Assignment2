#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector.h"
#include "ray.h"
#include "color.h"
#include "material.h"
#include "point_light.h"

class Sphere {
private:
	float x,y,z, radius, kd, ka;
	Material material;
	bool intersects(Ray ray, Sphere spheres[]); //more parameters might be required
	Color surface_color();
	float Ka();
	float Kd();
	float discriminant(float a, float b, float c) {
		float val = (float) (b * b - 4 * a * c);
		return val;
	}
	Vector normal_to_sphere(Vector intersection);
 public:
	Sphere(){}
	Sphere(float x1, float y1, float z1, float r, Material mat){
		x = x1;
		y = y1;
		z = z1;
		radius = r;
		material = mat;
	}
	float get_x();
	float get_y();
	float get_z();
	bool intersects(Ray ray);
	Color lambertian_shader(Ray ray, PointLight lights[], Vector intersection, Color ambient_light, Sphere other_spheres[]);
};

#endif