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
	int start_fb = GetFrameBuffer();
	
	float t = 0.f;
	
	bool flag = false; //this is kinda lame
	
	float Kd, Ka, ulen, aspect_ratio;
	Kd = 0.7f;
	Ka = 0.3f;
	ulen = 0.194f;
	aspect_ratio = 1.f;
	
	Color mat1(0.1f, 0.3f, 0.9f);
	Color mat2(1.f, 0.2f, 0.2f);
	Color mat3(1.f, 0.9f, 0.1f);
	Color mat4(.4f, .4f, .7f);
	Color background(0.5f, 0.8f, 0.9f);
	Color ambient(.6f, .1f, .1f);
	Color light_colors[] = {Color(.7f, .9f, .9f),
	Color(.6f, .1f, .1f)
	};
	Color result;
	
	Material material1(mat1, Kd, Ka);
	Material material2(mat2, Kd, Ka);
	Material material3(mat3, Kd, Ka);
	Material material4(mat4, Kd, Ka);
	
	Vector E(-24.f, -2.f, 5.2f);
	Vector Up(0.f, 0.f, 1.f);
	Vector Lookat(1.f, 1.f, 2.4f);
	Vector light_positions[] = {Vector(-30.f, -20.f, 80.f),
	Vector(-20.f, -50.f, 40.f)
	};
	
	Sphere spheres[] = {Sphere(1.5f, 3.5f, 4.f, 2.4f, material1),
	Sphere(-0.5f, -1.5f, 2.f, 1.8f, material2),
	Sphere(0.5f, 1.0f, 1.f, 1.f, material3),
	Sphere(0.5f, 1.0f, -100.f, 100.f, material4)
	};
	
	Image image(xres, yres, start_fb);
	
	PinHoleCamera camera(E, Lookat, Up, aspect_ratio, ulen);
	
	Ray ray;
	PointLight lights[] = {PointLight(light_positions[0], light_colors[0]),
	PointLight(light_positions[1], light_colors[1])
	};
	for(int pix = atomicinc(0); pix < xres*yres; pix = atomicinc(0)){
		int i = pix / xres;
		int j = pix % xres;
	
		float x = (float)(2.0f * (j - xres/2.0f + 0.5f)/xres);
		float y = (float)(2.0f * (i - yres/2.0f + 0.5f)/yres);
		
		camera.make_ray(ray, x, y);
		for (int k = 0; k < 4; k++) {
			t = spheres[k].intersects(ray);
			if (t > 0.f) {
				flag = true;
				result = spheres[k].lambertian_shader(ray, t, lights, ambient, spheres);
				break;
			}
		}
		if (!flag)
			result = background;
		flag = false; // lame again
		image.set(i, j, result);	
	}
	trax_cleanup();
}
