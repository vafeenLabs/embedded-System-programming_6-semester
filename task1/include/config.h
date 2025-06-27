#ifndef CONFIG_H
#define CONFIG_H

// Пин GPIO, к которому подключена кнопка (для ESP32)
const int BUTTON_PIN = 5;

// Базовое значение, которое передается при старте и после таймаута
const int DEFAULT_VALUE = 100;

// Время в миллисекундах, после которого система сбрасывается (10 секунд)
const unsigned long TIMER_DURATION = 10000;

#endif