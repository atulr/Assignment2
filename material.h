#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Color.h"

class Material {
private:
	Color color_of_material;
	float ka;
	float kd;
public:
	Material() {}
	Material(Color material, float coefficient1, float coefficient2) {
		color_of_material = material;
		ka = coefficient1;
		kd = coefficient2;
	}

	Color get_color();
	float Ka(); 
	float Kd(); 
};

#endif
