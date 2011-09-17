#include "trax.hpp"
#include "image.h"

// #include "color.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void Image::set(int i, int j, Color result) {
  storef(result.red(), (start_fb + ( j * xres) + i) * 2, 0);
  storef(result.green(), (start_fb + ( j * xres) + i) * 2, 1);
  storef(result.blue(), (start_fb + ( j * xres) + i) * 2, 2);
}