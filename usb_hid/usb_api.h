#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "keylayouts.h"
#include "Print.h"
#include "Stream.h"

extern uint8_t joystick_report_data[12];

class usb_joystick_class
{
	public:
	usb_joystick_class() { manual_mode = 0; }
	inline void button(uint8_t button, bool val) {
		button--;
		uint8_t mask = (1 << (button & 7));
		if (val) {
			if (button < 8) joystick_report_data[0] |= mask;
			else if (button < 16) joystick_report_data[1] |= mask;
			else if (button < 24) joystick_report_data[2] |= mask;
			else if (button < 32) joystick_report_data[3] |= mask;
		} else {
			mask = ~mask;
			if (button < 8) joystick_report_data[0] &= mask;
			else if (button < 16) joystick_report_data[1] &= mask;
			else if (button < 24) joystick_report_data[2] &= mask;
			else if (button < 32) joystick_report_data[3] &= mask;
		}
		if (!manual_mode) send_now();
	}
	inline void X(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[4] = (joystick_report_data[4] & 0x0F) | (val << 4);
		joystick_report_data[5] = (joystick_report_data[5] & 0xC0) | (val >> 4);
		if (!manual_mode) send_now();
	}
	inline void Y(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[5] = (joystick_report_data[5] & 0x3F) | (val << 6);
		joystick_report_data[6] = (val >> 2);
		if (!manual_mode) send_now();
	}
	inline void position(uint16_t x, uint16_t y) {
		if (x > 1023) x = 1023;
		if (y > 1023) y = 1023;
		joystick_report_data[4] = (joystick_report_data[4] & 0x0F) | (x << 4);
		joystick_report_data[5] = (x >> 4) | (y << 6);
		joystick_report_data[6] = (y >> 2);
		if (!manual_mode) send_now();
	}
	inline void Z(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[7] = val;
		joystick_report_data[8] = (joystick_report_data[8] & 0xFC) | (val >> 8);
		if (!manual_mode) send_now();
	}
	inline void Zrotate(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[8] = (joystick_report_data[8] & 0x03) | (val << 2);
		joystick_report_data[9] = (joystick_report_data[9] & 0xF0) | (val >> 6);
		if (!manual_mode) send_now();
	}
	inline void sliderLeft(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[9] = (joystick_report_data[9] & 0x0F) | (val << 4);
		joystick_report_data[10] = (joystick_report_data[10] & 0xC0) | (val >> 4);
		if (!manual_mode) send_now();
	}
	inline void sliderRight(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[10] = (joystick_report_data[10] & 0x3F) | (val << 6);
		joystick_report_data[11] = (val >> 2);
		if (!manual_mode) send_now();
	}
	inline void slider(uint16_t val) {
		if (val > 1023) val = 1023;
		joystick_report_data[9] = (joystick_report_data[9] & 0x0F) | (val << 4);
		joystick_report_data[10] = (val >> 4) | (val << 6);
		joystick_report_data[11] = (val >> 2);
		if (!manual_mode) send_now();
	}
	inline void hat(int16_t dir) {
		uint8_t val;
		if (dir < 0) val = 15;
		else if (dir < 23) val = 0;
		else if (dir < 68) val = 1;
		else if (dir < 113) val = 2;
		else if (dir < 158) val = 3;
		else if (dir < 203) val = 4;
		else if (dir < 245) val = 5;
		else if (dir < 293) val = 6;
		else if (dir < 338) val = 7;
		joystick_report_data[4] = (joystick_report_data[4] & 0xF0) | val;
		if (!manual_mode) send_now();
	}
	inline void useManualSend(bool mode) {
		manual_mode = mode;
	}
	void send_now(void);
	private:
	//static uint8_t manual_mode;
	uint8_t manual_mode;
};

extern usb_joystick_class Joystick;


#endif
