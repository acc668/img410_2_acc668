#ifndef V3MATH_H
#define V3Math_H

// library inclusions
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

// form vector from point a to point b
void v3_from_points(float *dst, float *a, float *b);

// add two vectors
void v3_add(float *dst, float *a, float *b);

// subtract vector b from vector a
void v3_subtract(float *dst, float *a, float *b);

// calculate dot product of two vectors
float v3_dot_product(float *a, float *b);

// calculate cross product of two vectors
void v3_cross_product(float *dst, float *a, float *b);

// scale a vector by scalar s
void v3_scale(float *dst, float s);

// calculate angle between two vectors in radians
float v3_angle(float *a, float *b);

// calculate angle between two vectors without inverse cosine 
float v3_angle_quick(float *a, float *b);

// reflect vector v across normal n
void v3_reflect(float *dst, float *v, float *n);

// calculate length/magnitude of a vector
float v3_length(float *a);

// normalize a vector to make it unit length
void v3_normalize(float *dst, float *a);

// test helper - check if two vectors are equal within tolerance
bool v3_equals(float *a, float *b, float tolerance);

#endif