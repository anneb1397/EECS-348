#include <math.h>

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
	return line;
}

Line detect_normal(unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// where 0 <= y < WIDTH  and 0 <= x < HEIGHT
	// set m line.theta and line.r 
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	Line line; 
	line.theta=0;
	line.r=0;
	return line;	
}

int detect_circles (unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// where 0 <= y < WIDTH  and 0 <= x < HEIGHT
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	return 0;	
}