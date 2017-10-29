#include <Bounce.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// The first number corresponds to the pin number and the second number to the button number. See https://www.pjrc.com/teensy/td_joystick.html for more information.
const uint8_t buttonsMap[][2] = {
  {21, 7},  // L3
  {18, 9},  // SELECT
  {17, 10}, // START
  {16, 8},  // R3
  {10, 3},  // A
  {9, 2},   // B
  {8, 1},   // Y
  {7, 4},   // X
  {6, 6},   // R
  {4, 5}    // L
};

const int buttonsMapSize = ARRAY_SIZE(buttonsMap);

Bounce* buttons[buttonsMapSize];

// Pin numbers used by the dpad
const uint8_t down = 2;
const uint8_t right = 0;
const uint8_t up = 3;
const uint8_t left = 1;

const uint8_t dpadButtons[] = {up, right, down, left};

const int dpadButtonsSize = ARRAY_SIZE(dpadButtons);

void setup() {

  // configure the joystick to manual send mode.  This gives precise
  // control over when the computer receives updates, but it does
  // require you to manually call Joystick.send_now().
  Joystick.useManualSend(true);
  
  for (int i = 0; i < buttonsMapSize; ++i) {
    const uint8_t pin = buttonsMap[i][0];
    buttons[i] = new Bounce(pin, 10);
    pinMode(pin, INPUT_PULLUP);
  }
  for (int i = 0; i < dpadButtonsSize; ++i) {
    pinMode(dpadButtons[i], INPUT_PULLUP);
  }
}

void loop() {
  // read 6 analog inputs and use them for the joystick axis
  Joystick.X(analogRead(2));
  // we need to invert the y axis
  Joystick.Y(1023 - analogRead(1));
  Joystick.Z(analogRead(6));
  Joystick.Zrotate(analogRead(7));

  // read digital pins and use them for the buttons
  for (int i = 0; i < buttonsMapSize; ++i) {
    const uint8_t* buttonMapping = buttonsMap[i];
    buttons[i]->update();

    if (buttons[i]->fallingEdge()) {
      Joystick.button(buttonMapping[1], 1);
    }

    if (buttons[i]->risingEdge()) {
      Joystick.button(buttonMapping[1], 0);
    }
  }

  uint8_t dpadValue = 0;
  for (int i = 0; i < dpadButtonsSize; ++i) {
    const int value = !digitalRead(dpadButtons[i]);
    dpadValue |= value << i; 
  }

  int angle = 0;
  switch(dpadValue) {
    case 0x0:
      // no button pressed, return to the rest position
      angle = -1;
      break;
    case 0x1:
      angle = 0;
      break;
    case 0x2:
      angle = 90;
      break;
    case 0x3:
      angle = 45;
      break;
    case 0x4:
      angle = 180;
      break;
    case 0x6:
      angle = 135;
      break;   
    case 0x8:
      angle = 270;
      break;
    case 0xC:
      angle = 225;
      break;
    case 0x9:
      angle = 315;
      break;
  }

  Joystick.hat(angle);
  Joystick.send_now();
  delay(50);
}

