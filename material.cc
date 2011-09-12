#include "trax.hpp"
#include "material.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

Color Material::get_material(){
	return color_of_material;
}

