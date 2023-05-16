#include "include/main.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+
button_status btn_stat = {
    .A = 0,
    .B = 0,
    .X = 0,
    .Y = 0,
    .CAPTUR = 0,
    .HOME = 0,
    .L = 0,
    .LCLICK = 0,
    .MINUS = 0,
    .PLUS = 0,
    .R = 0,
    .RCLICK = 0
};

static void send_hid_report(uint8_t report_id, uint32_t btn) {
    // skip if hid is not ready yet
    if (!tud_hid_ready())
        return;

    hid_gamepad_report_t report = {
        .x			= 0,
        .y			= 0,
        .z			= 0,
        .rx			= 0,
        .ry			= 0,
        .rz			= 0,
        .hat		= 0,
        .buttons	= 0
    };

    switch(btn) {
        case 0: {
            report.hat = 0;

            break;
        }

        case 1: {
            report.hat = GAMEPAD_HAT_UP;

            break;
        }

        default : {
            report.x = 0;
            report.y = 0;
            report.z = 0;
            report.rx = 0;
            report.ry = 0;
            report.rz = 0;
            report.hat = 0;
            report.buttons = 0;

            break;
        }
    }

    report.buttons += btn_stat.A == 0 ? GAMEPAD_BUTTON_A : 0x0000;
    report.buttons += btn_stat.B == 0 ? GAMEPAD_BUTTON_B : 0x0000;
    report.buttons += btn_stat.X == 0 ? GAMEPAD_BUTTON_X : 0x0000;
    report.buttons += btn_stat.Y == 0 ? GAMEPAD_BUTTON_Y : 0x0000;

    tud_hid_report(report_id, &report, sizeof(report));
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

    btn_stat.A = gpio_get(BUTTON_1);
    btn_stat.B = gpio_get(BUTTON_2);
    btn_stat.X = gpio_get(BUTTON_3);
    btn_stat.Y = gpio_get(BUTTON_4);

    board_led_write((bool)btn);

    gpio_get_dir(BUTTON_1) ? board_led_off() : board_led_on();

    send_hid_report(REPORT_ID_GAMEPAD, btn);

    return;
}

void init() {
    for(int i = 0; i < BUTTON_COUNT; i++) {
        gpio_init(i);

        gpio_set_dir(i, GPIO_IN);

        gpio_pull_up(i);
    }

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