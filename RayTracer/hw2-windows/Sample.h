#ifndef SAMPLE_H
#define SAMPLE_H

class Sample {
public:
	int x;
	int y;
	int curr_x = 0;
	int curr_y = 0;	
	
	Sample::Sample() {
		x = 0; y = 0;
	}

	Sample::Sample(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool Sample::getSample(int max_x, int max_y) {
		//*sample = Sample(curr_x, curr_y);
		curr_x = curr_x + 1;
		if (curr_x > max_x) {
			curr_x = 0;
			curr_y = curr_y + 1;
		}
		if (curr_y > max_y) {
			return false;
		}
		return true;
	}
};

#endif