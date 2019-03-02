/* WizardKeys.c
 *
 * This program turns the keyboard backlight on and off with each key press.
 *
 * Compile with gcc -o WizardKeys WizardKeys.c -framework IOKit -framework
 * ApplicationServices -framework CoreFoundation
 *
 * By Mario Villaplana http://www.stanford.edu/~mariojv
 *
 * Use at your own risk; I'm not responsible if your keyboard lights burn out from
 * too much use.
 */

#include "MacKeyLEDAPI.h"
#include <ApplicationServices/ApplicationServices.h>

CGEventRef lightCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef
    event, void *refcon) {
  if (getKeyboardLEDValue() < 0xfff / 2) {
    setKeyboardLEDValue(0xfff);
  } else {
    setKeyboardLEDValue(0);
  }
  return NULL; // Returns NULL since passive listeners do not affect stream.
}

int main(int argc, const char * argv[]) {
  startLightService();
  CGEventMask keyMask = CGEventMaskBit(kCGEventKeyDown);
  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap,
    kCGTailAppendEventTap, kCGEventTapOptionListenOnly, keyMask,
    lightCallback, NULL);
  if (eventTap == NULL) {
    fprintf(stderr, "Event tap could not be created. Ending program.");
    exit(1);
  }
  CFRunLoopSourceRef runLoopSource =
    CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
      kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true); // needed? should be enabled by default
  CFRunLoopRun();
  return 0;
}
