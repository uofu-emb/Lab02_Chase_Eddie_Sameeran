#include <pico/stdlib.h>         // Includes standard library functions for the Raspberry Pi Pico
#include <pico/cyw43_arch.h>     // Includes functions to control the CYW43 wireless chip, which also controls the onboard LED
#include "stuff.h"               // Includes the header file containing declarations of switch_case and do_blink

/**
 * Switches the case of a given character.
 * - If the input character is lowercase ('a' to 'z'), it converts it to uppercase.
 * - If the input character is uppercase ('A' to 'Z'), it converts it to lowercase.
 * - Non-alphabetic characters are returned unchanged.
 * 
 * @param c: The character to switch case.
 * @return The case-switched character, or the original character if it's non-alphabetic.
 */
char switch_case(char c)
{
    // Check if the character is lowercase and convert to uppercase by subtracting 32 (ASCII difference)
    if (c <= 'z' && c >= 'a') return c - 32;
    // Check if the character is uppercase and convert to lowercase by adding 32
    else if (c >= 'A' && c <= 'Z') return c + 32;
    // Return non-alphabetic characters unchanged
    else return c;
}

/**
 * Toggles the state of an LED on the Pico W board based on the current state and increments a count.
 * - The LED's state is toggled every time the function is called, except when the count is a multiple of 11.
 * - The function increments the count each time it is called.
 * 
 * @param on: The current state of the LED (true for on, false for off).
 * @param count: A pointer to an integer that tracks how many times the function has been called.
 * @return The new state of the LED (true for on, false for off).
 */
bool do_blink(bool on, int *count)
{
    // Set the state of the onboard LED (on or off) using the cyw43_arch_gpio_put function
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);

    // Increment the count
    *count += 1;

    // Return the toggled state of the LED unless the count is a multiple of 11, in which case keep the state unchanged
    return *count % 11 ? !on : on;
}
