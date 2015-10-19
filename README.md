# DWAVDriver
A user-side driver for a "D-WAV Scientific Co., Ltd" screen.

By user-side, I mean that you don't need to modify/patch/recompile your kernel. It's just a little software that read in the HID file and simulate a mouse with X11.


## Features :

* Moving the mouse.

* Left Click.

* Calibration tool.


## How to use it :

* Clone the repository.

* install the software : `sudo ./install.sh`

* calibrate the screen : `sudo calibrateDWAV [XRES] [YRES]` 

 * In order to calibrate the screen, slide your finger on the 4 edge and corners of the screen.

 * Most important corners are top-left and bottom-right ones

* reboot.

 * Auto startup of the driver only works on distros using systemctl (tested on Archlinux), feel free to change the install.sh

* Enjoy.


## Want to contribute ?

 * Fork the repository

 * Create a new branch to work on.

 * Make sure it really works

 * Make a pull request


## License :

MIT
