/* MacKeyLEDAPI.c
 * This implements a few functions for accessing and modifying the keyboard
 * lights on Mac laptops in OS X 10.6 and above.
 *
 * By Mario Villaplana http://www.stanford.edu/~mariojv
 *
 * Inspired by/some code taken from Amit Singh's site below the header
 * inclusions.
 * 
 * I also looked at some posts on these mailing lists and forums to figure out
 * how to handle some deprecated functions from Amit's site:
 * http://forums.macrumors.com/archive/index.php/t-1133446.html
 * http://lists.apple.com/archives/darwin-drivers/2008/mar/msg00022.html
 * http://lists.apple.com/archives/darwin-drivers/2008/Jan/msg00070.html
 */

#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

/* This enum defines the different functions available for hardware
 * manipulation by the IOConnectCallMethod. Taken directly from Amit Singh's
 * OSX Internals website at http://osxbook.com/book/bonus/chapter10/light/. */ 
enum {
    kGetSensorReadingID   = 0,  // getSensorReading(int *, int *)
    kGetLEDBrightnessID   = 1,  // getLEDBrightness(int, int *)
    kSetLEDBrightnessID   = 2,  // setLEDBrightness(int, int, int *)
    kSetLEDFadeID         = 3,  // setLEDFade(int, int, int, int *)

    // other firmware-related functions
    // verifyFirmwareID     = 4,  // verifyFirmware(int *)
    // getFirmwareVersionID = 5,  // getFirmwareVersion(int *)

    // other flashing-related functions
    // ...
};

/* This defines the connection used by the IOConnectCall methods. Must be set
 * by the startLightService function before being used. */ 
static io_connect_t connect = 0;

/* This function performs initialization work to ensure that the connection to
 * the service performing keyboard LED modifications is open. It modifies the
 * io_connect_t connect used throughout the implementation. */
void startLightService() {
  kern_return_t kr;
  io_service_t serviceObject;

  // Find a service object for the controller.
  serviceObject = IOServiceGetMatchingService(kIOMasterPortDefault,
    IOServiceMatching("AppleLMUController"));

  // Check a matching service object was found
  if (!serviceObject) {
    fprintf(stderr, "Failed to find service matching \"AppleLMUController\".\
        Ending program.");
    exit(1);
  }
  
  // Open the matching service. The static variable connect is used to allow
  // communication with the IOConnect APIs.
  kr = IOServiceOpen(serviceObject, mach_task_self(), 0, &connect);

  // Release the service object and clean up, checking for errors.
  IOObjectRelease(serviceObject);
  if(kr != KERN_SUCCESS) {
    mach_error("IOServiceOpen: ", kr);
    exit(kr);
  }
}

/* Returns a value between 0 and 0xfff indicating the brightness of the
 * keyboard LED light. */
uint64_t getKeyboardLEDValue() {
  kern_return_t kr;
  IOItemCount inputCount = 1;
  IOItemCount outputCount = 1;
  uint64_t outValue = 5;
  const uint64_t fakeInput = 0; // Function requires fake input.

  kr = IOConnectCallMethod(connect, kGetLEDBrightnessID, &fakeInput, inputCount, nil,
    0, &outValue, &outputCount, nil, 0);
  if (kr != KERN_SUCCESS) {
    mach_error("IOConnectCallMethod: ", kr);
  }
  return outValue;
}

/* Sets the keyboard LED brightness to a value between 0 and 0xfff. */
void setKeyboardLEDValue(uint64_t ledValue) {
  if (ledValue > 0xfff) {
    fprintf(stderr, "ledValue is higher than the maximum value, 0xfff. Ending\
        program to avoid hardware funkiness.");
    exit(1);
  }
  kern_return_t kr;
  IOItemCount inputCount = 2; // 2 inputs are needed because of fake input var.
  IOItemCount outputCount = 1; // Fake output is needed.
  uint64_t fakeOutput = 0;
  uint64_t inValues[2];
  inValues[0] = 0;
  inValues[1] = ledValue;
  
  kr = IOConnectCallMethod(connect, kSetLEDBrightnessID, inValues, inputCount,
      nil, 0, &fakeOutput, &outputCount, nil, 0);
  if (kr != KERN_SUCCESS) {
    mach_error("IOConnectCallMethod: ", kr);
  }
}

/* Set keyboard LED brightness to a value between 0 and 0xfff, fading the
   change in brightness over time_ms milliseconds. */
void setKeyboardLEDValueFade(uint64_t ledValue, uint64_t time_ms) {
  if (ledValue > 0xfff) {
    fprintf(stderr, "ledValue is higher than the maximum value, 0xfff. Ending\
        program to avoid hardware funkiness.");
    exit(1);
  }
  kern_return_t kr;
  IOItemCount inputCount = 3; // 3 inputs are needed because of fake input var.
  IOItemCount outputCount = 1; // Fake output is needed.
  uint64_t fakeOutput = 0;
  uint64_t inValues[3];
  inValues[0] = 0;
  inValues[1] = ledValue;
  inValues[2] = time_ms;
  
  kr = IOConnectCallMethod(connect, kSetLEDFadeID, inValues, inputCount,
      nil, 0, &fakeOutput, &outputCount, nil, 0);
  if (kr != KERN_SUCCESS) {
    mach_error("IOConnectCallMethod: ", kr);
  }
}
