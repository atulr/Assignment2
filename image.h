#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "color.h"
class Image {
	int xres, yres, start_fb;
	public:
		Image(int x, int y, const int& fb){
			xres = x;
			yres = y;
			start_fb = fb;
		}

		void set(int i, int j, Color result);
};

#endif
