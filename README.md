WizardKeys v0.1
By Mario Villaplana

This project has not been worked on in many years.

HOW TO COMPILE AND RUN:

Type the following commands in terminal while in the folder holding WizardKeys:

```
gcc -o WizardKeys WizardKeys.c -framework IOKit -framework ApplicationServices
-framework CoreFoundation

sudo ./WizardKeys
```

sudo is needed because certain versions of OS X require root permissions to
create the event tap.

This is a keyboard mod for Mac laptops running OS X 10.6 and above. Every time
you press a key with WizardKeys running in the background, the program switches
the keyboard LEDs on and off, giving you the 1337 appearance of a h4x0r wizard
casting spells with a computer

A small API for modifying and reading keyboard LED brightness programatically
is also included in MacKeyLEDAPI.h/c. Feel free to use this in your own
projects.

TODO if I continue working on this hack:
0. Create a Makefile.
1. Make a nice package/daemon with a small GUI.
2. Enable other wizardry, such as having lights fade on and off with key
presses, having lights turn on when the user presses keys and fade away when
not in use, etc.
3. Enable functionality for OS X 10.5 and below if requested. Test on Lion.
