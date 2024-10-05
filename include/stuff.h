#pragma once  // Ensures this header file is included only once during compilation

// Define task priorities and stack sizes for FreeRTOS tasks
// `tskIDLE_PRIORITY` is the lowest priority in FreeRTOS, and we add to it to assign our task priorities.
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )  // Priority for the main task (just above idle)
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )  // Priority for the blink task (higher than main)

// Define stack sizes for the tasks
#define MAIN_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE    // Minimum stack size for the main task
#define BLINK_TASK_STACK_SIZE   configMINIMAL_STACK_SIZE    // Minimum stack size for the blink task

// Function declarations (prototypes) for the tasks and utility functions

/**
 * Task for handling the LED blinking logic.
 * @param params: Pointer to task parameters, typically unused.
 */
void blink_task(void *params);

/**
 * Main task that coordinates program execution.
 * @param params: Pointer to task parameters, typically unused.
 */
void main_task(void *params);

/**
 * Switches the case of the input character.
 * If the character is lowercase, it is converted to uppercase, and vice versa.
 * Non-alphabetical characters remain unchanged.
 * 
 * @param c: The character to switch case.
 * @return The case-switched character.
 */
char switch_case(char c);

/**
 * Blinks an LED by toggling its state based on the given parameters.
 * The count is incremented, and the LED is toggled depending on certain conditions.
 * 
 * @param on: Current state of the LED (on or off).
 * @param count: Pointer to an integer count that tracks how many times the function has been called.
 * @return The new state of the LED (true for on, false for off).
 */
bool do_blink(bool on, int *count);
