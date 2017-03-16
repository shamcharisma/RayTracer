// Main variables in the program.  
#define MAINPROGRAM

#include <iostream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>

#include "Vector.h"
#include "SceneObject.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Plane.h"
#include "Sphere.h"
#include "Sample.h"
#include "Image.h" 

;using namespace std;

Camera CreateCamera(Vector Y)
{
	Vector camPos(5, 2.25, -1);
	Vector lookAt(0.0, 0.0, 0.0);
	Vector diffBetween = Vector(camPos.x - lookAt.x, camPos.y - lookAt.y, camPos.z - lookAt.z);
	Vector camDir = diffBetween.Negative().Normalize();

	Vector camRight = Y.CrossProduct(camDir).Normalize();
	Vector camDown = camRight.CrossProduct(camDir);

	return Camera(camPos, camDir, camRight, camDown);
}

Ray ComputeCameraRay(Camera camera, double xamt, double yamt, double offset)
{
	Vector cameraRayDirection = camera.cameraDirection.Add(camera.cameraRight.Multiply(xamt - offset).Add(camera.cameraDown.Multiply(yamt - offset))).Normalize();

	return Ray(camera.cameraPosition, cameraRayDirection);
}

int TraceRay(vector<double> intersections) {
	int indexOfMinimum = 0;

	if (intersections.size() == 0)
	{
		return -1;
	}

	if (intersections.size() == 1)
	{
		if (intersections.at(0) > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}

	double max = 0;

	for (int i = 0; i < intersections.size(); i++)
	{
		if (intersections.at(i) > max) {
			max = intersections.at(i);
		}
	}

	//starting from maximum value, find minimum positive value
	if (max > 0)
	{
		for (int i = 0; i < intersections.size(); i++)
		{
			if (intersections.at(i) > 0 && intersections.at(i) <= max)
			{
				max = intersections.at(i);
				indexOfMinimum = i;
			}
		}

		return indexOfMinimum;
	}

	return -1;
}

struct RGBType {
	double r;
	double g;
	double b;
};

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data) {
	FILE *f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = { (int)floor(blue),(int)floor(green),(int)floor(red) };

		fwrite(color, 1, 3, f);
	}

	fclose(f);
}

int thiscolor;

int main(int argc, char* argv[]) {

	Vector X(1, 0, 0);
	Vector Y(0, 1, 0);
	Vector Z(0, 0, 1);
	Vector center(0, 0, 0);

	FreeImage_Initialise();

	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width*height;
	RGBType *pixels = new RGBType[n];
	int thiscolor;

	double aspectRatio = (double)width / (double)height;

	Image image = Image::Image(width, height);
	Sample sample;
	sample.getSample(width, height);
	Color color = Color(0.0, 0.0, 0.0, 0.0);

	cout << "Rendering Raytracer..." << endl;

	Camera camera = CreateCamera(Y);

	Color whiteLight(1.0, 1.0, 1.0, 0);
	Color prettyGreen(0.5, 1.0, 0.5, 0.3);
	Color greyLight(0.5, 0.5, 0.5, 0);
	Color black(0, 0, 0, 0);
	Color maroon(0.5, 0.25, 0.25, 0);

	Vector lightPos(-7, 10, -10);
	Light light(lightPos, whiteLight);

	Sphere sphere(center, 1.0, prettyGreen);
	Plane plane(Y, -1.0, maroon);

	vector<SceneObject*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<SceneObject*>(&sphere));
	sceneObjects.push_back(dynamic_cast<SceneObject*>(&plane));

	double xamt, yamt;
	const double offset = 0.5;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			thiscolor = j * width + i;
			if (width > height) {
				xamt = (((i + offset) / width)*aspectRatio) - (((width - height) / (double)height) / 2);
				yamt = ((height - j) + offset) / height;
			}
			else if (height > width) {
				xamt = (i + offset) / width;
				yamt = (((height - j) + offset) / height) / aspectRatio - (((height - width) / (double)width) / 2);
			}
			else {
				xamt = (i + offset) / width;
				yamt = ((height - j) + offset) / height;
			}	
			
			Ray ray = ComputeCameraRay(camera, xamt, yamt, offset);
			vector<double> intersections;

			for (int index = 0; index < sceneObjects.size(); index++) {
				intersections.push_back(sceneObjects.at(index)->FindIntersection(ray));
			}
			int indexOfWinningObject = TraceRay(intersections);
			cout << indexOfWinningObject;
			if (indexOfWinningObject == -1) {
				//image.commit(sample, color);
				pixels[thiscolor].r = 0;
				pixels[thiscolor].g = 0;
				pixels[thiscolor].b = 0;
			}
			else {
				//image.commit(sample, sceneObjects.at(indexOfWinningObject)->color);
				Color currentColor = sceneObjects.at(indexOfWinningObject)->getColor();
				pixels[thiscolor].r = currentColor.red;
				pixels[thiscolor].g = currentColor.green;
				pixels[thiscolor].b = currentColor.blue;
			}			
		}
	}
	savebmp("scene_anti-aliased.bmp", width, height, dpi, pixels);

	delete pixels;
	//image.writeImage("RayTracedImage.png");

	//saveScreenshot("RayTracedImage.png", width, height);
	FreeImage_DeInitialise();
	return 0;
}



