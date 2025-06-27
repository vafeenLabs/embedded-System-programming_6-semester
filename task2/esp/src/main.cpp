#include <Arduino.h>
#include "config.h"
#include <EEPROM.h>

#define EEPROM_SIZE 10

String correctCode = "";
bool unlocked = false;

//запись кода в EEPROM
void writeToEEPROM(int addrOffset, String& code) {
  int len = code.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, code[i]);
  }
  EEPROM.commit();
}

//чтение кода из EEPROM
String readFromEEPROM(int addrOffset) {
  int len = EEPROM.read(addrOffset);
  char data[len + 1];
  for (int i = 0; i < len; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[len] = '\0';
  return String(data);
}

//переход в сон
void goToSleep() {
  //команда Arduino об уходе в сон
  Serial.println("Going to sleep...");
  //отключаем светодиод
  digitalWrite(LED_PIN, LOW);
  //включаем таймер сна
  esp_sleep_enable_timer_wakeup(MAX_SLEEP_TIME_SEC * 1000000ULL);
  delay(100);
  //уходим в сон
  esp_deep_sleep_start();
}

//генерируем код (при запуске)
String generateCode(int length = 4) {
  String code = "";
  //случайно генерируем код почислово
  for (int i = 0; i < length; i++) {
    code += String(esp_random() % 10); //случайное число от 0 до 9
  }
  return code;
}

void setup() {
  //пин светодиода на выход
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  //запуск соединения с Arduino
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  delay(1000);

  //генерируем код при первом включении
  if(esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
    correctCode = generateCode();
    writeToEEPROM(0, correctCode);
  } else { //если после сна - читаем сгенерированный при первом запуске код
    correctCode = readFromEEPROM(0);
  }

  //уведомляем Arduino, что замок готов к работе
  Serial.println("AWAKE");
  delay(100);
  //отправляем код на Arduino
  Serial.println("CODE:" + correctCode);
}

void loop() {
  if (Serial.available()) {
    //читаем команду с Arduino
    String input = Serial.readStringUntil('\n');
    input.trim();

    //если код ввели верно
    if (input == "unlock") {
      //включаем светодиод
      digitalWrite(LED_PIN, HIGH);
      //сообщаем Arduino о том, что замок открыт
      Serial.println("UNLOCKED");
      unlocked = true;
    } else if (input == "sleep") {
      //уходим в сон, если команда "уйти в сон"
      goToSleep();
    }
  }
}
