#define MAX_ITERATIONS 255

typedef struct {
	unsigned char r, g, b;
} COLOR;


inline double sqr(double x) {
	return x * x;
}

inline int in_cardioid(double x, double y) {
	double q = sqr(x - 0.25) + sqr(y);
	return q * (q + (x - 0.25)) < sqr(y) / 4.0;
}

inline int in_bulb(double x, double y) {
	return sqr(x + 1) + sqr(y) < 0.0625;
}

int get_iterations(double x, double y) {
	if (in_cardioid(x, y) || in_bulb(x, y)) {
		return -1;
	}
	double a = x;
	double b = y;
	double temp;
	for(int i = 0; i < MAX_ITERATIONS; i++) {
		if (a * a + b * b > 4.0) {
			return i;
		}
		temp = a;
		a = a * a - b * b + x;
		b = 2 * temp * b + y;
	}
	return -1;
}

void get_color(double x, double y, COLOR* result) {
	int iterations = get_iterations(x, y);
	if (iterations == -1) {
		result->r = 
		result->g = 
		result->b = 0;
	}
	else if (iterations <= 15) {
  		result->r = 16;
  		result->g = 16;
  		result->b = 16 * iterations;
  	}
    else if (iterations <= 47) {
	  	result->r = 0;
	  	result->g = 8 * (iterations - 16);
	  	result->b = 255;
	}
    else if (iterations <= 111) {
	  	result->r = 4 * (iterations - 48);
	  	result->g = 255;
	  	result->b = 255;
	}
    else {
	  	result->r = 
	  	result->g = 
	  	result->b = MAX_ITERATIONS - iterations;
	}
}