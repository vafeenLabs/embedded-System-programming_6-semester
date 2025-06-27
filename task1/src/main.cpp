#include <Arduino.h>
#include "BluetoothSerial.h"
#include "config.h"

//инициализируем Bluetooth-передатчик
BluetoothSerial SerialBT;

// const int cycleLength = sizeof(cycleValues) / sizeof(cycleValues[0]); //длина цикла

unsigned long timerStartMillis = 0;
bool timerRunning = false;
int cycleIndex = -1; //для того, чтобы при первом нажатии передавался первый элемент цикла
int lastBroadcastValue = DEFAULT_VALUE;
bool lastButtonState = HIGH;
int value = 1; 
//функция передачи значения
void broadcastValue(int value) {
  //если значение изменилось
  if (value != lastBroadcastValue) {
    lastBroadcastValue = value;
    String msg = String("Value: ") + String(value);
    Serial.println(msg);
    SerialBT.println(msg);
  }
}

//конфигурирование системы
void setup() {
  //ставим кнопку на вход с подтяжкой
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //последовательный порт для отладки
  Serial.begin(115200);
  //запускаем Bluetooth-передатчик
  SerialBT.begin("ESP32_Broadcaster");
  Serial.println("ESP32 Bluetooth broadcaster started.");
  SerialBT.println("Value: " + String(DEFAULT_VALUE));
}

void loop() {
  
  //проверяем состояние кнопки
  bool buttonState = digitalRead(BUTTON_PIN);
  //кнопка нажата
  if (buttonState == LOW && lastButtonState == HIGH) {
    //инициализируем таймер
    timerStartMillis = millis();
    timerRunning = true;
    //сдвигаем элемент по циклу
    // cycleIndex = (cycleIndex + 1) % cycleLength;
    //передаем значение цикла
    // broadcastValue(cycleValues[cycleIndex]);
    broadcastValue(value);
    value+=1;
  }
  lastButtonState = buttonState;

  //таймер не истек
  if (timerRunning) {
    //таймер истекает
    if (millis() - timerStartMillis > TIMER_DURATION) {
      //остановка таймера
      timerRunning = false;
      //передаем дефолтное значение
      value =1; 
      broadcastValue(value);
    }
  }
  delay(50); //антидребезг
}