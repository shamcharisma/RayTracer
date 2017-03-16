#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vector.h"
#include "Color.h"

class Light {
public:
	Vector position;
    Color color;

public:
	Light::Light() {
		position = Vector(0, 0, 0);
		color = Color(1, 1, 1, 0);
	}

	Light::Light(Vector pos, Color col) {
		position = pos;
		color = col;
	}
};

#endif // !LIGHT_H
