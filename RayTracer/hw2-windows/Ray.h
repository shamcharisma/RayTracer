#ifndef _RAY_H
#define _RAY_H

#include <math.h>

#include "Vector.h"

class Ray {
public:
	Vector origin;
	Vector direction;

public:	
	Ray::Ray() {
		origin = Vector(0.0, 0.0, 0.0);
		direction = Vector(1.0, 0.0, 0.0);
	}

	Ray::Ray(Vector o, Vector d) {
		origin = o;
		direction = d;
	}	
};

#endif // !RAY_H
