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
	
	bool flag = false; //this is kinda lame
	
	float Kd, Ka, ulen, aspect_ratio;
	Kd = .7f;
	Ka = .3f;
	ulen = 0.194f;
	aspect_ratio = 1.f;
	
	Color mat1(0.1f, 0.3f, 0.9f);
	Color mat2(1.f, 0.2f, 0.2f);
	Color mat3(1.f, 0.9f, 0.1f);
	Color mat4(.4f, .4f, .7f);
	Color background(0.5f, 0.8f, 0.9f);
	Color ambient(.6f, .1f, .1f);
	Color light_colors[2];
	Color result;
	light_colors[0](.7f, .9f, .9f);
	light_colors[1](.6f, .1f, .1f);
	
	Material material1(mat1, Kd, Ka);
	Material material2(mat2, Kd, Ka);
	Material material3(mat3, Kd, Ka);
	Material material4(mat4, Kd, Ka);
	
	Vector E(-24.f, -2.f, 5.2f);
	Vector Up(0.f, 0.f, 1.f);
	Vector Lookat(1.f, 1.f, 2.4f);
	Vector light_positions[2];
	light_positions[0](-30.f, -20.f, 80.f);
	light_positions[1](-20.f, -50.f, 40.f);
	
	//have an array of spheres
	Sphere spheres[4];
	spheres[0](1.5f, 3.5f, 4.f, 2.4f, material1);
	spheres[1](-0.5, -1.5, 2.f, 1.8f, material2);
	spheres[2](0.5f, 1.0f, 1.f, 1.f, material3);
	spheres[3](0.5f, 1.0f, -100.f, 100.f, material4);
	
	Image image(xres, yres, start_fb);
	
	PinHoleCamera camera(E, Lookat, Up, aspect_ratio, ulen);
	
	Ray ray;
	
	PointLight lights[2];
	lights[0](light_positions[0], light_colors[0]);
	lights[1](light_positions[1], light_colors[1]);
	
	for(int pix = atomicinc(0); pix < xres*yres; pix = atomicinc(0))
	{
		int i = pix / xres;
		int j = pix % xres;
		float x = (float)(2.0f * (j - xres/2.0f + 0.5f)/xres);
		float y = (float)(2.0f * (i - yres/2.0f + 0.5f)/yres);
		camera.make_ray(ray, x, y);
		for (int k = 0; k < sizeof(spheres); k++) {
			if spheres[i].intersect(ray) {
				flag = true;
				result = spheres[i].lambertian_shader(ray, lights, sphere[i].get_intersection(), ambient); //add parameters and the method to get the intersection
			}
		}
		
		if (flag == false)
			result = background;
		
		image.set(i, j, result);
	}
	trax_cleanup();
}


