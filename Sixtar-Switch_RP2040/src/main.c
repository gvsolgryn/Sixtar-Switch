#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

enum btnEnum {
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_COUNT
};

typedef struct _BUTTON_STATUS_ {
	uint8_t HAT_UP;
	uint8_t HAT_DOWN;
	uint8_t HAT_LEFT;
	uint8_t HAT_RIGHT;
} button_state;

static void send_hid_report(uint8_t report_id, button_state *btn_state) {
	// skip if hid is not ready yet
	if (!tud_hid_ready())
		return;

	if(report_id == REPORT_ID_GAMEPAD) {
		hid_gamepad_report_t report = {
			.x			= 0,
			.y			= 0,
			.z			= 0,
			.rz			= 0,
			.ry			= 0,
			.rz			= 0,
			.hat		= 0,
			.buttons	= 0
		};

		// TEST Code

		if(btn_state->HAT_UP) {
			report.hat 		= GAMEPAD_HAT_UP;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}
		else {
			report.hat 		= GAMEPAD_HAT_CENTERED;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}

		if(btn_state->HAT_DOWN) {
			report.hat 		= GAMEPAD_HAT_DOWN;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}
		else {
			report.hat 		= GAMEPAD_HAT_CENTERED;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}

		if(btn_state->HAT_LEFT) {
			report.hat 		= GAMEPAD_HAT_LEFT;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}
		else {
			report.hat 		= GAMEPAD_HAT_CENTERED;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}

		if(btn_state->HAT_RIGHT) {
			report.hat 		= GAMEPAD_HAT_RIGHT;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}
		else {
			report.hat 		= GAMEPAD_HAT_CENTERED;

			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
		}
	}
}

// Every 1ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
static void update_input() {
	const uint32_t interval_ms	= 1;
	static uint32_t start_ms 	= 0;

	if (board_millis() - start_ms < interval_ms)
		return;
	
	start_ms += interval_ms;

	uint32_t const btn = board_button_read();

	button_state *btn_state;

	btn_state->HAT_UP 		= gpio_get_dir(BUTTON_1);
	btn_state->HAT_DOWN 	= gpio_get_dir(BUTTON_2);
	btn_state->HAT_LEFT 	= gpio_get_dir(BUTTON_3);
	btn_state->HAT_RIGHT 	= gpio_get_dir(BUTTON_4);

	board_led_write((bool)btn);

	send_hid_report(REPORT_ID_GAMEPAD, btn_state);

	return;
}

void init() {
	for(int i = 0; i < BUTTON_COUNT; i++) {
		gpio_init(i);

		gpio_set_dir(i, GPIO_IN);

		gpio_pull_down(i);
	}

	return;
}

/*------------- MAIN -------------*/
int main(void)
{
	board_init();
	tusb_init();

	while (1) {
		tud_task(); // tinyusb device task

		update_input();
	}

	return 0;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
	// TODO not Implemented
	(void) instance;
	(void) report_id;
	(void) report_type;
	(void) buffer;
	(void) reqlen;

	return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
	(void) instance;

	if (report_type == HID_REPORT_TYPE_OUTPUT) {

	}
}