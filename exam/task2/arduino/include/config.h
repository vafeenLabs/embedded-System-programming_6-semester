#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// Параметры OLED-дисплея
const int SCREEN_WIDTH = 128;    // Ширина дисплея в пикселях
const int SCREEN_HEIGHT = 64;    // Высота дисплея в пикселях
const int OLED_RESET = -1;       // Пин сброса (-1 если не используется)

// Параметры матричной клавиатуры
const int ROWS = 4;              // Количество строк клавиатуры
const int COLS = 4;              // Количество столбцов клавиатуры

// Матрица символов на клавиатуре
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Пины для подключения столбцов клавиатуры
const byte colPins[COLS] = {6,7,8,9}; 
// Пины для подключения строк клавиатуры
const byte rowPins[ROWS] = {5,4,3,2}; 

// Максимальное количество попыток ввода кода
const int maxAttempts = 3;

#endif