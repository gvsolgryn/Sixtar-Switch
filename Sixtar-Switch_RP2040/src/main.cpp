#include "include/main.h"
#include "include/switch_tinyusb.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "EndlessLoop"
NSGamepad gamepad;

int setup() {
    board_init();
    tusb_init();

    for(int i = 0; i < BUTTON_COUNT; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_up(i);
    }

    return true;
}

void loop() {
    tud_task(); // tinyusb device task

    update_input();
}

// Every 1ms, we will send 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void update_input() {
    const uint32_t interval_ms	= 1;
    static uint32_t start_ms 	= 0;

    if (board_millis() - start_ms < interval_ms)
        return;
    
    start_ms += interval_ms;

    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (gpio_get(buttonPins[i]) != 1) {
            gamepad.press(i);
        }
        else {
            gamepad.release(i);
        }
    }

    if (!gamepad.ready())
        board_led_off();
    else {
        board_led_on();
        gamepad.write();
    }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    // Implementation

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance;

    if (report_type == HID_REPORT_TYPE_OUTPUT) {

    }
}

/*------------- MAIN -------------*/
int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
#pragma clang diagnostic pop