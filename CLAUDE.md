# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**aulas-micro** is a portfolio of microcontroller learning projects for an embedded systems course. The focus is **bare metal programming** (direct register manipulation) on the **ATmega328** microcontroller.

- **Microcontroller**: ATmega328 (Arduino Uno compatible)
- **Toolchain**: XC8 2.36 (Microchip)
- **IDE**: Microchip Studio
- **Simulation**: SimulIDE
- **Language**: C (direct register manipulation, no abstractions)
- **Mentoring Style**: Socratic method - ask questions, reveal contradictions, let learner discover solutions. Never give complete code solutions unless explicitly requested with "give me the full code".
- **Build System**: Makefile at root (auto-detects aulas, no per-folder makefiles needed)

## Repository Structure

```
aulas-micro/
├── portifolio/                    # Main projects organized by lesson
│   ├── aula1_estruturacao_proj/   # Aula 1.1-1.2: Basic structure + blink LED
│   ├── aula2_gpio/                # Aula 1.3: GPIO Advanced (atividade1, atividade2 - natal)
│   ├── aula3_interrupts/          # Aula 1.4: Interrupts (INT0, INT1, PCINT2)
│   ├── aula3.1_teste_makefile/    # Build system testing
│   ├── aula4-usart/               # Aula 1.6: USART serial communication (9600/115200)
│   ├── portifolio.atsln           # Visual Studio solution file
│   ├── Makefile                   # Build system (root level)
│   └── CLAUDE.md                  # Build system documentation
├── exemplos/                      # Example code from lessons (single-file patterns)
│   ├── portb.c, ddrb.c, delay.c   # Basic GPIO patterns
│   ├── portb_shadow.c             # Port Shadowing (cli/sei protection)
│   ├── rising_falling_edge.c      # Edge detection (intermediate)
│   ├── pinb_shadow.c              # PINB_shadow synchronized
│   └── state_machine.c            # State Machine pattern (3 states)
└── CLAUDE.md                      # This file
```

## Code Architecture

### Progression of Topics Covered

**Aula 1.3 (GPIO Advanced)** ✅ COMPLETED
- Basic I/O (DDRB, PORTB, PINB)
- Port Shadowing (RMW safety with cli/sei)
- Edge Detection (rising/falling transitions)
- State Machines (coordinating multiple peripherals)

**Aula 1.4 (Interrupts)** ✅ COMPLETED
- External Interrupts (INT0, INT1)
- Pin Change Interrupts (PCINT2)
- Edge detection inside ISR handlers
- Flag-driven architecture (central event handling)

**Aula 1.6 (USART)** ✅ COMPLETED
- BAUDRATE calculation: (F_CPU / (16 * BAUD)) - 1
- UCSR0B configuration (TXEN0, UCSZ02)
- UCSR0C configuration (parity, stop bits, character size)
- Transmit: UDR0 register
- Async modes (9600, 115200)

### Bare Metal Conventions

- **Direct register access**: DDRB, PORTB, PINB, UBRR0, UCSR0A/B/C (no digitalWrite)
- **Bit manipulation**: `|=` (set), `&= ~(...)` (clear), `^=` (toggle), `<<` (shift)
- **F_CPU definition**: Must define `#define F_CPU 16000000UL` before `#include <util/delay.h>`
- **Interrupt naming**: ISR(INT0_vect), ISR(PCINT2_vect), with sei()/cli() for atomicity
- **Flag-driven design**: ISR sets flags, main loop handles them (prevents ISR bloat)

## Building and Compiling

### With Makefile (Recommended)

```bash
# Build single aula
make build AULA=aula3_interrupts

# Build all
make all

# List available aulas
make list

# Clean single aula
make clean AULA=aula2_gpio

# Clean all
make clean-all
```

### Microchip Studio (Primary IDE)

1. Open `portifolio/portifolio.atsln` in Microchip Studio
2. Select target project
3. Build → Build Solution (or F7)
4. Output: `.elf` file in build/ folder

## Simulation

### SimulIDE

```bash
# Launch SimulIDE with circuit file
simulide portifolio/aula2_gpio/natal.sim1 &
simulide portifolio/aula3_interrupts/simulide/circuit.sim1 &
simulide portifolio/aula4-usart/circuito.sim1 &
```

- Open `.sim1` files in SimulIDE (or use command above)
- Validate register operations on virtual hardware
- Test interrupt behavior with simulated pin changes

## Key Lesson Topics (by date)

Progress through course:

- **1.1** (13/02): Processor & Memory architecture ✅
- **1.2** (20/02): Development tools (Microchip Studio, GIT, SimulIDE) ✅
- **3.1** (27/02): Version control (GIT, commits, GitHub) ✅
- **1.3** (06/03): Digital I/O, GPIO ports, bit operations ✅ COMPLETED
  - ✅ Basic I/O (DDRB, PORTB, PINB)
  - ✅ Port Shadowing & Read-Modify-Write (RMW) safety
  - ✅ Edge detection (rising/falling transitions)
  - ✅ State Machines (3-state controller example: natal)
- **1.4** (13/03): Interrupts, DMA, interrupt vectors ✅ COMPLETED
  - ✅ External interrupts (INT0, INT1)
  - ✅ Pin Change Interrupts (PCINT2)
  - ✅ Edge detection inside ISR
  - ✅ Flag-driven architecture
- **1.5** (20/03): Serial protocols (UART, SPI) ⏳
- **1.6** (27/03): USART module & RS232/RS485 ✅ COMPLETED
  - ✅ UBRR, UCSR0A/B/C configuration
  - ✅ BAUDRATE calculation
  - ✅ Transmit via UDR0
- **2.1** (24/04): SPI protocol & peripheral communication ⏳
- **2.2** (08/05): I2C/TWI communication ⏳
- **2.3** (15/05): Timers & Counters ⏳
- **2.4** (22/05): PWM, input capture, comparators ⏳
- **2.5** (29/05): ADC (Analog-to-Digital conversion) ⏳
- **3.2** (05/06): Programming tools (AVRDUDE, bootloader) ⏳
- **2.6** (12/06): Digital signal processing ⏳
- **2.7** (19/06): EEPROM & power management (sleep modes) ⏳

## Common Development Patterns

### Interrupts with Flags (Flag-Driven Architecture)

```c
// Global flag set by ISR
volatile int flag_event = 0;

// Interrupt handler (keep it SHORT)
ISR(INT0_vect) {
    flag_event = 1;  // Just set flag, do NOT do heavy work here
}

int main(void) {
    sei();  // Enable interrupts globally

    while(1) {
        if(flag_event) {
            // Handle event in main loop (not in ISR)
            do_something();
            flag_event = 0;
        }
    }
}
```

**Why**: ISRs should be short. Heavy work goes in main loop.

### Pin Change Interrupt with Edge Detection

```c
volatile int prev_state = 0;

ISR(PCINT2_vect) {
    int current_state = PIND & (1<<PIND2);

    // Detect RISING edge (0 → 1)
    if(current_state && !prev_state) {
        // Rising edge detected
        flag_event = 1;
    }

    prev_state = current_state;
}

void PCINT_init(void) {
    PCMSK2 |= (1<<PCINT18);  // Enable D2
    PCICR |= (1<<PCIE2);     // Enable group PCIE2
    sei();
}
```

### USART Configuration

```c
#define BAUDRATE_9600 103     // (16*10^6) / (16*9600) - 1
#define F_CPU 16000000

void usart_init_9600(void) {
    UBRR0 = BAUDRATE_9600;

    // Control Register A: Double speed = 0
    UCSR0A = (0 << U2X0);

    // Control Register B: TX enable, 8-bit character
    UCSR0B = (1 << TXEN0) | (0 << UCSZ02);

    // Control Register C: Async, no parity, 1 stop bit, 8-bit
    UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) |  // Async mode
             (0 << UPM01) | (0 << UPM00) |       // No parity
             (0 << USBS0) |                      // 1 stop bit
             (1 << UCSZ01) | (1 << UCSZ00);      // 8-bit char
}

// Transmit a byte
void usart_send(uint8_t data) {
    while(!(UCSR0A & (1 << UDRE0)));  // Wait for ready
    UDR0 = data;
}
```

### Port Shadowing (Safe I/O with Interrupts)

```c
static volatile uint8_t PORTB_shadow = 0x00;

void gpio_safe_set_pin(uint8_t pin) {
    cli();
    PORTB_shadow |= (1 << pin);
    PORTB = PORTB_shadow;
    sei();
}

void gpio_safe_clear_pin(uint8_t pin) {
    cli();
    PORTB_shadow &= ~(1 << pin);
    PORTB = PORTB_shadow;
    sei();
}
```

### Bit Shifting for LED Sequences

```c
// "Pinheirinho de Natal" pattern
uint8_t pattern = 1;  // Start with bit 0

while(1) {
    PORTC = pattern;

    // Shift left to next LED
    pattern = pattern << 1;

    // Wrap around when reach bit 5
    if(pattern & (1 << 6)) {
        pattern = 1;
    }

    _delay_ms(500);
}
```

## Important Notes

- **No Arduino abstractions**: This is bare metal - use registers, not `digitalWrite()`
- **Always define F_CPU**: Required for accurate delay and USART calculations
- **Datasheet is your reference**: ATmega328 datasheet defines all registers and bit positions
- **Atomic commits**: Each git commit should represent one learning concept
- **SimulIDE validation**: Test circuits in simulation before expecting physical behavior
- **ISR efficiency**: Keep interrupt handlers SHORT - do heavy work in main loop
- **Flag-driven design**: ISR sets flag, main loop responds (safer than ISR doing work)

## Development Workflow

### Current Progress

**Completed Aulas:**
- ✅ Aula 1.3 (GPIO Advanced) - Branch: `gpio-avancado/topicos-1-4`
- ✅ Aula 1.4 (Interrupts) - In `aula3_interrupts/`
- ✅ Aula 1.6 (USART) - In `aula4-usart/`

### Branch Strategy

```bash
# View current branches
git branch -a

# Switch to feature branch
git checkout gpio-avancado/topicos-1-4

# Merge when ready
git checkout main
git merge gpio-avancado/topicos-1-4
```

### Building Projects

```bash
# Build specific aula
cd portifolio
make build AULA=aula3_interrupts

# Or from root
make -C portifolio build AULA=aula3_interrupts

# List all available aulas
make list
```

## Helpful Resources

- **ATmega328 Datasheet**: Register definitions, interrupt vectors, baud rate tables
- **Microchip Studio**: Built-in simulator and debugger
- **SimulIDE**: Realistic circuit simulation with components and oscilloscope
- **AVR Libc**: `avr/interrupt.h` for ISR macros, `util/delay.h` for timing

---

## Claude Code Mentoring Guidelines

This section tells Claude how to work effectively in this repository.

### Mentoring Philosophy (Socratic Method)

**NEVER give complete code solutions** unless explicitly asked with "give me the full code".

**Do:**
- Ask questions that reveal contradictions
- Ask "what register controls X?" to guide datasheet research
- Let silence exist - let learner sit with difficult questions
- Connect concepts to **physical hardware**: "What happens electrically in the silicon?"
- Say "correct" briefly, then move forward
- Reference exact file paths: `portifolio/aula3_interrupts/main.c:17`

**Don't:**
- Offer numbered options like "what do you prefer?"
- Give hints unless explicitly asked "give me a hint"
- Tell them they're wrong directly - ask revealing questions
- Explain concepts they can discover through guided questions

### Code Example Patterns

Examples in `/exemplos` demonstrate foundational patterns:
- `portb_shadow.c` - Safe PORTB writing with `cli()`/`sei()`
- `pinb_shadow.c` - Input shadowing (multiple pins synchronized)
- `state_machine.c` - 3-state machine example

### Teaching Progression

**Completed Topics:**
1. ✅ Basic GPIO (DDRB, PORTB, PINB)
2. ✅ Port Shadowing (RMW safety)
3. ✅ Edge Detection (rising/falling)
4. ✅ State Machines (coordinating peripherals)
5. ✅ Interrupts (INT0, INT1, PCINT)
6. ✅ Flag-driven architecture
7. ✅ USART (BAUDRATE, transmission)

**Current Level**: Post-Aula 1.4, implementing real protocols (USART, preparing for SPI/I2C)

**Next Major Topics**: Aula 2.x series - SPI, I2C, Timers, PWM, ADC

### Important Caveats

- **No Arduino abstractions**: Enforce bare metal (registradores, not `digitalWrite()`)
- **Datasheet is law**: Always reference ATmega328 datasheet sections
- **SimulIDE validation**: Test in simulator before assuming hardware behavior
- **ISR safety**: Emphasize short ISRs, flag-driven main loop pattern
- **Atomic operations**: RMW operations MUST use cli()/sei() when interrupts are enabled
