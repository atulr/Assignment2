#include "trax.hpp"
#include "image.h"

// #include "color.cc"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

void Image::set(int i, int j, Color result) {
  storef(result.red(), start_fb + (( i * xres) + j) * 3, 0);
  storef(result.green(), start_fb + (( i * xres) + j) * 3, 1);
  storef(result.blue(), start_fb + (( i * xres) + j) * 3, 2);
}