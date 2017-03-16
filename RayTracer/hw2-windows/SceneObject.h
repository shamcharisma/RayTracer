#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Ray.h"
#include "Color.h"

class SceneObject {
public:
	Color color;

public:
	SceneObject::SceneObject() {
		color = Color(0, 0, 0, 0);
	}

	virtual Color getColor() {
		return color;
	}
	
	virtual double FindIntersection(Ray ray) {
		return 0;
	}
};


#endif