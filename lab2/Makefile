include config.mk

CC=avr-gcc
OBJCOPY=avr-objcopy
TARGET=main
SRCS=main.c

BUTTON_A_PORT = $(shell echo $(BUTTON_A) | cut -c 1)
BUTTON_A_PIN = $(shell echo $(BUTTON_A) | cut -c 2)

BUTTON_B_PORT = $(shell echo $(BUTTON_B) | cut -c 1)
BUTTON_B_PIN = $(shell echo $(BUTTON_B) | cut -c 2)

LED_A_PORT = $(shell echo $(LED_A) | cut -c 1)
LED_A_PIN = $(shell echo $(LED_A) | cut -c 2)

LED_B_PORT = $(shell echo $(LED_B) | cut -c 1)
LED_B_PIN = $(shell echo $(LED_B) | cut -c 2)

LED_XOR_PORT = $(shell echo $(LED_XOR) | cut -c 1)
LED_XOR_PIN = $(shell echo $(LED_XOR) | cut -c 2)

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
CFLAGS += -DBUTTON_A_PORT=$(BUTTON_A_PORT) -DBUTTON_B_PORT=$(BUTTON_B_PORT)
CFLAGS += -DLED_A_PORT=$(LED_A_PORT)
CFLAGS += -DLED_B_PORT=$(LED_B_PORT) -DLED_XOR_PORT=$(LED_XOR_PORT)

CFLAGS += -DBUTTON_A_PIN=P$(BUTTON_A_PORT)$(BUTTON_A_PIN) -DBUTTON_B_PIN=P$(BUTTON_B_PORT)$(BUTTON_B_PIN)
CFLAGS += -DLED_A_PIN=P$(LED_A_PORT)$(LED_A_PIN)
CFLAGS += -DLED_B_PIN=P$(LED_B_PORT)$(LED_B_PIN) -DLED_XOR_PIN=P$(LED_XOR_PORT)$(LED_XOR_PIN)

ifeq ($(MCU), attiny24)
	ifeq ($(BUTTON_A_PORT), A)
		BUTTON_A_PCMSK = PCMSK0
		BUTTON_A_PCIE = PCIE0
	else
		BUTTON_A_PCMSK = PCMSK1
		BUTTON_A_PCIE = PCIE1
	endif
	ifeq ($(BUTTON_B_PORT), B)
		BUTTON_B_PCMSK = PCMSK1
		BUTTON_B_PCIE = PCIE1
	else
		BUTTON_B_PCMSK = PCMSK0
		BUTTON_B_PCIE = PCIE0
	endif
else ifeq ($(MCU), attiny44)
	ifeq ($(BUTTON_A_PORT), A)
		BUTTON_A_PCMSK = PCMSK0
		BUTTON_A_PCIE = PCIE0
	else
		BUTTON_A_PCMSK = PCMSK1
		BUTTON_A_PCIE = PCIE1
	endif
	ifeq ($(BUTTON_B_PORT), B)
		BUTTON_B_PCMSK = PCMSK1
		BUTTON_B_PCIE = PCIE1
	else
		BUTTON_B_PCMSK = PCMSK0
		BUTTON_B_PCIE = PCIE0
	endif
else ifeq ($(MCU), attiny84)
	ifeq ($(BUTTON_A_PORT), A)
		BUTTON_A_PCMSK = PCMSK0
		BUTTON_A_PCIE = PCIE0
	else
		BUTTON_A_PCMSK = PCMSK1
		BUTTON_A_PCIE = PCIE1
	endif
	ifeq ($(BUTTON_B_PORT), B)
		BUTTON_B_PCMSK = PCMSK1
		BUTTON_B_PCIE = PCIE1
	else
		BUTTON_B_PCMSK = PCMSK0
		BUTTON_B_PCIE = PCIE0
	endif
else ifeq ($(MCU), attiny2313)
	ifeq ($(BUTTON_A_PORT), B)
		BUTTON_A_PCMSK = PCMSK
		BUTTON_A_PCIE = PCIE
	else ifeq ($(BUTTON_A_PORT), A)
		BUTTON_A_PCMSK = PCMSK
		BUTTON_A_PCIE = INT0
	else
		BUTTON_A_PCMSK = PCMSK
		BUTTON_A_PCIE = INT1
	endif
	ifeq ($(BUTTON_B_PORT), B)
		BUTTON_B_PCMSK = PCMSK
		BUTTON_B_PCIE = PCIE
	else ifeq ($(BUTTON_A_PORT), A)
		BUTTON_B_PCMSK = PCMSK
		BUTTON_B_PCIE = INT0
	else
		BUTTON_B_PCMSK = PCMSK
		BUTTON_B_PCIE = INT1
	endif
endif
CFLAGS += -DBUTTON_A_PCMSK=$(BUTTON_A_PCMSK) -DBUTTON_A_PCIE=$(BUTTON_A_PCIE) -DBUTTON_B_PCMSK=$(BUTTON_B_PCMSK) -DBUTTON_B_PCIE=$(BUTTON_B_PCIE)

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
objcopy:
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

clean:
	rm -f *.bin *.hex