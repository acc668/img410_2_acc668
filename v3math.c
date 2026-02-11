// library inclusions
#include "v3math.h"

// define the tolerance for floating point comparisons
#define EPSILON 1e-6f

// form a vector from point a to point b
// dst = b - a
void v3_from_points(float *dst, float *a, float *b)
{
    assert(dst != NULL && a != NULL && b != NULL);

    // handle overlapping memory by using temporary storage
    float temp[3];
    temp[0] = b[0] - a[0];
    temp[1] = b[1] - a[1];
    temp[2] = b[2] - a[2];

    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// add two vectors
// dst = a + b
void v3_add(float *dst, float *a, float *b)
{
    assert(dst != NULL && a != NULL && b != NULL);

    float temp[3];
    temp[0] = a[0] + b[0];
    temp[1] = a[1] + b[1];
    temp[2] = a[2] + b[2];
    
    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// subtract vector b from vector a
// dst = a - b
void v3_subtract(float *dst, float *a, float *b)
{
    assert(dst != NULL && a != NULL && b != NULL);
    
    float temp[3];
    temp[0] = a[0] - b[0];
    temp[1] = a[1] - b[1];
    temp[2] = a[2] - b[2];
    
    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// calculate dot product of two vectors
// returns: a * b = a.x * b.x + a.y * b.y + a.z * b.z
float v3_dot_product(float *a, float *b)
{
    assert(a != NULL && b != NULL);
    
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

// calculate cross product of two vectors
// dst = a * b
void v3_cross_product(float *dst, float *a, float *b)
{
    assert(dst != NULL && a != NULL && b != NULL);
    
    // use temporary storage to handle overlapping memory
    float temp[3];
    temp[0] = a[1] * b[2] - a[2] * b[1];
    temp[1] = a[2] * b[0] - a[0] * b[2];
    temp[2] = a[0] * b[1] - a[1] * b[0];
    
    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// scale a vector by scalar s in-place
// dst = dst * s
void v3_scale(float *dst, float s)
{
    assert(dst != NULL);

    dst[0] *= s;
    dst[1] *= s;
    dst[2] *= s;
}

// calculate angle between two vectors in radians
// returns: angle in range [0, pi]
float v3_angle(float *a, float *b)
{
    assert(a != NULL && b != NULL);
    
    float len_a = v3_length(a);
    float len_b = v3_length(b);

    // check for zero length vectors
    if (len_a < EPSILON || len_b < EPSILON)
    {
        fprintf(stderr, "Error: Cannot compute angle with zero length vector\n");
        errno = EINVAL;
        return 0.0f;
    }

    float dot = v3_dot_product(a, b);
    float cos_angle = dot / (len_a * len_b);

    // clamp to [-1, 1] to avoid numerical errors with acos
    if (cos_angle > 1.0f) cos_angle = 1.0f;
    if (cos_angle < -1.0f) cos_angle = -1.0f;

    return acosf(cos_angle);
}

// calculate angle between two vectors without inverse cosine
// returns: cosine of the angle
float v3_angle_quick(float *a, float *b)
{
    assert(a != NULL && b != NULL);

    float len_a = v3_length(a);
    float len_b = v3_length(b);

    // check for zero length vectors
    if (len_a < EPSILON || len_b < EPSILON)
    {
        fprintf(stderr, "Error: Cannot compute angle with zero length vector\n");
        errno = EINVAL;
        // cos(0) = 1
        return 1.0f;
    }

    float dot = v3_dot_product(a, b);
    float cos_angle = dot / (len_a * len_b);

    // clamp to [-1, 1]
    if (cos_angle > 1.0f) cos_angle = 1.0f;
    if (cos_angle < -1.0f) cos_angle = -1.0f;

    return cos_angle;
}

// reflect vector v across normal n
// dst = v - 2(v * n)n
// assumes n is normalized
void v3_reflect(float *dst, float *v, float *n)
{
    assert(dst != NULL && v != NULL && n != NULL);

    float dot = v3_dot_product(v, n);

    // use temporary storage
    float temp[3];
    temp[0] = v[0] - 2.0f * dot * n[0];
    temp[1] = v[1] - 2.0f * dot * n[1];
    temp[2] = v[2] - 2.0f * dot * n[2];
    
    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// calculate length/magnitude of a vector
// returns: ||a|| = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z))
float v3_length(float *a)
{
    assert(a != NULL);

    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

// normalize a vector to make it a unit length
// dst = a / ||a||
void v3_normalize(float *dst, float *a)
{
    assert(dst != NULL && a != NULL);

    float len = v3_length(a);

    if (len < EPSILON)
    {
        fprintf(stderr, "Error: Cannot normalize zero length vector\n");
        errno = EINVAL;
        dst[0] = 0.0f;
        dst[1] = 0.0f;
        dst[2] = 0.0f;
        return;
    }

    float inv_len = 1.0f / len;

    // use temporary storage
    float temp[3];
    temp[0] = a[0] * inv_len;
    temp[1] = a[1] * inv_len;
    temp[2] = a[2] * inv_len;
    
    dst[0] = temp[0];
    dst[1] = temp[1];
    dst[2] = temp[2];
}

// test helper - check if two vectors are equal within tolerance
bool v3_equals(float *a, float *b, float tolerance)
{
    assert(a != NULL && b != NULL);

    for (int i = 0; i < 3; i++)
    {
        float diff = fabsf(a[i] - b[i]);

        if (a[i] == b[i])
        {
            continue;
        }

        if (diff > tolerance)
        {
            return false;
        }
    }

    return true;
}