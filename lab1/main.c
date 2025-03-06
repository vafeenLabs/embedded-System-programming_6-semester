#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Определение констант для номеров пинов кнопок и светодиодов
#define BUTTON_A_PIN PA0  // Пин для кнопки A
#define BUTTON_B_PIN PA1  // Пин для кнопки B

#define LED_A_PIN PB0     // Пин для светодиода A
#define LED_B_PIN PB1     // Пин для светодиода B
#define LED_XOR_PIN PB2   // Пин для светодиода результата XOR

// Переменные для хранения состояния кнопок и результата операции XOR
volatile uint8_t varA = 0;  // Состояние кнопки A
volatile uint8_t varB = 0;  // Состояние кнопки B
volatile uint8_t xor = 0;   // Результат операции XOR

// Обработчик прерывания для кнопок на порте A
ISR(PCINT0_vect) {
    // Задержка на 50 мс для предотвращения дребезга контактов
    _delay_ms(50);
    
    // Проверка состояния кнопки A и инвертирование переменной varA, если кнопка нажата
    if (!(PINA & (1 << BUTTON_A_PIN))) varA ^= 1;
    
    // Проверка состояния кнопки B и инвертирование переменной varB, если кнопка нажата
    if (!(PINA & (1 << BUTTON_B_PIN))) varB ^= 1;
    
    // Вычисление результата операции XOR между varA и varB
    xor = varA ^ varB;
    
    // Обновление светодиодов
    update_leds();
}

// Функция настройки портов
void setup_ports() {
    // Настройка режимов портов
    // Установка пинов BUTTON_A_PIN и BUTTON_B_PIN на порт A как входы с подтяжкой к Vcc (pull-up)
    DDRA &= ~((1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN));
    PORTA |= (1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN);
    
    // Установка пинов LED_A_PIN, LED_B_PIN и LED_XOR_PIN на порт B как выходы
    DDRB |= (1 << LED_A_PIN) | (1 << LED_B_PIN) | (1 << LED_XOR_PIN);
}

// Функция настройки прерываний
void setup_interrupts() {
    // Включение прерываний для пинов PA0 и PA1
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1);
    
    // Включение прерываний для порта A
    GIMSK |= (1 << PCIE0);
    
    // Глобальное разрешение прерываний
    sei();
}

// Функция обновления светодиодов
void update_leds(){
    // Обновление состояния светодиодов на основе текущих значений varA, varB и xor
    PORTB = (varA << LED_A_PIN) | 
                (varB << LED_B_PIN) | 
                (xor << LED_XOR_PIN);
}

// Основная функция программы
int main(void) {
    // Вызов функций настройки портов и прерываний
    setup_ports();
    setup_interrupts();
    
    // Обновление светодиодов
    update_leds();
    
    // Бесконечный цикл ожидания прерываний
    while(1) {
    }
}
