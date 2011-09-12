#include "trax.hpp"
#include "vector.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

Vector Vector::cross(Vector other) {
	// code for cross product
}

Vector Vector::add(Vector other){
	float x1,y1,z1;
	x1 = (float)(x + other.x);
	y1 = (float)(y + other.y);
	z1 = (float)(z + other.z);
	Vector vector(x1, y1, z1);
	return vector;
}

Vector Vector::sub(Vector other){
	float x1,y1,z1;
	x1 = (float)(x - other.x);
	y1 = (float)(y - other.y);
	z1 = (float)(z - other.z);
	Vector vector(x1, y1, z1);
	return vector;
}

float Vector::dot(Vector other) {
	float product = 0.0f;
	product += (float)(other.x * x);
	product += (float)(other.y * y);
	product += (float)(other.z * z);
	return product;
}

Vector Vector::normalize() {
	float magnitude = length();
	Vector vector((float)x/magnitude, (float)y/magnitude, (float)z/magnitude);
	return vector;
}

float Vector::length (){
	return ((float)sqrt((float)x*x + (float)y*y + (float)z*z));
}