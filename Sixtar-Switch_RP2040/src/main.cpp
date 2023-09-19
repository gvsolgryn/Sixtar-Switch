#include "include/main.h"
#include "include/switch_tinyusb.h"

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

    for (unsigned char dpadPin : dPadPins) {
        gpio_init(dpadPin);
        gpio_set_dir(dpadPin, GPIO_IN);
        gpio_pull_up(dpadPin);
    }
}

void loop() {
    tud_task(); // tinyusb device task

    update_input();
}

void update_input() {
    const uint32_t interval_ms	= 1;
    static uint32_t start_ms 	= 0;

    if (board_millis() - start_ms < interval_ms)
        return;

    start_ms += interval_ms;

    updateButtons();
    updateLeftXAxis();
    updateRightXAxis();
    updateDPad();

    if (!Gamepad.ready())
        board_led_off();
    else {
        board_led_on();
        Gamepad.write();
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