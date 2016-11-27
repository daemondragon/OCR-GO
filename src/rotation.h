#ifndef ROTATION_H
#define ROTATION_H

#include "rotation.h"


// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// double angle is the angle in degrees between 0 and 90 or 270 and 360
double *rotate (double *matrix, int *width, int *height, double angle);

void test_rotation();
#endif

