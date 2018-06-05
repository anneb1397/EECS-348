#include <math.h>
#define PI 3.1415926

bool isBlack(unsigned char ***image, int y, int x) {
	return image[RED][y][x] == 0 && image[GREEN][y][x] == 0 && image[BLUE][y][x] == 0;
}

Line detect_slope_intercept(unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// where 0 <= y < WIDTH  and 0 <= x < HEIGHT
	// set m line.m and line.b 
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	Line line;
	line.m=0;
	line.b=0;

	int space_size = 2000;
	int half = space_size / 2;
	int **hough = init_space(space_size, space_size);
	float m, b;

	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			if (isBlack(image, y, x))
				for (int t = 0; t < space_size; t++) {
					m = float(t) / float(100) - 10;
					b = -m*x + y;
					if (b > -half && b < half)
						hough[t][int(b) + half] += 1;
				}
		}

	int max = -99999;
	for (int y = 0; y < space_size; y++)
		for (int x = 0; x < space_size; x++)
			if (hough[y][x] > max)
			{
				max = hough[y][x];
				line.m = float(y) / float(100) - 10;
				line.b = x - half;
			}

	return line;
}

float toRadians(float value) {
	return value * PI / 180;
}

Line detect_normal(unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// where 0 <= y < WIDTH  and 0 <= x < HEIGHT
	// set m line.theta and line.r 
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	Line line;
	line.theta = 0;
	line.r = 0;

	int space_size = 1800;
	int half = space_size / 2;
	int **hough = init_space(space_size, space_size);
	float theta, r;

	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			if (isBlack(image, y, x))
				for (int t = 0; t < space_size; t++) {
					theta = toRadians(float(t)) / float(10);
					r = x*cos(theta) - y*sin(theta);
					if (r > -half && r < half)
						hough[t][int(r) + half] += 1;
				}
		}

	int max = -99999;
	for (int y = 0; y < space_size; y++)
		for (int x = 0; x < space_size; x++)
			if (hough[y][x] > max)
			{
				max = hough[y][x];
				line.theta = PI - toRadians(float(y)) / float(10);
				line.r = half - x;
			}
	return line;
}

int detect_circles (unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// where 0 <= y < WIDTH  and 0 <= x < HEIGHT
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"

	float radius = 30;
	float r_squared = radius * radius;
	int **hough = init_space(640, 480);
	int circles = 0;
	float b;

	for(int y=0;y<HEIGHT;y++)
		for (int x = 0; x < WIDTH; x++) {
			if (isBlack(image, y, x)) {
				for (float a = 0; a < 640; a++) {
					if ((x - a)*(x - a) < r_squared) {
						b = float(y) - sqrt(r_squared - float((x - a)*(x - a)));
						if (b > -480 && b < 480)
							hough[int(a)][int(b)] += 1;
					}
				}
			}
		}

	for (int y = 0; y < 640; y++) {
		for (int x = 0; x < 480; x++) {
			if (hough[y][x] > 59)
				circles++;
		}
	}
	return circles;	
}