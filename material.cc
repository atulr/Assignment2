#include "trax.hpp"
#include "material.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

float Material::Ka() {
	return ka;
}

float Material::Kd() {
	return kd;
}

Color Material::get_color() {
	return color_of_material;
}

