#include "hardware/gpio.h"
#define BUTTON_COUNT 14
#define AXIS_COUNT 2
void setup();
void loop();
void update_input();

uint8_t buttonPins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
uint8_t axisPins[] = { 14, 15 };