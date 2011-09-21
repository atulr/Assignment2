#include "trax.hpp"
#include "color.h"

// Only include stdio for printf on the non-trax version
#if TRAX==0
#include <stdio.h>
#endif

float Color::red(){
	return r;
}

float Color::green(){
	return g;
}

float Color::blue(){
	return b;
}

Color Color::times(Color color){
	float newr, newg, newb;
	newr = (float)(color.r * r);
	newg = (float)(color.g * g);
	newb = (float)(color.b * b);
	Color new_color(newr, newg, newb);
	return new_color;
}

Color Color::times(float scalar){
	float newr, newg, newb;
	newr = (float)(r * scalar);
	newg = (float)(g * scalar);
	newb = (float)(b * scalar);
	Color new_color(newr, newg, newb);
	return new_color;
}


Color Color::add(Color color){
	float newr, newg, newb;
	newr = (float)(color.r + r);
	newg = (float)(color.g + g);
	newb = (float)(color.b + b);
	Color new_color(newr, newg, newb);
	return new_color;
}

void Color::add_modify(Color color) {
	r = color.r + r;
   	g = color.g + g;
    b = color.b + b;
}
Color Color::sub(Color color){
	float newr, newg, newb;
	newr = (float)(color.r - r);
	newg = (float)(color.g - g);
	newb = (float)(color.b - b);
	Color new_color(newr, newg, newb);
	return new_color;
}