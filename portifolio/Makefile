# ==============================================================================
# Makefile Raiz - Portfólio de Aulas de Microcontroladores
# ==============================================================================
# Compilador unificado para todas as aulas
# Detecta automaticamente as aulas e compila de fora para dentro
#
# Uso:
#   make build AULA=aula3_interrupts    - Compila uma aula específica
#   make clean AULA=aula3_interrupts    - Limpa uma aula específica
#   make all                             - Compila todas as aulas
#   make clean-all                       - Limpa tudo
# ==============================================================================

# ==============================================================================
# DETECÇÃO AUTOMÁTICA E CONFIGURAÇÃO
# ==============================================================================

# Detecta todas as pastas que são aulas (subdiretórios da raiz)
AULAS := $(filter-out .vscode .vs, $(wildcard */))
AULAS := $(patsubst %/,%,$(AULAS))

# Configurações do Compilador AVR
MCU      = atmega328p
F_CPU    = 16000000UL
COMPILER = xc8-cc
OBJCOPY  = avr-objcopy
SIZE     = avr-size

# Configurações do AVRDUDE (upload)
AVRDUDE      = avrdude
UPLOAD_MCU   = atmega328p
UPLOAD_PROG  = arduino
UPLOAD_PORT  = $(if $(PORT),$(PORT),/dev/ttyACM0)
UPLOAD_BAUD  = $(if $(BAUD),$(BAUD),115200)

# Paths do XC8
DFP      = /opt/microchip/mplabx/v6.25/packs/Microchip/ATmega_DFP/3.3.279/xc8
XC8_INCLUDE = -I/opt/microchip/xc8/v3.10/avr/lib/gcc/avr/5.4.0/include \
              -I/opt/microchip/xc8/v3.10/avr/avr/include

# Flags de compilação
CFLAGS = -mcpu=$(MCU)
CFLAGS += -mdfp="$(DFP)"
CFLAGS += -O2
CFLAGS += $(XC8_INCLUDE)
CFLAGS += -Wall -Wextra

# ==============================================================================
# FUNÇÕES AUXILIARES
# ==============================================================================

# Detecta arquivos .c em uma pasta
get_sources = $(wildcard $(1)/*.c $(1)/src/*.c)

# Detecta pasta include
get_include = $(if $(wildcard $(1)/include),-I$(1)/include,-Iinclude)

# ==============================================================================
# ALVOS PRINCIPAIS
# ==============================================================================

.DEFAULT_GOAL := help

# Validar se AULA foi especificada (exceto para help, all, clean-all, etc)
check-aula:
ifndef AULA
	@echo "Erro: Você precisa especificar a aula!"
	@echo ""
	@echo "Uso: make build AULA=<nome_da_pasta>"
	@echo ""
	@echo "Aulas disponíveis:"
	@for aula in $(AULAS); do \
		echo "  - $$aula"; \
	done
	@echo ""
	@exit 1
endif
	@if [ ! -d "$(AULA)" ]; then \
		echo "Erro: Pasta '$(AULA)' não encontrada!"; \
		exit 1; \
	fi

# Compilar uma aula específica
build: check-aula
	@echo "==> Compilando $(AULA)"
	@$(MAKE) --no-print-directory _build_aula AULA=$(AULA)
	@echo ""

# Target interno para compilação
_build_aula:
	$(eval SOURCES := $(call get_sources,$(AULA)))
	$(eval INCLUDE := $(call get_include,$(AULA)))
	$(eval PROJECT := main)
	$(eval OUTPUT_DIR := $(AULA)/build)
	$(eval ELF := $(OUTPUT_DIR)/$(PROJECT).elf)
	$(eval HEX := $(OUTPUT_DIR)/$(PROJECT).hex)
	@mkdir -p $(OUTPUT_DIR)
	@if [ -z "$(SOURCES)" ]; then \
		echo "Erro: Nenhum arquivo .c encontrado em $(AULA)/"; \
		echo "Procurei em: $(AULA)/*.c e $(AULA)/src/*.c"; \
		exit 1; \
	fi
	@echo "  Compilando: $(SOURCES)"
	@$(COMPILER) $(CFLAGS) $(INCLUDE) -o $(ELF) $(SOURCES)
	@echo "  Gerando HEX: $(HEX)"
	@$(OBJCOPY) -O ihex $(ELF) $(HEX)
	@echo "  Build concluído: $(HEX)"

# Compilar e fazer upload para o microcontrolador
upload: build
	@echo "==> Fazendo upload de $(AULA) para $(UPLOAD_PORT)"
	$(AVRDUDE) -v -p $(UPLOAD_MCU) -c $(UPLOAD_PROG) --port $(UPLOAD_PORT) --baud $(UPLOAD_BAUD) -D -U flash:w:"$(AULA)/build/main.hex":i
	@echo ""

# Limpar uma aula específica
clean: check-aula
	@echo "==> Limpando $(AULA)"
	@rm -rf $(AULA)/build
	@rm -f $(AULA)/*.elf $(AULA)/*.hex $(AULA)/*.o
	@echo "  Limpeza concluída"
	@echo ""

# Compilar todas as aulas
all:
	@echo "==> Compilando todas as aulas"
	@echo ""
	@for aula in $(AULAS); do \
		echo "==> Compilando $$aula"; \
		$(MAKE) --no-print-directory build AULA=$$aula || true; \
	done
	@echo "==> Compilação completa"
	@echo ""

# Limpar todas as aulas
clean-all:
	@echo "==> Limpando todas as aulas"
	@echo ""
	@for aula in $(AULAS); do \
		echo "==> Limpando $$aula"; \
		$(MAKE) --no-print-directory clean AULA=$$aula || true; \
	done
	@echo "==> Limpeza concluída"
	@echo ""

# ==============================================================================
# INFORMAÇÕES
# ==============================================================================

list:
	@echo "Aulas detectadas automaticamente:"
	@for aula in $(AULAS); do \
		echo "  - $$aula"; \
		if [ -f $$aula/*.c ] || [ -f $$aula/src/*.c ]; then \
			echo "    [com arquivos .c]"; \
		else \
			echo "    [sem arquivos .c]"; \
		fi; \
	done
	@echo ""

status:
	@echo "Status das aulas:"
	@echo ""
	@for aula in $(AULAS); do \
		echo "[$$aula]"; \
		if [ -f $$aula/build/main.hex ]; then \
			echo "  Compilado: SIM"; \
		else \
			echo "  Compilado: NAO"; \
		fi; \
		SRCS=$$(find $$aula -maxdepth 2 -name "*.c" 2>/dev/null | wc -l); \
		echo "  Arquivos .c: $$SRCS"; \
		echo ""; \
	done

help:
	@echo "================================================================"
	@echo "  Makefile Raiz - Portfólio de Microcontroladores"
	@echo "================================================================"
	@echo ""
	@echo "Compilação de Aula Específica:"
	@echo "  make build  AULA=<pasta>   - Compila uma aula específica"
	@echo "  make upload AULA=<pasta>   - Compila e faz upload (avrdude)"
	@echo "  make clean  AULA=<pasta>   - Limpa uma aula específica"
	@echo ""
	@echo "Exemplos:"
	@echo "  make build  AULA=aula3_interrupts"
	@echo "  make upload AULA=aula4.3-pisca-led-avrdude"
	@echo "  make upload AULA=aula4.3-pisca-led-avrdude PORT=/dev/ttyUSB0"
	@echo "  make clean  AULA=aula1_estruturacao_proj"
	@echo ""
	@echo "Upload (variáveis configuráveis):"
	@echo "  PORT=<porta>    (padrão: $(UPLOAD_PORT))"
	@echo "  BAUD=<baud>     (padrão: $(UPLOAD_BAUD))"
	@echo ""
	@echo "Compilação de Todas as Aulas:"
	@echo "  make all               - Compila todas as aulas"
	@echo "  make clean-all         - Limpa todas as aulas"
	@echo ""
	@echo "Informações:"
	@echo "  make list              - Lista aulas e arquivos .c"
	@echo "  make status            - Status de compilação"
	@echo "  make help              - Esta ajuda"
	@echo ""
	@echo "Aulas detectadas:"
	@for aula in $(AULAS); do \
		echo "  - $$aula"; \
	done
	@echo ""
	@echo "Nota: Nenhum Makefile é necessário nas pastas das aulas!"
	@echo "      Este Makefile detecta automaticamente os arquivos .c"
	@echo ""

# ==============================================================================
# CONFIGURAÇÃO PHONY
# ==============================================================================

.PHONY: help all clean-all build upload clean list status check-aula _build_aula
