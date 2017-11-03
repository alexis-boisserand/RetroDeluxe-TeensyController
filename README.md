# RetroDeluxe-TeensyController

This is the code for the teensy 2.0 firmware of the RetroDeluxe handheld game console. It reads the buttons and analog joystick input values and acts as an USB HID device for the raspberry pi.

## Compilation

### Prerequisites 

You must have the Arduino IDE installed with Teensyduino. Check this link for more information: https://www.pjrc.com/teensy/td_download.html

For compiling this code, you first need to copy/overwrite the usb_hid folder in the \<Arduino installation path>/hardware/teensy/avr/cores folder. If you don't, three different USB devices (keyboard, mouse and joystick) will be enumerated and Lakka will get confused. With this modification, only one the joystick is enumerated.
Once copied, launch the arduino IDE and compile the controller.ino file making sure that in the "Tools" menu the "Board" is "Teensy 2.0" and the "USB Type" is "Keyboard + Mouse + Joystick".
Load the firmware following the instructions on the teensy website and you are good to go.
