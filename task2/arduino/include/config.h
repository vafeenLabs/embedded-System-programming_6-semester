#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;

const int ROWS = 4;
const int COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
const byte colPins[COLS] = {6,7,8,9};
const byte rowPins[ROWS] = {5,4,3,2};

const int maxAttempts = 3;

#endif