#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

int curSpeed = 10;

uint8_t dir = 0;
uint8_t motor_on = 0;

void USART_init(unsigned int ubrr) {
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_transmit(uint16_t data) {
    while (!(UCSRA & (1 << UDRE)));

    UDR = data;
}

unsigned char USART_receive(void) {
    while (!(UCSRA & (1 << RXC)));

    return UDR;
}

void check_input_data(unsigned char input) {
    if (input == '1') {
        motor_on = 1;
        USART_transmit(curSpeed);
        if (dir) {
            PORT_LED_REVERSE |= (1 << LED_REVERSE);
        }
        else {
            PORT_LED_REVERSE &= ~(1 << LED_REVERSE);
        }
        PORT_LED_ON |= (1 << LED_ON);
    } else if (input == '2') {
        motor_on = 0;
        PORT_LED_ON &= ~(1 << LED_ON);
        if (dir) {
            PORT_LED_REVERSE |= (1 << LED_REVERSE);
        }
        else {
            PORT_LED_REVERSE &= ~(1 << LED_REVERSE);
        }
    } else if (input == '0') {
        dir ^= 1;
        if (dir) {
            PORT_LED_REVERSE |= (1 << LED_REVERSE);
        }
        else {
            PORT_LED_REVERSE &= ~(1 << LED_REVERSE);
        }
    }
    else if (input == '+') {
        curSpeed++;
        USART_transmit(curSpeed);
    } 
    else if (input == '-') {
        if (curSpeed-1 >= 0) {
            curSpeed--;
        }
        USART_transmit(curSpeed);
    }
    else {
        USART_transmit(curSpeed);
    }
}

void setup() {
    DDR_LED_ON |= (1 << LED_ON);
    DDR_LED_REVERSE |= (1 << LED_REVERSE);

    DDR_A_PLUS |= (1 << A_PLUS);
    DDR_B_PLUS |= (1 << B_PLUS);
    DDR_A_MINUS |= (1 << A_MINUS);
    DDR_B_MINUS |= (1 << B_MINUS);

    PORT_LED_ON &= ~(1 << LED_ON);
    PORT_LED_REVERSE &= ~(1 << LED_REVERSE);
    PORT_A_PLUS &= ~(1 << A_PLUS);
    PORT_B_PLUS &= ~(1 << B_PLUS);
    PORT_A_MINUS &= ~(1 << A_MINUS);
    PORT_B_MINUS &= ~(1 << B_MINUS);
}

void make_step(uint8_t index) {
    PORT_A_PLUS &= ~(1 << A_PLUS);
    PORT_B_PLUS &= ~(1 << B_PLUS);
    PORT_A_MINUS &= ~(1 << A_MINUS);
    PORT_B_MINUS &= ~(1 << B_MINUS);

    switch (index % 4) {
        case 0: PORT_A_PLUS |= (1 << A_PLUS); break;
        case 1: PORT_B_PLUS |= (1 << B_PLUS); break;
        case 2: PORT_A_MINUS |= (1 << A_MINUS); break;
        case 3: PORT_B_MINUS |= (1 << B_MINUS); break;
    }
}

void delay_variable_ms(uint16_t ms) {
    while(ms--){
        _delay_ms(50);
    }
}

int main(void) {
    setup();
    USART_init(103);

    uint8_t step = 0;

    while (1) {
        if (UCSRA & (1 << RXC)) {
            unsigned char input = USART_receive();
            check_input_data(input);
        }

        if (motor_on && curSpeed > 0) {
            make_step(step);
            step = dir ? (step + 3) % 4 : (step + 1) % 4;
            delay_variable_ms(200 - curSpeed*15);
        }
    }
}
