# Project 2: 3D Math

A comprehensive C++ library for 3D vector mathematics operations, including a full test suite.

## Files

- 'v3math.h'
- 'v3math.c'
- 'v3test.c'
- 'Makefile'

## Building

Compile the test program:
```bash
g++ -o v3test v3test.cpp v3math.cpp -lm -Wall -Wextra -std=c++11
```

Or use the Makefile:
```bash
make
make test
make clean
```

Run the tests:
```bash
./v3test
```

## Library Functions

### Vector Construction
- **`v3_from_points(float *dst, float *a, float *b)`**  
  Creates a vector from point `a` to point `b`.  
  Result: `dst = b - a`

### Basic Operations
- **`v3_add(float *dst, float *a, float *b)`**  
  Adds two vectors.  
  Result: `dst = a + b`

- **`v3_subtract(float *dst, float *a, float *b)`**  
  Subtracts vector `b` from vector `a`.  
  Result: `dst = a - b`

- **`v3_scale(float *dst, float s)`**  
  Scales a vector by scalar `s` (in-place).  
  Result: `dst = dst * s`

### Products
- **`v3_dot_product(float *a, float *b)`**  
  Returns the dot product of two vectors.  
  Result: `a · b = a.x * b.x + a.y * b.y + a.z * b.z`

- **`v3_cross_product(float *dst, float *a, float *b)`**  
  Calculates the cross product of two vectors.  
  Result: `dst = a × b`

### Angles
- **`v3_angle(float *a, float *b)`**  
  Returns the angle between two vectors in radians [0, pi].  
  Uses `acos()` for precise angle calculation.

- **`v3_angle_quick(float *a, float *b)`**  
  Returns the cosine of the angle between two vectors.  
  Faster than `v3_angle()` since it skips `acos()`.

### Reflection
- **`v3_reflect(float *dst, float *v, float *n)`**  
  Reflects vector `v` across normal `n`.  
  Formula: `dst = v - 2(v · n)n`  
  Assumes `n` is normalized.

### Magnitude and Normalization
- **`v3_length(float *a)`**  
  Returns the length (magnitude) of a vector.  
  Result: `||a|| = sqrt(a.x * a.x + a.y * a.y + a.z * a.z)`

- **`v3_normalize(float *dst, float *a)`**  
  Normalizes a vector to unit length.  
  Result: `dst = a / ||a||`

### Testing Helper
- **`v3_equals(float *a, float *b, float tolerance)`**  
  Checks if two vectors are equal within a tolerance.  
  Returns `true` if all components differ by less than `tolerance`.

# Features

### Memory Safety
- All functions handle overlapping memory correctly (e.g., `dst` and `a` can be the same)
- Uses temporary storage internally to prevent corruption
- All pointers are validated with `assert()`

### Error Handling
- Functions check for invalid inputs (NULL pointers, zero-length vectors)
- Error messages are printed to `stderr` with "Error:" prefix
- Functions handle edge cases gracefully

### Testing
The test suite includes:
- **53 unit tests** covering all functions
- **3-5 tests per function** with different equivalence classes
- Tests for:
  - Basic functionality
  - Edge cases (zero vectors, unit vectors, parallel/perpendicular vectors)
  - Overlapping memory scenarios
  - Negative values
  - Floating-point precision
- Colorized output for easy reading
- Detailed failure messages showing expected vs actual values

### Test Coverage

| Function | Tests |
|----------|-------|
| v3_from_points | 5 tests |
| v3_add | 5 tests |
| v3_subtract | 4 tests |
| v3_dot_product | 5 tests |
| v3_cross_product | 5 tests |
| v3_scale | 4 tests |
| v3_angle | 4 tests |
| v3_angle_quick | 4 tests |
| v3_reflect | 4 tests |
| v3_length | 5 tests |
| v3_normalize | 5 tests |
| v3_equals | 3 tests |

## Example Usage

```cpp
#include "v3math.h"

int main() 
{
    // create two vectors
    float a[3] = {1.0f, 0.0f, 0.0f};
    float b[3] = {0.0f, 1.0f, 0.0f};
    
    // calculate cross product
    float result[3];
    v3_cross_product(result, a, b);
    
    // calculate angle
    float angle = v3_angle(a, b);
    
    // normalize a vector
    float v[3] = {3.0f, 4.0f, 0.0f};
    v3_normalize(v, v);
    
    return 0;
}
```

# Technical Notes

### Coding Style
- Uses "Restricted C++" approach (no exceptions, RTTI, STL, virtual functions, or multiple inheritance)
- Follows C++11 standard
- Uses `stdint.h` types (int32_t, uint8_t, etc.) for platform-independent integer sizes
- Error handling via `errno` and `fprintf` to `stderr`
- Robust memory management with local temporary arrays to handle overlapping pointers
- All variables initialized before use
- Comprehensive error checking with assertions

### Floating Point Comparisons
The library uses a tolerance-based comparison for floating-point values:
- Internal epsilon: `1e-6f`
- Test tolerance: `1e-5f`

### Mathematical Properties
The implementation respects fundamental vector properties:
- Cross product anti-commutativity: `a × b = -(b × a)`
- Dot product commutativity: `a · b = b · a`
- Vector addition commutativity: `a + b = b + a`
- Angle range: [0, pi] radians
