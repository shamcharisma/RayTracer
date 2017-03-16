#ifndef _IMAGE_H
#define _IMAGE_H

#include <FreeImage.h>
#include <string>
#include "Sample.h"
#include "Color.h"

class Image {
public:	
	FIBITMAP* bitmap;
	int max_x;
	int max_y;

	char convertToPixel(double x) {
		if (x < 0.0) return ((unsigned char)(0.0));
		else if (x >= 1.0) return ((unsigned char)(255.0));
		else return ((unsigned char)(x * 255.0));
	}

	void Image::commit(Sample sample, Color color) {
		if (sample.x < 0 || sample.x >= max_x) return;
		else if (sample.y < 0 || sample.y >= max_y) return;
		RGBQUAD* pixel = new RGBQUAD();
		pixel->rgbRed = convertToPixel(color.blue);
		pixel->rgbGreen = convertToPixel(color.green);
		pixel->rgbBlue = convertToPixel(color.red);
		//printf("PIXEL: %d, %d, COLOR: %f, %f, %f.\n", sample.x, sample.y, color.red, color.green, color.blue);
		FreeImage_SetPixelColor(bitmap, sample.x, sample.y, pixel);
	}

	void Image::writeImage(std::string filename) {
		FreeImage_Save(FIF_PNG, bitmap, (filename).c_str(), 0);
	}

	Image::Image(const int width, const int height) {
		bitmap = FreeImage_Allocate(width, height, 24);
		max_x = width;
		max_y = height;
	}
}

#endif