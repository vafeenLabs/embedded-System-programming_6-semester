#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//вспомогательные переменные
String correctCode = "";
String inputCode = "";
int attemptCount = 0;
bool codeReceived = false;

//отображение сообщения на экране
void showMessage(const String& msg, int y = 0, bool clear = true) {
  if (clear) {
    display.clearDisplay();
    display.setCursor(0, y);
    display.print(msg);
    display.display();
  } else {
    display.setCursor(0, y);
    display.print(msg);
    display.display();
  }
}

//отправка команды на замок
void sendCommand(String cmd) {
  Serial.println(cmd);
}

//подсказка - указание числа на верной позиции
void giveHint() {
  display.setCursor(0, 40);
  for (int i = 0; i < inputCode.length(); i++) {
    if (i < correctCode.length() && inputCode[i] == correctCode[i]) {
      display.print(inputCode[i]);
    } else {
      display.print('_');
    }
  }
  display.display();
}

//установка
void setup() {
  //инициализация приемопередатчика
  Serial.begin(9600);
  
  //инициализируем дисплей
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  //выводим, что ожидаем связи с замком
  showMessage("Waiting for lock...");
}

void loop() {
  if (Serial.available()) {
    //обрабатываем сигнал
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    if (msg.startsWith("CODE:")) { //если пришел код
      correctCode = msg.substring(5);
      inputCode = "";
      attemptCount = 0;
      codeReceived = true;
      showMessage("PIN:");
    }
    else if (msg == "AWAKE") { //если замок передал свою готовность к работе
      showMessage("Connected!");
      delay(1500);
      if (codeReceived) {
        showMessage("PIN: ");
      }
      else {
        showMessage("Waiting...");
      }
    }
  }

  //читаем нажатую клавишу
  char key = keypad.getKey();
  if (key && codeReceived) {  // Обрабатываем ввод только после получения кода
    if (key == '#') { //подтвердили ввод - проверка кода
      attemptCount++;
      
      // Проверяем длину и содержимое кода
      if (inputCode.length() == correctCode.length() && inputCode == correctCode) {
        showMessage("Unlocked!");
        sendCommand("unlock");
        delay(2000);
        showMessage("PIN:");
      } 
      else if (attemptCount >= maxAttempts) { //превысили число попыток - блокировка
        showMessage("Lock blocked!");
        sendCommand("sleep");
        codeReceived = false;
      } 
      else { //неверный код и есть еще попытки
        showMessage("Oops! Try " + String(attemptCount) + "/" + String(maxAttempts));
        giveHint();
        delay(2000);
        showMessage("PIN:");
      }
      inputCode = "";
    } 
    else if (key == '*') { //очищаем введенный код
      inputCode = "";
      showMessage("PIN:");
    } 
    else if (isdigit(key)) { //добавляем цифры к вводимому коду
      if (inputCode.length() < correctCode.length()) {
        inputCode += key;
        display.clearDisplay();
        showMessage("PIN:", 0, false);
        showMessage(inputCode, 20, false);
      }
    }
  }
}