#include "hardware/gpio.h"
#include "include/switch_tinyusb.h"

#define BUTTON_COUNT 14
#define AXIS_COUNT 2
#define DPAD_COUNT 4

NSGamepad Gamepad;

void setup();
void loop();
void update_input();
void updateButtons();
void updateLeftXAxis();
void updateRightXAxis();
void updateDPad();

uint8_t buttonPins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
uint8_t axisPins[] = { 14, 15 };
uint8_t dPadPins[] = { 15, 16, 17, 18 };

void updateButtons() {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (gpio_get(buttonPins[i]) != 1) {
            Gamepad.press(i);
        }
        else {
            Gamepad.release(i);
        }
    }
}

void updateLeftXAxis() {
    uint8_t leftXAxisBtn = gpio_get(axisPins[0]);

    if (leftXAxisBtn != 1) {
        Gamepad.leftXAxis(0);
    }
    else {
        Gamepad.leftXAxis(128);
    }
}

void updateRightXAxis() {
    uint8_t rightXAxisBtn = gpio_get(axisPins[1]);

    if (rightXAxisBtn != 1) {
        Gamepad.rightXAxis(255);
    }
    else {
        Gamepad.rightXAxis(128);
    }
}

void updateDPad() {
    uint8_t up    = gpio_get(dPadPins[0]);
    uint8_t down  = gpio_get(dPadPins[1]);
    uint8_t left  = gpio_get(dPadPins[2]);
    uint8_t right = gpio_get(dPadPins[3]);

    NSDirection_t direction;

    if (up && !down) {
        if (left && !right) direction = NSGAMEPAD_DPAD_UP_LEFT;
        else if (!left && right) direction = NSGAMEPAD_DPAD_UP_RIGHT;
        else direction = NSGAMEPAD_DPAD_UP;
    }
    else if (!up && down) {
        if (left && !right) direction = NSGAMEPAD_DPAD_DOWN_LEFT;
        else if (!left && right) direction = NSGAMEPAD_DPAD_DOWN_RIGHT;
        else direction = NSGAMEPAD_DPAD_DOWN;
    }
    else if (left && !right) direction = NSGAMEPAD_DPAD_LEFT;
    else if (!left && right) direction = NSGAMEPAD_DPAD_RIGHT;
    else direction = NSGAMEPAD_DPAD_CENTERED;

    Gamepad.dPad(direction);
}