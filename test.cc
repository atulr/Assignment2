#include "trax.hpp"
#include "main.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

int main()
{
	trax_setup();
	int xres = loadi( 0, 1 );
	int yres = loadi( 0, 4 );
	int start_fb = loadi( 0, 7 );
	Sphere sphere1(0.0f, 0.2f, 1.1f, 1.0f);
	Sphere sphere2(1.4f, 1.5f, 1.2f, 1.3f);
	Sphere sphere3(-1.5f, -0.5f, 1.0f, 1.9f);
	Vector origin(0.0f,0.0f,-3.0f);
	Color color1(1.0f, .4f, 1.0f);
	Color color2(.2f, .3f, 1.0f);
	Color color3(1.0f, .3f, .2f);
	Color color4(.2f, .1f, .5f);
	Color result;
	Image image(xres, yres, start_fb);
	
	for(int pix = atomicinc(0); pix < xres*yres; pix = atomicinc(0))
	{
		int i = pix / xres;
		int j = pix % xres;
		float x = (float)(2.0f * (j - xres/2.0f + 0.5f)/xres);
		float y = (float)(2.0f * (i - yres/2.0f + 0.5f)/yres);
		Vector direction(x, y, 1.0f); // this step is probably not required.
		Ray ray(origin, direction); // even this step. Just pass the ray object to make_ray.
		if(sphere1.intersects(ray))
			result = color1;
		else if(sphere2.intersects(ray))
			result = color2;
		else if(sphere3.intersects(ray))
			result = color3;
		else
			result = color4;
		image.set(i, j, result);
	}
	trax_cleanup();
}


