#ifndef _COLOR_H
#define _COLOR_H

#include <math.h>

class Color {
	
public: double red, green, blue, alpha;
		double rgbMax = 255.0;
public:
	Color::Color() {
		red = 0;
		green = 0;
		blue = 0;
		alpha = 0;
	}

	Color::Color(double r, double g, double b, double a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}

	void setRed(double r) {
		red = r;
	}
	void setGreen(double g) {
		green = g;
	}
	void setBlue(double b) {
		blue = b;
	}
	void setAlpha (double a) {
		alpha = a;
	}	
};

#endif // !COLOR_H
