#include <stdio.h>                // Standard I/O for printing
#include <pico/stdlib.h>          // Pico SDK standard library
#include <stdint.h>               // Standard integer type definitions
#include <unity.h>                // Unity testing framework
#include <pico/cyw43_arch.h>      // Pico wireless architecture
#include "unity_config.h"         // Custom Unity configuration
#include "stuff.h"                // Include external function declarations (like switch_case and do_blink)

// setUp() is a Unity framework function that runs before each test.
// Currently, it does nothing but is required by the Unity framework.
void setUp(void) {}

// tearDown() is a Unity framework function that runs after each test.
// Currently, it does nothing but is required by the Unity framework.
void tearDown(void) {}

// Test case for testing the case-switching function (upper to lower and vice versa)
void test_change_case()
{
    // Test switching from lowercase to uppercase and vice versa
    TEST_ASSERT_EQUAL('A', switch_case('a'));  // 'a' should become 'A'
    TEST_ASSERT_EQUAL('Z', switch_case('z'));  // 'z' should become 'Z'
    TEST_ASSERT_EQUAL('a', switch_case('A'));  // 'A' should become 'a'
    TEST_ASSERT_EQUAL('z', switch_case('Z'));  // 'Z' should become 'z'
    TEST_ASSERT_EQUAL('g', switch_case('G'));  // 'G' should become 'g'

    // Test non-alphabetical characters, which should remain unchanged
    TEST_ASSERT_EQUAL('0', switch_case('0'));  // Numbers should not change
    TEST_ASSERT_EQUAL('!', switch_case('!'));  // Symbols should not change
    TEST_ASSERT_EQUAL('\n', switch_case('\n'));  // Control characters should not change
    TEST_ASSERT_EQUAL('\a', switch_case('\a'));  // Other control characters should not change

    // Test characters close to 'A' and 'Z' to ensure no unexpected results
    TEST_ASSERT_EQUAL('A' - 1, switch_case('A' - 1));  // Character before 'A' should remain unchanged
    TEST_ASSERT_EQUAL('Z' + 1, switch_case('Z' + 1));  // Character after 'Z' should remain unchanged
    TEST_ASSERT_EQUAL('a' - 1, switch_case('a' - 1));  // Character before 'a' should remain unchanged
    TEST_ASSERT_EQUAL('z' + 1, switch_case('z' + 1));  // Character after 'z' should remain unchanged
}

// Test case for testing the LED blinking functionality
void test_blinking(void)
{
    int count = 0;              // Initialize count for blinking
    bool on = 0;                // Initial state of the LED (off)
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);  // Ensure LED is off initially
    
    // Test LED blinking for 200 iterations
    for (int i = 0; i < 200; i += 1) {
        int curr_count = count;              // Store the current count value
        bool next_on = do_blink(on, &count); // Call the blinking function and store the new LED state
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);  // Get current GPIO (LED) state

        // Check if the GPIO (LED) matches the "on" state
        TEST_ASSERT_EQUAL_MESSAGE(gpio, on, "GPIO should be set to the state of 'on' variable.");
        // Check if the count is incremented correctly
        TEST_ASSERT_EQUAL_MESSAGE(count, curr_count + 1, "Always increment the count");

        // Toggle the LED if count is not a multiple of 11
        if ((i + 1) % 11) {
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, next_on, "Should toggle when count is not a multiple of 11.");
        } else {
            TEST_ASSERT_EQUAL_MESSAGE(on, next_on, "Should not toggle otherwise.");
        }

        on = next_on;  // Update the "on" state for the next iteration
    }
}

// Main function to run the tests
int main (void)
{
    stdio_init_all();                              // Initialize standard I/O
    hard_assert(cyw43_arch_init() == PICO_OK);     // Initialize wireless architecture, ensure success
    sleep_ms(5000);                                // Delay to allow TTY (serial) connection to attach
    printf("Start tests\n");                       // Print message to indicate start of tests
    UNITY_BEGIN();                                 // Begin Unity test framework
    RUN_TEST(test_change_case);                    // Run the test for case-switching
    RUN_TEST(test_blinking);                       // Run the test for blinking functionality
    sleep_ms(5000);                                // Delay after tests for easier visibility of results
    return UNITY_END();                            // End Unity tests and return results
}
