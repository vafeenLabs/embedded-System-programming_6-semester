#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_A_PIN PA0
#define BUTTON_B_PIN PA1

#define LED_A_PIN PB0
#define LED_B_PIN PB1
#define LED_XOR_PIN PB2

volatile uint8_t varA = 0;
volatile uint8_t varB = 0;
volatile uint8_t xor = 0;
void update_leds();

// Interrupt handler
ISR(PCINT0_vect) {
    _delay_ms(50);
    if (!(PINA & (1 << BUTTON_A_PIN))) varA ^= 1;
    if (!(PINA & (1 << BUTTON_B_PIN))) varB ^= 1;
    xor = varA ^ varB;
    update_leds();
}

void setup_ports() {
    // Input/output settings
    DDRA &= ~((1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN)); //inputs
    PORTA |= (1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN); // pullup
    
    DDRB |= (1 << LED_A_PIN) | (1 << LED_B_PIN) | (1 << LED_XOR_PIN); //output
}

void setup_interrupts() {
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1); // allow interrupts for PA0 and PA1
    GIMSK |= (1 << PCIE0); // enable PORTA interrupts
    sei(); // allow interruprs globally
}

void update_leds(){
  PORTB = (varA << LED_A_PIN) | 
                (varB << LED_B_PIN) | 
                (xor << LED_XOR_PIN);
}

int main(void) {
    setup_ports();
    setup_interrupts();
    update_leds();
    while(1) {
    }
}