######################################################################################
#
#   !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!    
#
######################################################################################
# 
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#
######################################################################################

######################################################################################
# GNU GCC ARM Embeded Toolchain base directories and binaries 
######################################################################################
CROSS_COMPILE ?= arm-none-eabi
GCC_BASE = /link/gcc-arm-none-eabi/
GCC_BIN  = $(GCC_BASE)bin/
GCC_LIB  = $(GCC_BASE)arm-none-eabi/lib/
GCC_INC  = $(GCC_BASE)arm-none-eabi/include/
AS       = $(GCC_BIN)$(CROSS_COMPILE)-gcc -x assembler-with-cpp 
CC       = $(GCC_BIN)$(CROSS_COMPILE)-gcc
CPP      = $(GCC_BIN)$(CROSS_COMPILE)-g++
LD       = $(GCC_BIN)$(CROSS_COMPILE)-ld
OBJDUMP  = $(GCC_BIN)$(CROSS_COMPILE)-objdump
OBJCOPY  = $(GCC_BIN)$(CROSS_COMPILE)-objcopy
SIZE     = $(GCC_BIN)$(CROSS_COMPILE)-size

######################################################################################
# Custom options for cortex-m and cortex-r processors
######################################################################################
CORTEX_M0PLUS_CC_FLAGS  = -mthumb -mcpu=cortex-m0plus
CORTEX_M0PLUS_LIB_PATH  = $(GCC_LIB)armv6-m
CORTEX_M0_CC_FLAGS      = -mthumb -mcpu=cortex-m0
CORTEX_M0_LIB_PATH      = $(GCC_LIB)armv6-m
CORTEX_M1_CC_FLAGS      = -mthumb -mcpu=cortex-m1
CORTEX_M1_LIB_PATH      = $(GCC_LIB)armv6-m
CORTEX_M3_CC_FLAGS      = -mthumb -mcpu=cortex-m3
CORTEX_M3_LIB_PATH      = $(GCC_LIB)armv7-m
CORTEX_M4_NOFP_CC_FLAGS = -mthumb -mcpu=cortex-m4
CORTEX_M4_NOFP_LIB_PATH = $(GCC_LIB)armv7e-m
CORTEX_M4_SWFP_CC_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
CORTEX_M4_SWFP_LIB_PATH = $(GCC_LIB)armv7e-m/softfp
CORTEX_M4_HWFP_CC_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORTEX_M4_HWFP_LIB_PATH = $(GCC_LIB)armv7e-m/fpu

######################################################################################
# Main makefile project configuration
#    PROJECT      = <name of the target to be built>
#    MCU_CC_FLAGS = <one of the CC_FLAGS above>
#    MCU_LIB_PATH = <one of the LIB_PATH above>
#    DEBUG_LEVEL  = < -g compiler option or nothing >
#    OPTIM_LEVEL  = < -O compiler option or nothing >
######################################################################################
PROJECT           = main
MCU_CC_FLAGS      = $(CORTEX_M3_CC_FLAGS)
MCU_LIB_PATH      = $(CORTEX_M3_LIB_PATH)
DEBUG_LEVEL       =
OPTIM_LEVEL       =
LINKER_SCRIPT     = ../src/STM32F103VC_flash.ld

PROJ_SRC = ../src/main.c \
	  ../src/stm32f10x_it.c \
	  ../src/system_stm32f10x.c

LIB_SRC = ../lib/CMSIS/CM3/CoreSupport/core_cm3.c \
	../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
	../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
	../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \

SOURCES = $(PROJ_SRC) $(LIB_SRC)
SOURCES_ASM = ../src/startup_stm32f10x_hd.s

#HEADERS = \
#	  $(TOPDIR)/Project/STM32F0xx_StdPeriph_Templates/main.h \
#	  $(TOPDIR)/Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_conf.h \
#	  $(TOPDIR)/Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.h \
#	  $(wildcard $(TOPDIR)/Libraries/CMSIS/Include/*.h) \
#	  $(wildcard $(TOPDIR)/Libraries/CMSIS/Device/ST/STM32F0xx/Include/*.h) \
#	  $(wildcard $(TOPDIR)/Libraries/STM32F0xx_StdPeriph_Driver/inc/*.h)

INCLUDES = ../inc \
	../lib/STM32F10x_StdPeriph_Driver/inc \
	../lib/CMSIS/CM3/CoreSupport \
	../lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x

PROJECT_INC_PATHS = $(INCLUDES)
PROJECT_LIB_PATHS =
PROJECT_LIBRARIES =
PROJECT_SYMBOLS   =
#PROJECT_SYMBOLS   = -DTOOLCHAIN_GCC_ARM -DUSE_STDPERIPH_DRIVER -DNO_RELOC='0'

######################################################################################
# Main makefile system configuration
######################################################################################
#SYS_INC_PATHS = $(GCC_INC)
SYS_INC_PATHS =
SYS_LIB_PATHS = $(MCU_LIB_PATH)
SYS_LIBRARIES = -lstdc++ -lsupc++ -lm -lc -lg -lnosys
SYS_LD_FLAGS  =

###############################################################################
# Command line building
###############################################################################
ifdef DEBUG_LEVEL
CC_DEBUG_FLAGS = -g$(DEBUG_LEVEL)
else
CC_DEBUG_FLAGS =
endif

ifdef OPTIM_LEVEL
CC_OPTIM_FLAGS = -O$(OPTIM_LEVEL)
else
CC_OPTIM_FLAGS =
endif

INCLUDE_PATHS 	= $(patsubst %,-I%,$(PROJECT_INC_PATHS) $(SYS_INC_PATHS))
LIBRARY_PATHS 	= $(patsubst %,-L%,$(PROJECT_LIB_PATHS) $(SYS_LIB_PATHS))
OBJS 			= $(SOURCES:.c=.o) $(SOURCES_ASM:.s=.o)

ASFLAGS = $(MCU_CC_FLAGS) -Wa,-amhls=$(<:.s=.lst)

CFLAGS = $(MCU_CC_FLAGS) $(CC_OPTIM_FLAGS) $(CC_DEBUG_FLAGS) -Wa,-ahlms=$(<:.c=.lst)
CFLAGS += -fno-common -fverbose-asm -fomit-frame-pointer -fno-exceptions -ffunction-sections -fdata-sections -mlittle-endian -std=c99
CFLAGS += $(PROJECT_SYMBOLS)

# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

LD_FLAGS = $(MCU_CC_FLAGS) -T$(LINKER_SCRIPT) -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch
LD_FLAGS += -Wl,--gc-sections $(SYS_LD_FLAGS) $(LIBRARY_PATHS) 
LD_LIBS = $(SYS_LIBRARIES) $(PROJECT_LIBRARIES)


# build target
BUILD_TARGET = $(PROJECT)

###############################################################################

all: build

build: $(OBJS) $(BUILD_TARGET).elf $(BUILD_TARGET).bin $(BUILD_TARGET).hex $(BUILD_TARGET).lst

%.o : %.c
	$(CC) -c $(CFLAGS) -I . $(INCLUDE_PATHS) $< -o $@

%.o : %.s
	$(AS) -c $(ASFLAGS) -I . $(INCLUDE_PATHS) $< -o $@

$(BUILD_TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LD_FLAGS) $(LD_LIBS) -o $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.lst: %.elf
	$(OBJDUMP) -x -S $(BUILD_TARGET).elf > $@

size: $(BUILD_TARGET).elf
	$(SIZE) $(BUILD_TARGET).elf

clean:
	-rm -f $(OBJS)
	-rm -f $(BUILD_TARGET).bin
	-rm -f $(BUILD_TARGET).elf
	-rm -f $(BUILD_TARGET).map
	-rm -f $(BUILD_TARGET).hex
	-rm -f $(SOURCES:.c=.c.bak)
	-rm -f $(SOURCES:.c=.lst)
	-rm -f $(ASOURCES:.s=.s.bak)
	-rm -f $(ASOURCES:.s=.lst)
	-rm -fR .dep

program: build
	st-flash write $(BUILD_TARGET).bin 0x08000000
## Or with openocd (>= v0.6.0)
#openocd -f board/stm32f0discovery.cfg -c "init; reset halt; flash write_image erase $(BUILD_TARGET).bin 0x08000000; reset run; shutdown"

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***