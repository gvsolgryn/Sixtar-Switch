#include "include/main.h"
#include "include/switch_tinyusb.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "EndlessLoop"
NSGamepad gamepad;

void setup() {
    board_init();
    tusb_init();

    for (unsigned char buttonPin : buttonPins) {
        gpio_init(buttonPin);
        gpio_set_dir(buttonPin, GPIO_IN);
        gpio_pull_up(buttonPin);
    }

    for (unsigned char axisPin : axisPins) {
        gpio_init(axisPin);
        gpio_set_dir(axisPin, GPIO_IN);
        gpio_pull_up(axisPin);
    }
}

void loop() {
    tud_task(); // tinyusb device task

    update_input();
}

// Every 1ms, we will send 1 report for each HID profile (keyboard, mouse etc …)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void update_input() {
    const uint32_t interval_ms	= 1;
    static uint32_t start_ms 	= 0;

    if (board_millis() - start_ms < interval_ms)
        return;
    
    start_ms += interval_ms;

    uint8_t leftXAxisBtn = gpio_get(axisPins[0]);
    uint8_t rightXAxisBtn = gpio_get(axisPins[1]);

    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (gpio_get(buttonPins[i]) != 1) {
            gamepad.press(i);
        }
        else {
            gamepad.release(i);
        }
    }

    if (leftXAxisBtn != 1) {
        gamepad.leftXAxis(0);
    }
    else {
        gamepad.leftXAxis(128);
    }

    if (rightXAxisBtn != 1) {
        gamepad.rightXAxis(255);
    }
    else {
        gamepad.rightXAxis(128);
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