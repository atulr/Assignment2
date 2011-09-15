#ifndef __RAY_H__
#define __RAY_H__

#include "vector.h"

class Ray {
private:
	Vector origin;
	Vector direction;
public:
	Ray(Vector point, Vector vector) {
		origin = point;
		direction = vector;
	}
	void set_origin(Vector new_origin);
	Vector return_origin();
	Vector return_direction();
};

#endif
