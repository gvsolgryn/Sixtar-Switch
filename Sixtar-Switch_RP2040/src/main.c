#include "include/main.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+
Button_Status btn_stat;
Hat_Status hat_stat;
Hat_Button_Status hat_btn_stat;

USB_JoystickReport_Input_t ns_report;
hid_gamepad_report_t report;

static void send_hid_report(uint8_t report_id, uint32_t btn) {
    // skip if hid is not ready yet
    if (tud_hid_ready()) {
		board_led_on();
	}
	else {
		board_led_off();
		return;
	}
    switch(btn) {
        case 0: {
            report.hat = 0;
            ns_report.Button = 0;

            break;
        }

        case 1: {
            report.hat = GAMEPAD_HAT_UP;

            ns_report.Button |= NS_BUTTON_L;
            ns_report.Button |= NS_BUTTON_R;

            break;
        }

        default: {
            memset(&ns_report, 0x00, sizeof(USB_JoystickReport_Input_t));
            memset(&report, 0x00, sizeof(hid_gamepad_report_t));

            break;
        }
    }

    ns_report.Button += btn_stat.Y == 0 ? NS_BUTTON_Y : 0x0000; // minus?
    ns_report.Button += btn_stat.B == 0 ? NS_BUTTON_B : 0x0000; // plus?
    ns_report.Button += btn_stat.A == 0 ? NS_BUTTON_A : 0x0000; // lclick?
    ns_report.Button += btn_stat.X == 0 ? NS_BUTTON_X : 0x0000; // rclick?
    ns_report.Button += btn_stat.L == 0 ? NS_BUTTON_L : 0x0000; // home?
    ns_report.Button += btn_stat.R == 0 ? NS_BUTTON_R : 0x0000; // capture?
    ns_report.Button += btn_stat.ZL == 0 ? NS_BUTTON_ZL : 0x0000; // none?
    ns_report.Button += btn_stat.ZR == 0 ? NS_BUTTON_ZR : 0x0000; // none?
    ns_report.Button += btn_stat.MINUS == 0 ? NS_BUTTON_MINUS : 0x0000; // why hat btn?
    ns_report.Button += btn_stat.PLUS == 0 ? NS_BUTTON_PLUS : 0x0000; // why hat btn?
    ns_report.Button += btn_stat.LCLICK == 0 ? NS_BUTTON_LCLICK : 0x0000; // why hat btn?
    ns_report.Button += btn_stat.RCLICK == 0 ? NS_BUTTON_RCLICK : 0x0000; // why hat btn?
    ns_report.Button += btn_stat.HOME == 0 ? NS_BUTTON_HOME : 0x0000; // why hat btn?
    ns_report.Button += btn_stat.CAPTUR == 0 ? NS_BUTTON_CAPTURE : 0x0000; // why hat btn?

    tud_hid_report(report_id, &ns_report, sizeof(ns_report));
	tud_hid_report(report_id, &report, sizeof(report));
    

	memset(&btn_stat, 0, sizeof(Button_Status));
    memset(&hat_stat, 0, sizeof(Hat_Status));
    memset(&hat_btn_stat, 0, sizeof(Hat_Button_Status));
    memset(&ns_report, 0, sizeof(USB_JoystickReport_Input_t));
    memset(&report, 0, sizeof(hid_gamepad_report_t));
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

    btn_stat.Y = gpio_get(GPIO_1);
    btn_stat.B = gpio_get(GPIO_2);
    btn_stat.A = gpio_get(GPIO_3);
    btn_stat.X = gpio_get(GPIO_4);
    btn_stat.L = gpio_get(GPIO_5);
    btn_stat.R = gpio_get(GPIO_6);
    btn_stat.ZL = gpio_get(GPIO_7);
    btn_stat.ZR = gpio_get(GPIO_8);
    btn_stat.MINUS = gpio_get(GPIO_9);
    btn_stat.PLUS = gpio_get(GPIO_10);
    btn_stat.LCLICK = gpio_get(GPIO_11);
    btn_stat.RCLICK = gpio_get(GPIO_12);
    btn_stat.HOME = gpio_get(GPIO_13);
    btn_stat.CAPTUR = gpio_get(GPIO_14);

    send_hid_report(REPORT_ID_GAMEPAD, btn);

    return;
}

void init() {
    for(int i = 0; i < BUTTON_COUNT; i++) {
        gpio_init(i);

        gpio_set_dir(i, GPIO_IN);

        gpio_pull_up(i);
    }

    memset(&btn_stat, 0, sizeof(Button_Status));
    memset(&hat_stat, 0, sizeof(Hat_Status));
    memset(&hat_btn_stat, 0, sizeof(Hat_Button_Status));
    memset(&ns_report, 0, sizeof(USB_JoystickReport_Input_t));
    memset(&report, 0, sizeof(hid_gamepad_report_t));

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