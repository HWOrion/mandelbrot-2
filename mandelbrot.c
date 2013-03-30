#include <stdio.h>
#include <stdlib.h>
#include "bmp.c"

#define IMAGE_WIDTH 1366
#define IMAGE_HEIGHT 768

#define VIEW_WIDTH 4.0
#define VIEW_CENTER_X -0.75
#define VIEW_CENTER_Y 0.0

#include "utils.c"

COLOR* calculate_mandelbrot() {
	COLOR* image = (COLOR*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 3);
	if (!image) {
		fprintf(stderr, "Failed to allocate memory for image\n");
		return NULL;
	}

	const double VIEW_HEIGHT = IMAGE_HEIGHT * VIEW_WIDTH / IMAGE_WIDTH;

	const double START_X = VIEW_CENTER_X - VIEW_WIDTH / 2;
    const double START_Y = VIEW_CENTER_Y - VIEW_HEIGHT / 2;

    const double STEP_X = VIEW_WIDTH / IMAGE_WIDTH;
    const double STEP_Y = VIEW_HEIGHT / IMAGE_HEIGHT;

    double cx, cy;
    COLOR color;
    for(int y = 0; y < IMAGE_HEIGHT; y++) {
    	for(int x = 0; x < IMAGE_WIDTH; x++) {
    		cx = START_X + x * STEP_X;
    		cy = START_Y + y * STEP_Y;
    		get_color(cx, cy, &color);
    		image[y * IMAGE_WIDTH + x] = color;
    	}
    }
    return image;
}

int main() {
	COLOR* image = calculate_mandelbrot();
	write_bmp("mandelbrot.bmp", IMAGE_WIDTH, IMAGE_HEIGHT, (char*)image);
	free(image);
	return 0;
}