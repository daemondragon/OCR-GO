#ifndef ROTATION_H
#define ROTATION_H

#include "rotation.h"


// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// double angle is the angle in degrees between 0 and 90 or 270 and 360
// rotation are in the clockwise direction
double *rotate (double *matrix, int *width, int *height, double angle);


// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// rotation are in the clockwise direction
// autorotion of +-20°
double * autorotate(double *matrix, int *width, int *height);


// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// rotation are in the clockwise direction
double *rotate180(double *matrix, int *width, int *height);

// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// rotation are in the clockwise direction
double *rotate90(double *matrix, int *width, int *height);

// double matrix is the rotated matrix
// int *width and int *height are the dimensions of the input matrix and
// become rotated matrix dimensions
// rotation are in the clockwise direction
double *rotate270(double *matrix, int *width, int *height);

void test_rotation();
#endif

