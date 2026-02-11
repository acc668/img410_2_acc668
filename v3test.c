// library inclusions
#include "v3math.h"

// test tolerance
#define TEST_TOLERANCE 1e-5f

// define pi
#define PI 3.14159265358979323846

// color codes for output
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_YELLOW "\033[0;33m"

// test counters
static int tests_passed = 0;
static int tests_failed = 0;
static int current_test_num = 0;


// helper function to print test results
void assert_v3_equals(const char *test_name, float *expected, float *actual) 
{
    current_test_num++;
    if (v3_equals(expected, actual, TEST_TOLERANCE)) 
    {
        printf(COLOR_GREEN "PASS" COLOR_RESET " [%d] %s\n", current_test_num, test_name);
        tests_passed++;
    } 
    else 
    {
        printf(COLOR_RED "FAIL" COLOR_RESET " [%d] %s\n", current_test_num, test_name);
        printf("  Expected: (%.6f, %.6f, %.6f)\n", expected[0], expected[1], expected[2]);
        printf("  Actual:   (%.6f, %.6f, %.6f)\n", actual[0], actual[1], actual[2]);
        tests_failed++;
    }
}

void assert_float_equals(const char *test_name, float expected, float actual) 
{
    current_test_num++;
    if (fabsf(expected - actual) <= TEST_TOLERANCE) 
    {
        printf(COLOR_GREEN "PASS" COLOR_RESET " [%d] %s\n", current_test_num, test_name);
        tests_passed++;
    } 
    else 
    {
        printf(COLOR_RED "FAIL" COLOR_RESET " [%d] %s\n", current_test_num, test_name);
        printf("  Expected: %.6f\n", expected);
        printf("  Actual:   %.6f\n", actual);
        tests_failed++;
    }
}

void print_test_section(const char *section_name) 
{
    printf("\n" COLOR_CYAN "=== Testing %s ===" COLOR_RESET "\n", section_name);
}

// test v3_from_points
void test_v3_from_points() 
{
    print_test_section("v3_from_points");

    {
        float a[3] = {0.0f, 0.0f, 0.0f};
        float b[3] = {1.0f, 2.0f, 3.0f};
        float result[3];
        float expected[3] = {1.0f, 2.0f, 3.0f};
        v3_from_points(result, a, b);
        assert_v3_equals("v3_from_points: origin to (1,2,3)", expected, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 6.0f, 8.0f};
        float result[3];
        float expected[3] = {3.0f, 4.0f, 5.0f};
        v3_from_points(result, a, b);
        assert_v3_equals("v3_from_points: (1,2,3) to (4,6,8)", expected, result);
    }

    {
        float a[3] = {-1.0f, -2.0f, -3.0f};
        float b[3] = {1.0f, 1.0f, 1.0f};
        float result[3];
        float expected[3] = {2.0f, 3.0f, 4.0f};
        v3_from_points(result, a, b);
        assert_v3_equals("v3_from_points: negative to positive", expected, result);
    }

    {
        float a[3] = {5.0f, 5.0f, 5.0f};
        float b[3] = {5.0f, 5.0f, 5.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, 0.0f};
        v3_from_points(result, a, b);
        assert_v3_equals("v3_from_points: same points", expected, result);
    }

    // dst = a
    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 6.0f, 8.0f};
        float expected[3] = {3.0f, 4.0f, 5.0f};
        v3_from_points(a, a, b);
        assert_v3_equals("v3_from_points: overlapping dst=a", expected, a);
    }
}

// test v3_add
void test_v3_add() 
{
    print_test_section("v3_add");
    
    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 5.0f, 6.0f};
        float result[3];
        float expected[3] = {5.0f, 7.0f, 9.0f};
        v3_add(result, a, b);
        assert_v3_equals("v3_add: basic addition", expected, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {0.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {1.0f, 2.0f, 3.0f};
        v3_add(result, a, b);
        assert_v3_equals("v3_add: adding zero vector", expected, result);
    }

    {
        float a[3] = {1.0f, -2.0f, 3.0f};
        float b[3] = {-1.0f, 2.0f, -3.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, 0.0f};
        v3_add(result, a, b);
        assert_v3_equals("v3_add: canceling addition", expected, result);
    }

    // dst = a
    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 5.0f, 6.0f};
        float expected[3] = {5.0f, 7.0f, 9.0f};
        v3_add(a, a, b);
        assert_v3_equals("v3_add: overlapping dst=a", expected, a);
    }

    {
        float a[3] = {0.1f, 0.2f, 0.3f};
        float b[3] = {0.4f, 0.5f, 0.6f};
        float result[3];
        float expected[3] = {0.5f, 0.7f, 0.9f};
        v3_add(result, a, b);
        assert_v3_equals("v3_add: fractional values", expected, result);
    }
}

// test v3_subtract
void test_v3_subtract() 
{
    print_test_section("v3_subtract");
    
    {
        float a[3] = {5.0f, 7.0f, 9.0f};
        float b[3] = {1.0f, 2.0f, 3.0f};
        float result[3];
        float expected[3] = {4.0f, 5.0f, 6.0f};
        v3_subtract(result, a, b);
        assert_v3_equals("v3_subtract: basic subtraction", expected, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, 0.0f};
        v3_subtract(result, a, a);
        assert_v3_equals("v3_subtract: vector minus itself", expected, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 5.0f, 6.0f};
        float result[3];
        float expected[3] = {-3.0f, -3.0f, -3.0f};
        v3_subtract(result, a, b);
        assert_v3_equals("v3_subtract: negative result", expected, result);
    }

    // dst = a
    {
        float a[3] = {5.0f, 7.0f, 9.0f};
        float b[3] = {1.0f, 2.0f, 3.0f};
        float expected[3] = {4.0f, 5.0f, 6.0f};
        v3_subtract(a, a, b);
        assert_v3_equals("v3_subtract: overlapping dst=a", expected, a);
    }
}

// test v3_dot_product
void test_v3_dot_product() 
{
    print_test_section("v3_dot_product");
    
    // dot = 0
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.0f, 1.0f, 0.0f};
        float result = v3_dot_product(a, b);
        assert_float_equals("v3_dot_product: perpendicular vectors", 0.0f, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {2.0f, 4.0f, 6.0f};
        float result = v3_dot_product(a, b);
        float expected = 1.0f*2.0f + 2.0f*4.0f + 3.0f*6.0f;
        assert_float_equals("v3_dot_product: parallel vectors", expected, result);
    }

    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {1.0f, 0.0f, 0.0f};
        float result = v3_dot_product(a, b);
        assert_float_equals("v3_dot_product: same unit vectors", 1.0f, result);
    }

    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {-1.0f, 0.0f, 0.0f};
        float result = v3_dot_product(a, b);
        assert_float_equals("v3_dot_product: opposite vectors", -1.0f, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, -5.0f, 6.0f};
        float result = v3_dot_product(a, b);
        float expected = 1.0f*4.0f + 2.0f*(-5.0f) + 3.0f*6.0f;
        assert_float_equals("v3_dot_product: general case", expected, result);
    }
}

// test v3_cross_product
void test_v3_cross_product() 
{
    print_test_section("v3_cross_product");
    
    // i * j = k
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.0f, 1.0f, 0.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, 1.0f};
        v3_cross_product(result, a, b);
        assert_v3_equals("v3_cross_product: i × j = k", expected, result);
    }

    // j * i = -k
    {
        float a[3] = {0.0f, 1.0f, 0.0f};
        float b[3] = {1.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, -1.0f};
        v3_cross_product(result, a, b);
        assert_v3_equals("v3_cross_product: j × i = -k", expected, result);
    }

    // cross = 0
    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {2.0f, 4.0f, 6.0f};
        float result[3];
        float expected[3] = {0.0f, 0.0f, 0.0f};
        v3_cross_product(result, a, b);
        assert_v3_equals("v3_cross_product: parallel vectors", expected, result);
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {4.0f, 5.0f, 6.0f};
        float result[3];
        // a * b = (2 * 6 - 3 * 5, 3 * 4 - 1 * 6, 1 * 5 - 2 * 4) = (-3, 6, -3)
        float expected[3] = {-3.0f, 6.0f, -3.0f};
        v3_cross_product(result, a, b);
        assert_v3_equals("v3_cross_product: general case", expected, result);
    }

    // dst = a
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.0f, 1.0f, 0.0f};
        float expected[3] = {0.0f, 0.0f, 1.0f};
        v3_cross_product(a, a, b);
        assert_v3_equals("v3_cross_product: overlapping dst=a", expected, a);
    }
}

// test v3_scale
void test_v3_scale() 
{
    print_test_section("v3_scale");
    
    {
        float v[3] = {1.0f, 2.0f, 3.0f};
        float expected[3] = {2.0f, 4.0f, 6.0f};
        v3_scale(v, 2.0f);
        assert_v3_equals("v3_scale: scale by 2", expected, v);
    }

    {
        float v[3] = {1.0f, 2.0f, 3.0f};
        float expected[3] = {0.0f, 0.0f, 0.0f};
        v3_scale(v, 0.0f);
        assert_v3_equals("v3_scale: scale by 0", expected, v);
    }

    {
        float v[3] = {1.0f, 2.0f, 3.0f};
        float expected[3] = {-1.0f, -2.0f, -3.0f};
        v3_scale(v, -1.0f);
        assert_v3_equals("v3_scale: scale by -1", expected, v);
    }

    {
        float v[3] = {2.0f, 4.0f, 6.0f};
        float expected[3] = {1.0f, 2.0f, 3.0f};
        v3_scale(v, 0.5f);
        assert_v3_equals("v3_scale: scale by 0.5", expected, v);
    }
}

// test v3_angle
void test_v3_angle() 
{
    print_test_section("v3_angle");
    
    // angle = 0
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {2.0f, 0.0f, 0.0f};
        float result = v3_angle(a, b);
        assert_float_equals("v3_angle: parallel vectors", 0.0f, result);
    }

    // angle = pi / 2
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.0f, 1.0f, 0.0f};
        float result = v3_angle(a, b);
        assert_float_equals("v3_angle: perpendicular vectors", PI / 2.0f, result);
    }

    // angle = pi
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {-1.0f, 0.0f, 0.0f};
        float result = v3_angle(a, b);
        assert_float_equals("v3_angle: opposite vectors", PI, result);
    }

    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {1.0f, 1.0f, 0.0f};
        float result = v3_angle(a, b);
        assert_float_equals("v3_angle: 45 degrees", PI / 4.0f, result);
    }
}

// test v3_angle_quick
void test_v3_angle_quick() 
{
    print_test_section("v3_angle_quick");
    
    // cos = 1
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {2.0f, 0.0f, 0.0f};
        float result = v3_angle_quick(a, b);
        assert_float_equals("v3_angle_quick: parallel vectors", 1.0f, result);
    }

    // cos = 0
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.0f, 1.0f, 0.0f};
        float result = v3_angle_quick(a, b);
        assert_float_equals("v3_angle_quick: perpendicular vectors", 0.0f, result);
    }

    // cos = -1
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {-1.0f, 0.0f, 0.0f};
        float result = v3_angle_quick(a, b);
        assert_float_equals("v3_angle_quick: opposite vectors", -1.0f, result);
    }

    // cos = 0.5
    {
        float a[3] = {1.0f, 0.0f, 0.0f};
        float b[3] = {0.5f, 0.866025f, 0.0f};
        float result = v3_angle_quick(a, b);
        assert_float_equals("v3_angle_quick: 60 degrees", 0.5f, result);
    }
}

// test v3_reflect
void test_v3_reflect() 
{
    print_test_section("v3_reflect");
    
    {
        float v[3] = {1.0f, 1.0f, 0.0f};
        float n[3] = {1.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {-1.0f, 1.0f, 0.0f};
        v3_reflect(result, v, n);
        assert_v3_equals("v3_reflect: across y-axis", expected, result);
    }

    {
        float v[3] = {1.0f, 0.0f, 0.0f};
        float n[3] = {1.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {-1.0f, 0.0f, 0.0f};
        v3_reflect(result, v, n);
        assert_v3_equals("v3_reflect: perpendicular to normal", expected, result);
    }

    {
        float v[3] = {0.0f, 1.0f, 0.0f};
        float n[3] = {1.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {0.0f, 1.0f, 0.0f};
        v3_reflect(result, v, n);
        assert_v3_equals("v3_reflect: parallel to normal", expected, result);
    }

    // dst = v
    {
        float v[3] = {1.0f, 1.0f, 0.0f};
        float n[3] = {1.0f, 0.0f, 0.0f};
        float expected[3] = {-1.0f, 1.0f, 0.0f};
        v3_reflect(v, v, n);
        assert_v3_equals("v3_reflect: overlapping dst=v", expected, v);
    }
}

// test v3_length
void test_v3_length() 
{
    print_test_section("v3_length");
    
    {
        float v[3] = {1.0f, 0.0f, 0.0f};
        float result = v3_length(v);
        assert_float_equals("v3_length: unit vector", 1.0f, result);
    }

    {
        float v[3] = {0.0f, 0.0f, 0.0f};
        float result = v3_length(v);
        assert_float_equals("v3_length: zero vector", 0.0f, result);
    }

    {
        float v[3] = {3.0f, 4.0f, 0.0f};
        float result = v3_length(v);
        assert_float_equals("v3_length: 3-4-5 triangle", 5.0f, result);
    }

    {
        float v[3] = {1.0f, 1.0f, 1.0f};
        float result = v3_length(v);
        assert_float_equals("v3_length: (1,1,1)", sqrtf(3.0f), result);
    }

    {
        float v[3] = {-3.0f, -4.0f, 0.0f};
        float result = v3_length(v);
        assert_float_equals("v3_length: negative components", 5.0f, result);
    }
}

// test v3_normalize
void test_v3_normalize() 
{
    print_test_section("v3_normalize");
    
    {
        float v[3] = {1.0f, 0.0f, 0.0f};
        float result[3];
        float expected[3] = {1.0f, 0.0f, 0.0f};
        v3_normalize(result, v);
        assert_v3_equals("v3_normalize: already normalized", expected, result);
    }

    {
        float v[3] = {3.0f, 4.0f, 0.0f};
        float result[3];
        float expected[3] = {0.6f, 0.8f, 0.0f};
        v3_normalize(result, v);
        assert_v3_equals("v3_normalize: scale down", expected, result);
    }

    {
        float v[3] = {1.0f, 1.0f, 1.0f};
        float result[3];
        float inv_sqrt3 = 1.0f / sqrtf(3.0f);
        float expected[3] = {inv_sqrt3, inv_sqrt3, inv_sqrt3};
        v3_normalize(result, v);
        assert_v3_equals("v3_normalize: (1,1,1)", expected, result);
    }

    {
        float v[3] = {5.0f, 12.0f, 13.0f};
        float result[3];
        v3_normalize(result, v);
        float length = v3_length(result);
        assert_float_equals("v3_normalize: result has unit length", 1.0f, length);
    }

    // dst = a
    {
        float v[3] = {3.0f, 4.0f, 0.0f};
        float expected[3] = {0.6f, 0.8f, 0.0f};
        v3_normalize(v, v);
        assert_v3_equals("v3_normalize: overlapping dst=a", expected, v);
    }
}

// test v3_equals helper
void test_v3_equals() 
{
    print_test_section("v3_equals");
    
    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {1.0f, 2.0f, 3.0f};
        current_test_num++;
        if (v3_equals(a, b, TEST_TOLERANCE)) 
        {
            printf(COLOR_GREEN "PASS" COLOR_RESET " [%d] v3_equals: exactly equal\n", current_test_num);
            tests_passed++;
        } 
        else 
        {
            printf(COLOR_RED "FAIL" COLOR_RESET " [%d] v3_equals: exactly equal\n", current_test_num);
            tests_failed++;
        }
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {1.000001f, 2.000001f, 3.000001f};
        current_test_num++;
        if (v3_equals(a, b, TEST_TOLERANCE)) 
        {
            printf(COLOR_GREEN "PASS" COLOR_RESET " [%d] v3_equals: within tolerance\n", current_test_num);
            tests_passed++;
        } 
        else 
        {
            printf(COLOR_RED "FAIL" COLOR_RESET " [%d] v3_equals: within tolerance\n", current_test_num);
            tests_failed++;
        }
    }

    {
        float a[3] = {1.0f, 2.0f, 3.0f};
        float b[3] = {1.1f, 2.0f, 3.0f};
        current_test_num++;
        if (!v3_equals(a, b, TEST_TOLERANCE)) 
        {
            printf(COLOR_GREEN "PASS" COLOR_RESET " [%d] v3_equals: outside tolerance\n", current_test_num);
            tests_passed++;
        } 
        else 
        {
            printf(COLOR_RED "FAIL" COLOR_RESET " [%d] v3_equals: outside tolerance\n", current_test_num);
            tests_failed++;
        }
    }
}

// main test runner
int main(int argc, char **argv) 
{
    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    printf("3D Vector Math Library Tests\n");

    test_v3_from_points();
    test_v3_add();
    test_v3_subtract();
    test_v3_dot_product();
    test_v3_cross_product();
    test_v3_scale();
    test_v3_angle();
    test_v3_angle_quick();
    test_v3_reflect();
    test_v3_length();
    test_v3_normalize();
    test_v3_equals();

    printf("Total tests: %d\n", tests_passed + tests_failed);

    if (tests_failed > 0) 
    {
        printf(COLOR_RED "Failed: %d\n" COLOR_RESET, tests_failed);
        printf("\n" COLOR_YELLOW "Some tests failed. Please review the output above.\n" COLOR_RESET);
        return 1;
    } 
    else 
    {
        printf(COLOR_RED "Failed: %d\n" COLOR_RESET, tests_failed);
        printf("\n" COLOR_GREEN "All tests passed!\n" COLOR_RESET);
        return 0;
    }
}