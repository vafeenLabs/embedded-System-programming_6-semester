#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const uint8_t digit_patterns[10] = {
    0b01111111, // 0
    0b00001101, // 1
    0b10110111, // 2
    0b10011111, // 3
    0b11001101, // 4
    0b11011011, // 5
    0b11111011, // 6
    0b00001111, // 7
    0b11111111, // 8
    0b11011111  // 9
};

void USART_init(unsigned int ubrr) {
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

uint16_t USART_receive(void) {
    while (!(UCSRA & (1 << RXC)));

    return UDR;
}

void setup_leds(){
    DDR_DISPLAYF_A |= (1 << DISPLAYF_A); 
    DDR_DISPLAYF_B |= (1 << DISPLAYF_B);  
    DDR_DISPLAYF_C |= (1 << DISPLAYF_C); 
    DDR_DISPLAYF_D |= (1 << DISPLAYF_D); 
    DDR_DISPLAYF_E |= (1 << DISPLAYF_E); 
    DDRD |= (1 << PD6); 
    DDRD |= (1 << PD7); 
    
    DDR_DIGIT_A |= (1 << DIGIT_A);
    DDR_DIGIT_B |= (1 << DIGIT_B);
    DDR_DIGIT_C |= (1 << DIGIT_C);
    DDR_DIGIT_D |= (1 << DIGIT_D);

    DDRB &= ~(1 << PB4);

    PORT_DIGIT_A |= (1 << DIGIT_A);
    PORT_DIGIT_B |= (1 << DIGIT_B);
    PORT_DIGIT_C |= (1 << DIGIT_C);
    PORT_DIGIT_D |= (1 << DIGIT_D);
}

void display_numbers(uint16_t number) {
    uint16_t digits[4];
    digits[0] = number / 1000;        
    digits[1] = (number / 100) % 10;  
    digits[2] = (number / 10) % 10;   
    digits[3] = number % 10;

    PORT_DIGIT_A |= (1 << DIGIT_A);
    PORT_DIGIT_B |= (1 << DIGIT_B);
    PORT_DIGIT_C |= (1 << DIGIT_C);
    PORT_DIGIT_D |= (1 << DIGIT_D);

    PORT_DIGIT_D &= ~(1 << DIGIT_D);
    PORTD = digit_patterns[digits[3]];
    _delay_ms(1);                   
    PORT_DIGIT_D |= (1 << DIGIT_D);

    PORT_DIGIT_C &= ~(1 << DIGIT_C);              
    PORTD = digit_patterns[digits[2]];
    _delay_ms(1);                      
    PORT_DIGIT_C |= (1 << DIGIT_C);

    PORT_DIGIT_B &= ~(1 << DIGIT_B);                 
    PORTD = digit_patterns[digits[1]];
    _delay_ms(1);                     
    PORT_DIGIT_B |= (1 << DIGIT_B);

    PORT_DIGIT_A &= ~(1 << DIGIT_A);                
    PORTD = digit_patterns[digits[0]];
    _delay_ms(1);
    PORT_DIGIT_A |= (1 << DIGIT_A);
}

int main()
{
    setup_leds(); 
    USART_init(103);
    uint16_t counter=0;
    while (1) {
        display_numbers(counter);

        if (UCSRA & (1 << RXC)) {
            counter = USART_receive();
        }
    }
}
