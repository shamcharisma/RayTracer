#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector.h"

class Camera {
public:
	Vector cameraPosition;
	Vector cameraDirection;
	Vector cameraRight;
	Vector cameraDown;

public:
	Camera::Camera() {
		cameraPosition = Vector(0, 0, 0);
		cameraDirection = Vector(0, 0, 1);
		cameraRight = Vector(0, 0, 0);
		cameraDown = Vector(0, 0, 0);
	}

	Camera::Camera(Vector camPos, Vector camDir, Vector camRight, Vector camDown) {
		cameraPosition = camPos;
		cameraDirection = camDir;
		cameraRight = camRight;
		cameraDown = camDown;
	}
};

#endif // !CAMERA_H
