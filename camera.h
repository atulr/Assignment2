#ifndef __CAMERA_H__
#define __CAMERA_H__

// #include "object.h"
// #include "ray.h"

class Camera {
	Vector position;
	Vector look_at_point;
	Vector up;
	float aspect_ratio;
	float ulen;
public:
	Camera(Vector E, Vector C, Vector U, float ar, float ul){
		position = E;
		look_at_point = C;
		up = U;
		aspect_ratio = ar;
		ulen = ul;
	}
	void make_ray(Ray ray, float x, float y);
};
#endif