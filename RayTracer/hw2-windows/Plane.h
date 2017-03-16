#ifndef _PLANE_H
#define _PLANE_H

#include "SceneObject.h"

class Plane : public SceneObject {
public:
	Vector normal;
	double distance;
	Color color;

public:
	Plane::Plane() {
		normal = Vector(1.0, 0, 0);
		distance = 0.0;
		color = Color(0.5, 0.5, 0.5, 0);
	}

	Plane::Plane(Vector nor, double dis, Color col) {
		normal = nor;
		distance = dis;
		color = col;
	}

	virtual Color getColor() {
		return color;
	}

	Vector getNormal(Vector point) {
		return normal;
	}

	virtual double FindIntersection(Ray ray) {

		Vector rayDirection = ray.direction;
		double a = normal.DotProduct(ray.direction);

		if (a == 0) {
			return -1;
		}
		double b = normal.DotProduct(ray.origin.Add(normal.Multiply(distance).Negative())); 
		return ((-1)*distance*b) / a;
	}
};


#endif;