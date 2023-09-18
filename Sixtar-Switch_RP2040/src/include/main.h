#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

// #define NS_BUTTON_Y          0x0001 // minus?
// #define NS_BUTTON_B          0x0002 // plus?
// #define NS_BUTTON_A          0x0004 // lclick?
// #define NS_BUTTON_X          0x0008 // rclick?
// #define NS_BUTTON_L          0x0010 // home?
// #define NS_BUTTON_R          0x0020 // capture?
// #define NS_BUTTON_ZL         0x0040
// #define NS_BUTTON_ZR         0x0080
// #define NS_BUTTON_MINUS      0x0100
// #define NS_BUTTON_PLUS       0x0200
// #define NS_BUTTON_LCLICK     0x0400
// #define NS_BUTTON_RCLICK     0x0800
// #define NS_BUTTON_HOME       0x1000
// #define NS_BUTTON_CAPTURE    0x2000

enum HAT {
    NS_HAT_UP             = 0x00,
    NS_HAT_UP_RIGHT       = 0x01,
    NS_HAT_RIGHT          = 0x02,
    NS_HAT_DOWN_RIGHT     = 0x03,
    NS_HAT_DOWN           = 0x04,
    NS_HAT_DOWN_LEFT      = 0x05,
    NS_HAT_LEFT           = 0x06,
    NS_HAT_UP_LEFT        = 0x07,
    NS_HAT_NEUTRAL        = 0x08
};

enum HAT_BTN {
    NS_HAT_BTN_UP         = 0b0001,
    NS_HAT_BTN_RIGHT      = 0b0010,
    NS_HAT_BTN_DOWN       = 0b0100,
    NS_HAT_BTN_LEFT       = 0b1000
};

enum NS_STICK {
    NS_STICK_MIN          = 0,
    NS_STICK_NEUTRAL      = 128,
    NS_STICK_MAX          = 255
};

// typedef struct {
//     uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
//     uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
//     uint8_t  LX;     // Left  Stick X
//     uint8_t  LY;     // Left  Stick Y
//     uint8_t  RX;     // Right Stick X
//     uint8_t  RY;     // Right Stick Y
//     uint8_t  VendorSpec;
// } USB_JoystickReport_Input_t;

enum {
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    BUTTON_COUNT
};