#include <Arduino.h>
#include "BluetoothSerial.h"
#include "config.h"

// Инициализация Bluetooth-интерфейса
BluetoothSerial SerialBT;

// Переменные состояния системы:
unsigned long timerStartMillis = 0;  // Время старта таймера
bool timerRunning = false;           // Флаг активен ли таймер
int lastBroadcastValue = DEFAULT_VALUE; // Последнее отправленное значение
bool lastButtonState = HIGH;         // Предыдущее состояние кнопки
int value = 1;                       // Текущее значение для отправки (начинается с 1)

// Функция отправки значения по Bluetooth и в Serial
void broadcastValue(int value) {
  if (value != lastBroadcastValue) { // Проверка изменения значения
    lastBroadcastValue = value;      // Обновление последнего значения
    String msg = String("Value: ") + String(value);
    Serial.println(msg);             // Вывод в монитор порта
    SerialBT.println(msg);           // Отправка по Bluetooth
  }
}

void setup() {
  // Настройка кнопки с внутренней подтяжкой к питанию
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Инициализация последовательного порта
  Serial.begin(115200);
  
  // Запуск Bluetooth с именем устройства
  SerialBT.begin("ESP32_Broadcaster");
  
  // Стартовые сообщения
  Serial.println("ESP32 Bluetooth broadcaster started.");
  SerialBT.println("Value: " + String(DEFAULT_VALUE));
}

void loop() {
  // Чтение текущего состояния кнопки
  bool buttonState = digitalRead(BUTTON_PIN);
  
  // Обработка нажатия (переход из HIGH в LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    timerStartMillis = millis();     // Старт таймера
    timerRunning = true;             // Активация флага таймера
    
    // Отправка текущего значения и инкремент
    broadcastValue(value);
    value += 1;                      // Увеличение значения на 1
  }
  lastButtonState = buttonState;     // Сохранение состояния кнопки

  // Проверка таймера
  if (timerRunning) {
    // Если таймер истек (10 секунд)
    if (millis() - timerStartMillis > TIMER_DURATION) {
      timerRunning = false;          // Сброс флага таймера
      value = 1;                     // Сброс значения на начальное
      broadcastValue(DEFAULT_VALUE); // Отправка значения по умолчанию
    }
  }
  
  delay(50); // Задержка для подавления дребезга кнопки
}