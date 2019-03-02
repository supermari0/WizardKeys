WizardKeys v0.1
By Mario Villaplana

This project has not been worked on in a few years. If it doesn't work for you,
ping me and I'll take a look.

HOW TO COMPILE AND RUN:

Type the following commands in a terminal while in the folder holding
WizardKeys:

```
gcc -o WizardKeys WizardKeys.c -framework IOKit -framework ApplicationServices
-framework CoreFoundation

sudo ./WizardKeys
```

You can install gcc and the necessary frameworks by installing XCode developer
tools.

sudo is needed because certain versions of macOS/OS X require root permissions
to create the event tap.

This is a keyboard mod for Mac laptops running OS X 10.6 and above. Every time
you press a key with WizardKeys running in the background, the program switches
the keyboard LEDs on and off with each press. It looks pretty neat!

A small API for modifying and reading keyboard LED brightness programatically
is also included in MacKeyLEDAPI.h/c. Feel free to use this in your own
projects.

TODO if I continue working on this:
0. Create a Makefile.
1. Make a nice package/daemon with a small GUI.
2. Enable other features, such as having lights fade on and off with key
presses, having lights turn on when the user presses keys and fade away when
not in use, etc.
