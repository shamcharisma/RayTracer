#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

class Vector {
public: double x, y, z;
public:
	Vector::Vector() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vector::Vector(double i, double j, double k) {
		x = i;
		y = j;
		z = k;
	}
	
	double Magnitude() {
		return sqrt((x*x) + (y*y) + (z*z));
	}

	Vector Normalize()
	{
		double magnitude = Magnitude();
		return Vector(x / magnitude, y / magnitude, z / magnitude);
	}

	Vector Negative()
	{
		return Vector(-x, -y, -z);
	}

	double DotProduct(Vector vect)
	{
		return (x*vect.x) + (y*vect.y) + (z*vect.z);
	}

	Vector CrossProduct(Vector vect)
	{
		return Vector(
			(y*vect.z - z*vect.y),
			(z*vect.x - x*vect.z),
			(x*vect.y - y*vect.x)
		);
	}

	Vector Add(Vector vect)
	{
		return Vector(x + vect.x, y + vect.y, z + vect.z);
	}

	Vector Subtract(Vector vect)
	{
		return Vector(x - vect.x, y - vect.y, z - vect.z);
	}

	Vector Multiply(double scalar)
	{
		return Vector(x *scalar, y * scalar, z * scalar);
	}
};

#endif // !VECTOR_H

