#include <Arduino.h>
#include "config.h"
#include <EEPROM.h>

// Размер выделяемой EEPROM (10 байт)
#define EEPROM_SIZE 10

// Глобальные переменные состояния
String correctCode = "";    // Хранит правильный код
bool unlocked = false;      // Флаг состояния замка

// Функция записи строки в EEPROM
void writeToEEPROM(int addrOffset, String& code) {
  int len = code.length();
  EEPROM.write(addrOffset, len);  // Записываем длину строки
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, code[i]);  // Посимвольно записываем код
  }
  EEPROM.commit();  // Сохраняем изменения
}

// Функция чтения строки из EEPROM
String readFromEEPROM(int addrOffset) {
  int len = EEPROM.read(addrOffset);  // Читаем длину строки
  char data[len + 1];                 // Буфер для данных
  for (int i = 0; i < len; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);  // Читаем посимвольно
  }
  data[len] = '\0';  // Добавляем терминатор строки
  return String(data);
}

// Функция перехода в режим глубокого сна
void goToSleep() {
  Serial.println("Going to sleep...");  // Уведомление Arduino
  digitalWrite(LED_PIN, LOW);          // Выключаем светодиод
  
  // Настраиваем пробуждение по таймеру
  esp_sleep_enable_timer_wakeup(MAX_SLEEP_TIME_SEC * 1000000ULL);
  delay(100);  // Короткая задержка для завершения операций
  esp_deep_sleep_start();  // Переход в глубокий сон
}

// Генерация случайного кода
String generateCode(int length = 4) {
  String code = "";
  for (int i = 0; i < length; i++) {
    code += String(esp_random() % 10);  // Цифра от 0 до 9
  }
  return code;
}

void setup() {
  // Настройка вывода для светодиода
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Инициализация последовательного порта и EEPROM
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  delay(1000);  // Стабилизация

  // Генерация/чтение кода в зависимости от причины пробуждения
  if(esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
    // Первый запуск - генерируем новый код
    correctCode = generateCode();
    writeToEEPROM(0, correctCode);
  } else {
    // Пробуждение после сна - читаем сохраненный код
    correctCode = readFromEEPROM(0);
  }

  // Отправка статуса Arduino
  Serial.println("AWAKE");          // Уведомление о готовности
  delay(100);
  Serial.println("CODE:" + correctCode); // Отправка кода
}

void loop() {
  // Обработка входящих команд от Arduino
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "unlock") {  // Команда разблокировки
      digitalWrite(LED_PIN, HIGH);  // Включаем светодиод
      Serial.println("UNLOCKED");   // Подтверждение
      unlocked = true;
    } else if (input == "sleep") {  // Команда сна
      goToSleep();
    }
  }
}