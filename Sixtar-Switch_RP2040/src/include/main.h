#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

#define NS_BUTTON_Y          0x0001 // minus?
#define NS_BUTTON_B          0x0002 // plus?
#define NS_BUTTON_A          0x0004 // lclick?
#define NS_BUTTON_X          0x0008 // rclick?
#define NS_BUTTON_L          0x0010 // home?
#define NS_BUTTON_R          0x0020 // capture?
#define NS_BUTTON_ZL         0x0040
#define NS_BUTTON_ZR         0x0080
#define NS_BUTTON_MINUS      0x0100
#define NS_BUTTON_PLUS       0x0200
#define NS_BUTTON_LCLICK     0x0400
#define NS_BUTTON_RCLICK     0x0800
#define NS_BUTTON_HOME       0x1000
#define NS_BUTTON_CAPTURE    0x2000

enum {
    PICO_GPIO_1_ON      = 0x00000001,
    PICO_GPIO_2_ON      = 0x00000002,
    PICO_GPIO_3_ON      = 0x00000004,
    PICO_GPIO_4_ON      = 0x00000008,
    PICO_GPIO_5_ON      = 0x00000010,
    PICO_GPIO_6_ON      = 0x00000020,
    PICO_GPIO_7_ON      = 0x00000040,
    PICO_GPIO_8_ON      = 0x00000080,
    PICO_GPIO_9_ON      = 0x00000100,
    PICO_GPIO_10_ON     = 0x00000200,
    PICO_GPIO_11_ON     = 0x00000400,
    PICO_GPIO_12_ON     = 0x00000800,
    PICO_GPIO_13_ON     = 0x00001000,
    PICO_GPIO_14_ON     = 0x00002000,
    PICO_GPIO_15_ON     = 0x00004000,
    PICO_GPIO_16_ON     = 0x00008000,
    PICO_GPIO_17_ON     = 0x00010000,
    PICO_GPIO_18_ON     = 0x00020000,
    PICO_GPIO_19_ON     = 0x00040000,
    PICO_GPIO_20_ON     = 0x00080000,
    PICO_GPIO_21_ON     = 0x00100000,
    PICO_GPIO_22_ON     = 0x00200000,
    PICO_GPIO_23_ON     = 0x00400000,
    PICO_GPIO_24_ON     = 0x00800000,
    PICO_GPIO_25_ON     = 0x01000000,
    PICO_GPIO_26_ON     = 0x02000000,
    PICO_GPIO_27_ON     = 0x04000000,
    PICO_GPIO_28_ON     = 0x08000000,
    PICO_GPIO_29_ON     = 0x10000000
};

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

typedef struct {
    uint16_t Button;
    uint8_t Hat;
    uint8_t LX;
    uint8_t LY;
    uint8_t RX;
    uint8_t RY;
    uint8_t VendorSpec;
} USB_JoystickReport_Input_t;

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

typedef struct {
    uint16_t Y;
    uint16_t B;
    uint16_t A;
    uint16_t X;
    uint16_t L;
    uint16_t R;
    uint16_t ZL;
    uint16_t ZR;
    uint16_t MINUS;
    uint16_t PLUS;
    uint16_t LCLICK;
    uint16_t RCLICK;
    uint16_t HOME;
    uint16_t CAPTUR;
} Button_Status;

typedef struct {
    uint8_t UP;
    uint8_t UP_RIGHT;
    uint8_t RIGHT;
    uint8_t DOWN_RIGHT;
    uint8_t DOWN;
    uint8_t DOWN_LEFT;
    uint8_t LEFT;
    uint8_t UP_LEFT;
    uint8_t NEUTRAL;
} Hat_Status;

typedef struct {
    uint8_t UP;
    uint8_t RIGHT;
    uint8_t DOWN;
    uint8_t LEFT;
} Hat_Button_Status;