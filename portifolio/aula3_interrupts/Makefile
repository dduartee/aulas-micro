MCU     = atmega328p
DFP     = /opt/microchip/mplabx/v6.25/packs/Microchip/ATmega_DFP/3.3.279/xc8
CC      = xc8-cc
CFLAGS  = -mcpu=$(MCU) \
          -mdfp="$(DFP)" \
          -Iinclude \
          -I/opt/microchip/xc8/v3.10/avr/lib/gcc/avr/5.4.0/include \
          -I/opt/microchip/xc8/v3.10/avr/avr/include

main.hex: main.elf
	avr-objcopy -O ihex $< $@

main.elf: main.c
	$(CC) $(CFLAGS) -o $@ $^ # $@=main.elf $^=main.c

clean:
	rm -f *.elf *.hex
