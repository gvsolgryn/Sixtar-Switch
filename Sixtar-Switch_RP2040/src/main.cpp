#include "include/main.h"
#include "include/switch_tinyusb.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

HID_NSGamepadReport_Data_t ns_report;

static void send_hid_report(uint8_t report_id, uint32_t btn) {
    // Check if HID is ready first
    if (!tud_hid_ready()) {
        board_led_off();
        return; // Exit if HID is not ready
    }

    memset(&ns_report, 0, sizeof(HID_NSGamepadReport_Data_t));

    switch(btn) {
        case 1: {
            ns_report.buttons |= NSButton_A;
            break;
        }
        default: {
            break;
        }
    }

    board_led_on();
    tud_hid_report(report_id, &ns_report, sizeof(ns_report));
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

    send_hid_report(REPORT_ID_GAMEPAD, btn);

    return;
}

void init() {
    for(int i = 0; i < BUTTON_COUNT; i++) {
        gpio_init(i);

        gpio_set_dir(i, GPIO_IN);

        gpio_pull_up(i);
    }

    memset(&ns_report, 0, sizeof(HID_NSGamepadReport_Data_t));

    return;
}

/*------------- MAIN -------------*/
int main(void)
{
    init();
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
/*
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    // TODO not Implemented
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}
*/

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    if (report_id == REPORT_ID_GAMEPAD && report_type == HID_REPORT_TYPE_INPUT) {
        memcpy(buffer, &ns_report, sizeof(ns_report));
        return sizeof(ns_report);
    }
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance;

    if (report_type == HID_REPORT_TYPE_OUTPUT) {

    }
}