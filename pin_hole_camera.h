#ifndef __PINHOLECAMERA_H__
#define __PINHOLECAMERA_H__

#include "vector.h"
#include "ray.h"
#include "math.h"

class PinHoleCamera {
	Vector position;
	Vector look_at_point;
	Vector up;
	float aspect_ratio;
	float ulen;
public:
	PinHoleCamera(Vector E, Vector C, Vector U, float ar, float ul){
		position = E;
		look_at_point = C;
		up = U;
		aspect_ratio = ar;
		ulen = ul;
	}
	void make_ray(Ray& ray, float x, float y);
};
#endif