#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_A_PIN PA0
#define BUTTON_B_PIN PB3

#define LED_A_PIN PA3
#define LED_B_PIN PB1
#define LED_XOR_PIN PB2

volatile uint8_t varA = 0;
volatile uint8_t varB = 0;
volatile uint8_t xor = 0;

void update_leds(){
    if (varA) {
    PORTA |= (1 << LED_A_PIN);
    }
    else {
        PORTA &= ~(1 << LED_A_PIN);
    }
    if (varB) {
        PORTB |= (1 << LED_B_PIN);
    }
    else {
        PORTB &= ~(1 << LED_B_PIN);
    }
    if (xor) {
        PORTB |= (1 << LED_XOR_PIN);
    }
    else {
        PORTB &= ~(1 << LED_XOR_PIN);
    }
}

// Interrupt handler
ISR(PCINT1_vect) {
    _delay_ms(50);
    if (!(PINB & (1 << BUTTON_B_PIN))) varB = !varB;
    xor = varA ^ varB;
    update_leds();
}

ISR(PCINT0_vect){
    _delay_ms(50);
    if (!(PINA & (1 << BUTTON_A_PIN))) varA = !varA;
    xor = varA ^ varB;
    update_leds();
}

void setup_ports() {
    // Input/output settings
    DDRA &= ~(1 << BUTTON_A_PIN);
    DDRB &= ~(1 << BUTTON_B_PIN); //inputs

    PORTA |= (1 << BUTTON_A_PIN); // pullup
    PORTB |= (1 << BUTTON_B_PIN);

    DDRB |= (1 << LED_B_PIN) | (1 << LED_XOR_PIN);
    DDRA |= (1 << LED_A_PIN); //output
}

void setup_interrupts() {
    PCMSK0 |= (1 << PCINT0); // allow interrupts for PB3
    GIMSK |= (1 << PCIE0);
    PCMSK1 |= (1 << PCINT11); //allow interrupts for PA0
    GIMSK |= (1 << PCIE1);
    sei(); // allow interruprs globally
}

int main(void) {
    setup_ports();
    setup_interrupts();
    update_leds();
    while(1) {
    }
}