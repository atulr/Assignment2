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
	
	Vector return_origin() {return origin;}
	Vector return_direction() {return direction;}
};

#endif
