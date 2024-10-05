#include <stdio.h>                // Standard I/O functions for input/output operations

#include <FreeRTOS.h>             // FreeRTOS includes for task management
#include <task.h>                 // FreeRTOS task management functions

#include <pico/stdlib.h>          // Standard library functions for the Raspberry Pi Pico
#include <pico/multicore.h>       // Functions for multicore support on the Raspberry Pi Pico
#include <pico/cyw43_arch.h>      // CYW43 wireless chip library, includes LED control
#include "stuff.h"                // Custom header file that contains switch_case and do_blink declarations

// Global variables for tracking the LED blink state
int count = 0;                    // Tracks the number of times the LED has toggled
bool on = false;                  // Tracks the current state of the LED (on or off)

/**
 * Task function that handles the LED blinking.
 * - The task uses the `do_blink` function to toggle the state of the LED and increments the count.
 * - The task runs indefinitely, with a delay of 500 milliseconds between toggles.
 * 
 * @param params: Unused parameter (can be NULL).
 */
void blink_task(__unused void *params) {
    // Initialize the CYW43 architecture, which controls the onboard LED. Hard assert if initialization fails.
    hard_assert(cyw43_arch_init() == PICO_OK);

    // Infinite loop to toggle the LED state
    while (true) {
        // Call the do_blink function to toggle the LED state and increment the count
        on = do_blink(on, &count);

        // Delay the task by 500 milliseconds (or 500 ticks)
        vTaskDelay(500);
    }
}

/**
 * Main task function that creates the LED blink task and processes user input.
 * - The task creates a new FreeRTOS task for the LED blinking functionality.
 * - It then continuously reads characters from input, switches their case using `switch_case`, and prints them.
 * 
 * @param params: Unused parameter (can be NULL).
 */
void main_task(__unused void *params) {
    // Create the blink task with its own stack size and priority
    xTaskCreate(blink_task, "BlinkThread", 
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    // Variable to hold the input character
    char c;

    // Continuously read input characters, switch their case, and print them back
    while (c = getchar()) {
        putchar(switch_case(c));
    }
}
