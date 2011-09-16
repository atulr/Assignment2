#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector.h"
#include "ray.h"

class Sphere {
private:
	float x,y,z, radius;
	float discriminant(float a, float b, float c) {
		float val = (float) (b * b - 4 * a * c);
		return val;
	}
	Vector normal(Vector intersection){
		float xnorm, ynorm, znorm;
		xnorm = (float)(x - intersection.getx());
		ynorm = (float)(y - intersection.gety());
		znorm = (float)(z - intersection.getz());
		Vector normal(xnorm, ynorm, znorm);
		return normal;
	}
 public:
	Sphere(float x1, float y1, float z1, float r){
		x = x1;
		y = y1;
		z = z1;
		radius = r;
	}
	bool intersects(Ray ray);
	void lambertian_shader();
};

#endif