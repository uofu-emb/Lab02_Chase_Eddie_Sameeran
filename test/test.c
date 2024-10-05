#include <stdint.h>  // Include standard integer type definitions
#include <unity.h>    // Include the Unity test framework

// setUp() is a Unity framework function that runs before each test.
// Currently, it does nothing but is required by the Unity framework.
void setUp(void) {}

// tearDown() is a Unity framework function that runs after each test.
// Currently, it does nothing but is required by the Unity framework.
void tearDown(void) {}

// Test to check if the variable assignment works as expected
void test_variable_assignment()
{
    int x = 1;  // Assign 1 to variable x
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");  // Assert that x is equal to 1
}

// Test to check if multiplication of two integers works correctly
void test_multiplication(void)
{
    int x = 5;  // Assign 5 to variable x
    int y = 6;  // Assign 6 to variable y
    int z = x * y;  // Multiply x and y, store result in z
    TEST_ASSERT_TRUE_MESSAGE(z == 30, "Multiplication of two integers returned incorrect value.");  // Assert that z is equal to 30
}

// Main function to run the tests
int main (void)
{
    UNITY_BEGIN();  // Initialize Unity test framework
    RUN_TEST(test_variable_assignment);  // Run the variable assignment test
    RUN_TEST(test_multiplication);  // Run the multiplication test
    return UNITY_END();  // Conclude the test run and return the result
}
