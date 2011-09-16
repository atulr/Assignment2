#include "trax.hpp"
#include "pin_hole_camera.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void PinHoleCamera::make_ray(Ray &ray, float x, float y) {
	ray.set_origin(position);
	Vector direction, L, ln, utmp, vtmp, V, u, v;
	L = look_at_point.sub(position);
	ln = L.normalize();
	utmp = ln.cross(up);
	vtmp = utmp.cross(ln);
	u = (utmp.normalize().scmult((float)tan(ulen/2)));
	v = (vtmp.normalize().scmult((float)(tan(ulen/2)/ aspect_ratio)));
	V = ln.add(u.scmult(x).add(v.scmult(y)));
	ray.set_direction(V);
}