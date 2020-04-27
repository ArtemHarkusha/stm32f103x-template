# path to STM32F103 standard peripheral library
CMSIS ?= ./CMSIS/

# list of source files
SOURCES  = main.c
SOURCES += ./lib/lib_gpio.c
SOURCES += $(CMSIS)/system_stm32f10x.c
SOURCES += $(CMSIS)/startup_stm32f10x_md.s

# name for output binary files
PROJECT ?= led

# compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# path to st-flash (or should be specified in PATH)
STM32_FLASH ?= stm32flash

# specify compiler flags
CFLAGS  = -g -O2 -Wall
CFLAGS += -T$(CMSIS)/stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I$(CMSIS)
CFLAGS += -I./lib

OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin

# flash
burn:
	sudo $(STM32_FLASH) -w $(PROJECT).bin -v -g 0x0 /dev/ttyUSB0
