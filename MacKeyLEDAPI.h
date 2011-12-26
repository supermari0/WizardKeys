/* MacKeyLEDAPI.h
 * This header defines functions for accessing and modifying keyboard lights on
 * Mac laptops in OS X 10.6 and above. Inspired by (and some code taken from) Amit 
 * Singh's OSX Internals website, see header file for details.
 *
 * Ensure that you compile with -framework IOKit -framework CoreFoundation when
 * compiling your programs to include the appropriate frameworks.
 *
 * By Mario Villaplana http://www.stanford.edu/~mariojv
 */

 #include "MacKeyLEDAPI.c"

/* startLightService is a setup function that must be called before any other
 * method in this file in order to set up communication between the program and
 * the hardware. */
void startLightService();

 /* getKeyboardLEDValue returns a value between 0 and 0xfff indicating the
  * brightness of the keyboard light. */

uint64_t geyKeyboardLEDValue();

/* setKeyboardLEDValue sets the keyboard brightness to a value between 0 and
 * 0xfff. */
void setKeyboardLEDValue(uint64_t ledValue);

/* setKeyboardLEDValueFade sets keyboard LED brightness to a value between 0 and 0xfff, fading the
   change in brightness over time_ms milliseconds. */
void setKeyboardLEDValueFade(uint64_t ledValue, uint64_t time_ms);
