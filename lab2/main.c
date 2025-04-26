#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

volatile uint8_t var_a = 0;
volatile uint8_t var_b = 0;
volatile uint8_t xor = 0;

#ifndef BUTTON_A_PORT
#error "BUTTON_A_PORT must be defined"
#endif
#ifndef BUTTON_B_PORT
#error "BUTTON_B_PORT must be defined"
#endif
#ifndef LED_A_PORT
#error "LED_A_PORT must be defined"
#endif
#ifndef LED_B_PORT
#error "LED_B_PORT must be defined"
#endif
#ifndef LED_XOR_PORT
#error "LED_XOR_PORT must be defined"
#endif

#ifndef BUTTON_A_PIN
#error "BUTTON_A_PIN must be defined"
#endif
#ifndef BUTTON_B_PIN
#error "BUTTON_B_PIN must be defined"
#endif
#ifndef LED_A_PIN
#error "LED_A_PIN must be defined"
#endif
#ifndef LED_B_PIN
#error "LED_B_PIN must be defined"
#endif
#ifndef LED_XOR_PIN
#error "LED_XOR_PIN must be defined"
#endif

#define CONCAT(first, second) first##second
#define DDR(port) CONCAT(DDR, port)
#define PORT(port) CONCAT(PORT, port)
#define PIN(port) CONCAT(PIN, port)
#define TO_STRING(x) #x
#define STRING_TO_CHAR(str) ((str)[0])

void setup_ports() {
    DDR(BUTTON_A_PORT) &= ~(1 << BUTTON_A_PIN);
    DDR(BUTTON_B_PORT) &= ~(1 << BUTTON_B_PIN);

    PORT(BUTTON_A_PORT) |= 1 << BUTTON_A_PIN;
    PORT(BUTTON_B_PORT) |= 1 << BUTTON_B_PIN;

    DDR(LED_A_PORT) |= 1 << LED_A_PIN;
    DDR(LED_B_PORT) |= 1 << LED_B_PIN;
    DDR(LED_XOR_PORT) |= 1 << LED_XOR_PIN;
}

void update_leds() {
    if (var_a) {
        PORT(LED_A_PORT) |= 1 << LED_A_PIN;
    } else {
        PORT(LED_A_PORT) &= ~(1 << LED_A_PIN);
    }
    if (var_b) {
        PORT(LED_B_PORT) |= 1 << LED_B_PIN;
    } else {
        PORT(LED_B_PORT) &= ~(1 << LED_B_PIN);
    }
    if (xor) {
        PORT(LED_XOR_PORT) |= 1 << LED_XOR_PIN;
    } else {
        PORT(LED_XOR_PORT) &= ~(1 << LED_XOR_PIN);
    }
}

#if defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny25__) || \
    defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
ISR(PCINT0_vect) {
    _delay_ms(50);
    if (!(PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN))) {
        while((PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN)) == 0) {}
        var_a = !var_a;
    }
    if (!(PIN(BUTTON_B_PORT) & (1 << BUTTON_B_PIN))) {
        var_b = !var_b;
    }
    xor = var_a ^ var_b;
    update_leds();
}

void setup_interrupts() {
    PCMSK |= (1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN);
    GIMSK |= (1 << PCIE);
    sei();
}

#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || \
      defined(__AVR_ATtiny84__)
ISR(PCINT1_vect, ISR_ALIASOF(PCINT0_vect));
ISR(PCINT0_vect) {
    _delay_ms(50);
    if (!(PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN))) {
        while((PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN)) == 0) {}
        var_a ^= 1;
    }
    if (!(PIN(BUTTON_B_PORT) & (1 << BUTTON_B_PIN))) {
        while((PIN(BUTTON_B_PORT) & (1 << BUTTON_B_PIN)) == 0) {}
        var_b ^= 1;
    }
    xor = var_a ^ var_b;
    update_leds();
}

void setup_interrupts() {
    BUTTON_A_PCMSK |= (1 << BUTTON_A_PIN);
    BUTTON_B_PCMSK |= (1 << BUTTON_B_PIN);
    GIMSK |= (1 << BUTTON_A_PCIE) | (1 << BUTTON_B_PCIE);
    sei();
}

#elif defined(__AVR_ATtiny2313__)
ISR(INT1_vect, ISR_ALIASOF(INT0_vect));
ISR(PCINT_vect, ISR_ALIASOF(INT0_vect));
ISR(INT0_vect) {
    _delay_ms(50);
    if (!(PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN))) {
        while((PIN(BUTTON_A_PORT) & (1 << BUTTON_A_PIN)) == 0) {}
        var_a = !var_a;
    }
    if (!(PIN(BUTTON_B_PORT) & (1 << BUTTON_B_PIN))) {
        while((PIN(BUTTON_B_PORT) & (1 << BUTTON_B_PIN)) == 0) {}
        var_b = !var_b;
    }
    xor = var_a ^ var_b;
    update_leds();
}

void setup_interrupts() {
    PCMSK |= (1 << BUTTON_A_PIN) | (1 << BUTTON_B_PIN);
    GIMSK |= (1 << BUTTON_A_PCIE) | (1 << BUTTON_B_PCIE);
    sei();
}

#endif

int main(void) {
    setup_ports();
    setup_interrupts();
    update_leds();
    while (1) {}
}