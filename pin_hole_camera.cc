#include "trax.hpp"
#include "pin_hole_camera.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void PinHoleCamera::make_ray(Ray& ray, float x, float y) {
	Vector direction, L, ln, utmp, vtmp, V, u, v, normalized_utmp, normalized_vtmp;
	
	L = look_at_point.sub(position);
	ln = L.normalize();
	
	utmp = ln.cross(up);
	
	normalized_utmp = utmp.normalize();
	
	vtmp = normalized_utmp.cross(ln);
	
	normalized_vtmp = vtmp.normalize();
	
	u = normalized_utmp.scmult(tan(ulen));
	v = normalized_vtmp.scmult(tan((float)(ulen)/aspect_ratio));
	V = ln.add((u.scmult(x)).add(v.scmult(y)));
	ray = Ray(position, V);
}