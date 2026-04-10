## Instalar AVRDUDE

https://github.com/avrdudes/avrdude/

## Manual

```bash
       avrdude — driver program for ‘‘simple'' Atmel AVR MCU programmer

       avrdude  [-p,  --part  partname]  [-b,  --baud  baudrate]  [-B, --bitclock bitclock] [-c, --programmer programmer-id] [-C, --config config-file]
               [-N, --noconfig] [-A] [-D, --noerase] [-e, --erase] [-E exitspec[,exitspec]] [-F] [-i delay] [-l, --logfile logfile] [-n, --test-memory]
               [-O, --osccal] [-P, --port port] [-r, --reconnect] [-q, --quell] [-T cmd] [-t,  --terminal]  [-U,  --memory  memory:op:filename:filefmt]
               [-v, --verbose] [-x extended_param] [-V, --noverify-memory] [--version]
```

## Comando

```bash
  avrdude -v -p atmega328p -c arduino --port /dev/ttyACM0 --baud 115200 -D -U flash:w:"build/main.hex":i
``` 

```bash
  make upload AULA=aula4.3-pisca-led-avrdude/ PORT=/dev/ttyACM0 BAUD=115200
```