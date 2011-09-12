#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector.h"
#include "ray.h"

class Sphere {
private:
	float x,y,z, radius;
	float discriminant(float a, float b, float c) {
		float val = (float) (b * b - 4*a*c);
		return val;
	}
 public:
	Sphere(float x1, float y1, float z1, float r){
		x = x1;
		y = y1;
		z = z1;
		radius = r;
	}
	bool intersects(Ray ray) {
		float a, b, c;
		Vector center(x,y,z);
		Vector oprime;
		oprime = ray.return_origin().sub(center);
		a = ray.return_direction().dot(ray.return_direction());
		b = (float)(2 * (oprime.dot(ray.return_direction())));
		c = (float)(oprime.dot(oprime) - (radius * radius));
		if (discriminant(a,b,c) > 0.0f)		
			return true;
		else
			return false;
		
	}
};

#endif