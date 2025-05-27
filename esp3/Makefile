include config.h

OBJCOPY=avr-objcopy
CC=avr-gcc

ifeq ($(findstring B, ${LED_ON}), B)
	PORT_LED_ON=PORTB
	DDR_LED_ON=DDRB
endif
ifeq ($(findstring C, ${LED_ON}), C)
	PORT_LED_ON=PORTC
	DDR_LED_ON=DDRC
endif
ifeq ($(findstring D, ${LED_ON}), D)
	PORT_LED_ON=PORTD
	DDR_LED_ON=DDRD
endif

ifeq ($(findstring B, ${LED_REVERSE}), B)
	PORT_LED_REVERSE=PORTB
	DDR_LED_REVERSE=DDRB
endif
ifeq ($(findstring C, ${LED_REVERSE}), C)
	PORT_LED_REVERSE=PORTC
	DDR_LED_REVERSE=DDRC
endif
ifeq ($(findstring D, ${LED_REVERSE}), D)
	PORT_LED_REVERSE=PORTD
	DDR_LED_REVERSE=DDRD
endif

ifeq ($(findstring B, ${A_PLUS}), B)
	PORT_A_PLUS=PORTB
	DDR_A_PLUS=DDRB
endif
ifeq ($(findstring C, ${A_PLUS}), C)
	PORT_A_PLUS=PORTC
	DDR_A_PLUS=DDRC
endif
ifeq ($(findstring D, ${A_PLUS}), D)
	PORT_A_PLUS=PORTD
	DDR_A_PLUS=DDRD
endif

ifeq ($(findstring B, ${B_PLUS}), B)
	PORT_B_PLUS=PORTB
	DDR_B_PLUS=DDRB
endif
ifeq ($(findstring C, ${B_PLUS}), C)
	PORT_B_PLUS=PORTC
	DDR_B_PLUS=DDRC
endif
ifeq ($(findstring D, ${B_PLUS}), D)
	PORT_B_PLUS=PORTD
	DDR_B_PLUS=DDRD
endif

ifeq ($(findstring B, ${A_MINUS}), B)
	PORT_A_MINUS=PORTB
	DDR_A_MINUS=DDRB
endif
ifeq ($(findstring C, ${A_MINUS}), C)
	PORT_A_MINUS=PORTC
	DDR_A_MINUS=DDRC
endif
ifeq ($(findstring D, ${A_MINUS}), D)
	PORT_A_MINUS=PORTD
	DDR_A_MINUS=DDRD
endif

ifeq ($(findstring B, ${B_MINUS}), B)
	PORT_B_MINUS=PORTB
	DDR_B_MINUS=DDRB
endif
ifeq ($(findstring C, ${B_MINUS}), C)
	PORT_B_MINUS=PORTC
	DDR_B_MINUS=DDRC
endif
ifeq ($(findstring D, ${B_MINUS}), D)
	PORT_B_MINUS=PORTD
	DDR_B_MINUS=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_A}), B)
	PORT_DISPLAYF_A=PORTB
	DDR_DISPLAYF_A=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_A}), C)
	PORT_DISPLAYF_A=PORTC
	DDR_DISPLAYF_A=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_A}), D)
	PORT_DISPLAYF_A=PORTD
	DDR_DISPLAYF_A=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_B}), B)
	PORT_DISPLAYF_B=PORTB
	DDR_DISPLAYF_B=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_B}), C)
	PORT_DISPLAYF_B=PORTC
	DDR_DISPLAYF_B=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_B}), D)
	PORT_DISPLAYF_B=PORTD
	DDR_DISPLAYF_B=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_C}), B)
	PORT_DISPLAYF_C=PORTB
	DDR_DISPLAYF_C=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_C}), C)
	PORT_DISPLAYF_C=PORTC
	DDR_DISPLAYF_C=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_C}), D)
	PORT_DISPLAYF_C=PORTD
	DDR_DISPLAYF_C=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_D}), B)
	PORT_DISPLAYF_D=PORTB
	DDR_DISPLAYF_D=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_D}), C)
	PORT_DISPLAYF_D=PORTC
	DDR_DISPLAYF_D=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_D}), D)
	PORT_DISPLAYF_D=PORTD
	DDR_DISPLAYF_D=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_E}), B)
	PORT_DISPLAYF_E=PORTB
	DDR_DISPLAYF_E=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_E}), C)
	PORT_DISPLAYF_E=PORTC
	DDR_DISPLAYF_E=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_E}), D)
	PORT_DISPLAYF_E=PORTD
	DDR_DISPLAYF_E=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_F}), B)
	PORT_DISPLAYF_F=PORTB
	DDR_DISPLAYF_F=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_F}), C)
	PORT_DISPLAYF_F=PORTC
	DDR_DISPLAYF_F=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_F}), D)
	PORT_DISPLAYF_F=PORTD
	DDR_DISPLAYF_F=DDRD
endif

ifeq ($(findstring B, ${DISPLAYF_G}), B)
	PORT_DISPLAYF_G=PORTB
	DDR_DISPLAYF_G=DDRB
endif
ifeq ($(findstring C, ${DISPLAYF_G}), C)
	PORT_DISPLAYF_G=PORTC
	DDR_DISPLAYF_G=DDRC
endif
ifeq ($(findstring D, ${DISPLAYF_G}), D)
	PORT_DISPLAYF_G=PORTD
	DDR_DISPLAYF_G=DDRD
endif

ifeq ($(findstring B, ${DIGIT_A}), B)
	PORT_DIGIT_A=PORTB
	DDR_DIGIT_A=DDRB
endif
ifeq ($(findstring C, ${DIGIT_A}), C)
	PORT_DIGIT_A=PORTC
	DDR_DIGIT_A=DDRC
endif
ifeq ($(findstring D, ${DIGIT_A}), D)
	PORT_DIGIT_A=PORTD
	DDR_DIGIT_A=DDRD
endif
ifeq ($(findstring B, ${DIGIT_B}), B)
	PORT_DIGIT_B=PORTB
	DDR_DIGIT_B=DDRB
endif
ifeq ($(findstring C, ${DIGIT_B}), C)
	PORT_DIGIT_B=PORTC
	DDR_DIGIT_B=DDRC
endif
ifeq ($(findstring D, ${DIGIT_B}), D)
	PORT_DIGIT_B=PORTD
	DDR_DIGIT_B=DDRD
endif
ifeq ($(findstring B, ${DIGIT_C}), B)
	PORT_DIGIT_C=PORTB
	DDR_DIGIT_C=DDRB
endif
ifeq ($(findstring C, ${DIGIT_C}), C)
	PORT_DIGIT_C=PORTC
	DDR_DIGIT_C=DDRC
endif
ifeq ($(findstring D, ${DIGIT_C}), D)
	PORT_DIGIT_C=PORTD
	DDR_DIGIT_C=DDRD
endif
ifeq ($(findstring B, ${DIGIT_D}), B)
	PORT_DIGIT_D=PORTB
	DDR_DIGIT_D=DDRB
endif
ifeq ($(findstring C, ${DIGIT_D}), C)
	PORT_DIGIT_D=PORTC
	DDR_DIGIT_D=DDRC
endif
ifeq ($(findstring D, ${DIGIT_D}), D)
	PORT_DIGIT_D=PORTD
	DDR_DIGIT_D=DDRD
endif

CFLAGS_main= -std=c99 -Wall -g -Os -mmcu=${FIRST_MCU}\
		-DLED_REVERSE=P${LED_REVERSE} -DPORT_LED_REVERSE=${PORT_LED_REVERSE} -DDDR_LED_REVERSE=${DDR_LED_REVERSE}\
		-DLED_ON=P${LED_ON} -DPORT_LED_ON=${PORT_LED_ON} -DDDR_LED_ON=${DDR_LED_ON}\
		-DA_PLUS=P${A_PLUS} -DPORT_A_PLUS=${PORT_A_PLUS} -DDDR_A_PLUS=${DDR_A_PLUS}\
		-DB_PLUS=P${B_PLUS} -DPORT_B_PLUS=${PORT_B_PLUS} -DDDR_B_PLUS=${DDR_B_PLUS}\
		-DA_MINUS=P${A_MINUS} -DPORT_A_MINUS=${PORT_A_MINUS} -DDDR_A_MINUS=${DDR_A_MINUS}\
		-DB_MINUS=P${B_MINUS} -DPORT_B_MINUS=${PORT_B_MINUS} -DDDR_B_MINUS=${DDR_B_MINUS}\
		
TARGET_main=main1
SRC_main=main1.c

CFLAGS_second= -std=c99 -Wall -g -Os -mmcu=${SECOND_MCU}\
		-DDISPLAYF_A=P${DISPLAYF_A} -DPORT_DISPLAYF_A=${PORT_DISPLAYF_A} -DDDR_DISPLAYF_A=${DDR_DISPLAYF_A}\
		-DDISPLAYF_B=P${DISPLAYF_B} -DPORT_DISPLAYF_B=${PORT_DISPLAYF_B} -DDDR_DISPLAYF_B=${DDR_DISPLAYF_B}\
		-DDISPLAYF_C=P${DISPLAYF_C} -DPORT_DISPLAYF_C=${PORT_DISPLAYF_C} -DDDR_DISPLAYF_C=${DDR_DISPLAYF_C}\
		-DDISPLAYF_D=P${DISPLAYF_D} -DPORT_DISPLAYF_D=${PORT_DISPLAYF_D} -DDDR_DISPLAYF_D=${DDR_DISPLAYF_D}\
		-DDISPLAYF_E=P${DISPLAYF_E} -DPORT_DISPLAYF_E=${PORT_DISPLAYF_E} -DDDR_DISPLAYF_E=${DDR_DISPLAYF_E}\
		-DDISPLAYF_F=P${DISPLAYF_F} -DPORT_DISPLAYF_F=${PORT_DISPLAYF_F} -DDDR_DISPLAYF_F=${DDR_DISPLAYF_F}\
		-DDISPLAYF_G=P${DISPLAYF_G} -DPORT_DISPLAYF_G=${PORT_DISPLAYF_G} -DDDR_DISPLAYF_G=${DDR_DISPLAYF_G}\
		-DDIGIT_A=P${DIGIT_A} -DPORT_DIGIT_A=${PORT_DIGIT_A} -DDDR_DIGIT_A=${DDR_DIGIT_A}\
		-DDIGIT_B=P${DIGIT_B} -DPORT_DIGIT_B=${PORT_DIGIT_B} -DDDR_DIGIT_B=${DDR_DIGIT_B}\
		-DDIGIT_C=P${DIGIT_C} -DPORT_DIGIT_C=${PORT_DIGIT_C} -DDDR_DIGIT_C=${DDR_DIGIT_C}\
		-DDIGIT_D=P${DIGIT_D} -DPORT_DIGIT_D=${PORT_DIGIT_D} -DDDR_DIGIT_D=${DDR_DIGIT_D}\

TARGET_second=main2
SRC_second=main2.c

all:
	${CC} ${CFLAGS_main} -o ${TARGET_main}.bin ${SRC_main}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET_main}.bin ${TARGET_main}.hex

	${CC} ${CFLAGS_second} -o ${TARGET_second}.bin ${SRC_second}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET_second}.bin ${TARGET_second}.hex
clean:
	rm -f *.bin *.hex