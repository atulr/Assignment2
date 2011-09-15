#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector {
	float x,y,z;
public:
	Vector(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	Vector(float x1, float y1, float z1) {
		x = x1;
		y = y1;
		z = z1;
	}
	float getx() {return x;}
	float gety() {return y;}
	float getz() {return z;}
	float dot(Vector other);
	Vector normalize();
	Vector cross(Vector other);
	Vector add(Vector other);
	Vector sub(Vector other);
	Vector scmult(float scalar);
	float length();
	
};
#endif