# Welcome to ARDVARC

<acronym style="cursor:help;text-decoration:underline;" title="Autonomous Radioactive Debris Verification Acquisition and Retrieval
Coordinator">ARDVARC</acronym> is an autonomous vehicle designed to collect radioactive waste.

This directory contains the code behind ARDVARC, including libraries used and written.

## Important!

If you want to build this code, then you will need to **change the Arduino IDE sketchbook path to the repository root** on your local hard drive. If you don't, then you're going to get an error like <span style="color:red;">"fatal error: DriveControl.h: No such file or directory"</span>.

For example, if I clone the repository into `C:\Some\Path\ARDVARC`, then I will need to go into the Arduino IDE and change the sketchbook directory to match. You can do this by going to `File > Preferences` and changing `Sketchbook Location` then restarting the Arduino IDE.

The reason you need to change the sketchbook location, is that Arduino can only handle importing libraries (with `#include`) that are located in the `<Sketchbook>\libraries` folder. The lack of support for local libraries is a limitation of the Arduino compiler itself, and makes code sharing a bit more complex. Luckily, it can be easily worked around by following the above steps.


### Developer Information

The ARDVARC code was developed with **Arduino IDE 1.8.1**

The code is meant to run on an Arduino UNO Rev3

**See the libraries folder README for recognition of external code.**