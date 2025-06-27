#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// Инициализация OLED-дисплея
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Инициализация клавиатуры
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Переменные состояния системы
String correctCode = "";      // Правильный код от замка
String inputCode = "";        // Вводимый пользователем код
int attemptCount = 0;         // Счетчик попыток ввода
bool codeReceived = false;    // Флаг получения кода от замка

// Функция вывода сообщения на дисплей
void showMessage(const String& msg, int y = 0, bool clear = true) {
  if (clear) {
    display.clearDisplay();   // Очистка дисплея при необходимости
    display.setCursor(0, y);  // Установка курсора
    display.print(msg);       // Вывод текста
    display.display();        // Обновление дисплея
  } else {
    display.setCursor(0, y);
    display.print(msg);
    display.display();
  }
}

// Отправка команды на замок через Serial
void sendCommand(String cmd) {
  Serial.println(cmd);  // Протоколирование команды
}

// Подсказка - показывает правильно введенные цифры
void giveHint() {
  display.setCursor(0, 40);  // Позиция для подсказки
  for (int i = 0; i < inputCode.length(); i++) {
    // Сравниваем каждый символ с правильным кодом
    if (i < correctCode.length() && inputCode[i] == correctCode[i]) {
      display.print(inputCode[i]);  // Показываем правильную цифру
    } else {
      display.print('_');  // Маскируем неправильные
    }
  }
  display.display();
}

void setup() {
  Serial.begin(9600);  // Инициализация последовательного порта
  
  // Инициализация дисплея
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    while (true);  // Бесконечный цикл при ошибке инициализации
  }
  
  // Настройки отображения текста
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  showMessage("Waiting for lock...");  // Стартовое сообщение
}

void loop() {
  // Обработка входящих сообщений от замка
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    if (msg.startsWith("CODE:")) {  // Получен новый код
      correctCode = msg.substring(5);  // Извлекаем код из сообщения
      inputCode = "";                 // Сброс введенного кода
      attemptCount = 0;               // Сброс счетчика попыток
      codeReceived = true;            // Флаг получения кода
      showMessage("PIN:");            // Приглашение для ввода
    }
    else if (msg == "AWAKE") {       // Замок готов к работе
      showMessage("Connected!");
      delay(1500);
      if (codeReceived) {
        showMessage("PIN: ");        // Продолжаем запрос кода
      } else {
        showMessage("Waiting...");   // Ожидаем код
      }
    }
  }

  // Обработка нажатий клавиш
  char key = keypad.getKey();
  if (key && codeReceived) {  // Обработка только после получения кода
    
    if (key == '#') {  // Подтверждение ввода
      attemptCount++;
      
      // Проверка кода
      if (inputCode.length() == correctCode.length() && inputCode == correctCode) {
        showMessage("Unlocked!");    // Успешное открытие
        sendCommand("unlock");       // Команда разблокировки
        delay(2000);
        showMessage("PIN:");         // Возврат к вводу
      } 
      else if (attemptCount >= maxAttempts) {  // Превышены попытки
        showMessage("Lock blocked!"); // Блокировка системы
        sendCommand("sleep");        // Команда блокировки
        codeReceived = false;        // Сброс флага
      } 
      else {  // Неверный код, но есть попытки
        showMessage("Oops! Try " + String(attemptCount) + "/" + String(maxAttempts));
        giveHint();                 // Показ подсказки
        delay(2000);
        showMessage("PIN:");        // Повторный запрос
      }
      inputCode = "";               // Сброс ввода
    } 
    else if (key == '*') {  // Сброс ввода
      inputCode = "";
      showMessage("PIN:");
    } 
    else if (isdigit(key)) {  // Ввод цифр
      if (inputCode.length() < correctCode.length()) {
        inputCode += key;      // Добавление цифры
        display.clearDisplay();
        showMessage("PIN:", 0, false);
        showMessage(inputCode, 20, false);  // Показ вводимого кода
      }
    }
  }
}