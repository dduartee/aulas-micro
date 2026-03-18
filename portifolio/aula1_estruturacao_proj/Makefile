MCU     = atmega328p
DFP     = /opt/microchip/mplabx/v6.25/packs/Microchip/ATmega_DFP/3.3.279/xc8
CC      = xc8-cc
CFLAGS  = -mcpu=$(MCU) -mdfp="$(DFP)" -Iinclude

SRCS    = $(wildcard src/*.c)
OBJS    = $(patsubst src/%.c, output/%.o, $(SRCS))

output/main.hex: output/main.elf
	avr-objcopy -O ihex $< $@

output/main.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

output/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f output/*.o output/*.elf output/*.hex