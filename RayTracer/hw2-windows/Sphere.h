#ifndef _SPHERE_H
#define _SPHERE_H

#include <math.h>

#include "SceneObject.h"

class Sphere : public SceneObject {
public:
	Vector center;
	double radius;
	Color color;

public:
	Sphere::Sphere() {
		center = Vector(0, 0, 0);
		radius = 1.0;
		color = Color(0.5, 0.5, 0.5, 0);
	}

	Sphere::Sphere(Vector cen, double rad, Color col) {
		center = cen;
		radius = rad;
		color = col;
	}

	virtual Color getColor() {
		return color;
	}

	//http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html#glas90
	virtual double FindIntersection(Ray ray) {
		Vector intersectedRay = Vector(center.x - ray.origin.x, center.y - ray.origin.y, center.z - ray.origin.z);
		double v = intersectedRay.DotProduct(ray.direction);
		double disc = (radius * radius) - ((intersectedRay.DotProduct(intersectedRay)) - (v * v));

		// no intersection
		if (disc < 0)
		{
			return -1;
		}
		double d = sqrt(disc);
		return (v - d);
	}


	Vector GetNormalAt(Vector point)
	{
		return point.Add(center.Negative()).Normalize();
	}
};


#endif;