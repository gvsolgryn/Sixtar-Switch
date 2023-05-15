#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

enum btnEnum {
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_COUNT
};

typedef struct {
	uint8_t HAT_UP;
	uint8_t HAT_DOWN;
	uint8_t HAT_LEFT;
	uint8_t HAT_RIGHT;
} button_state;

struct Button
{
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
    uint16_t CAPTURE;
} button = {
    0x0001,
    0x0002,
    0x0004,
    0x0008,
    0x0010,
    0x0020,
    0x0040,
    0x0080,
    0x0100,
    0x0200,
    0x0400,
    0x0800,
    0x1000,
    0x2000
};

struct Hat
{
    uint8_t UP;
    uint8_t UP_RIGHT;
    uint8_t RIGHT;
    uint8_t DOWN_RIGHT;
    uint8_t DOWN;
    uint8_t DOWN_LEFT;
    uint8_t LEFT;
    uint8_t UP_LEFT;
    uint8_t NEUTRAL;
} hat = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x08
};

struct HatButton
{
    uint8_t UP;
    uint8_t RIGHT;
    uint8_t DOWN;
    uint8_t LEFT;
}hat_btn = {
    0b0001,
    0b0010,
    0b0100,
    0b1000
};