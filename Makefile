MCU ?= msp430f149
CROSS_COMPILE ?= msp430-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

# Can't use -f*-sections until SF 3534425 is fixed
OPT_CFLAGS ?= -Os -ffunction-sections -fdata-sections -s
WARN_CFLAGS = -Wall -Wno-main
# Turn off warnings related to brokenness in the TI code
# -Wno-unused-function: Headers provide static function declarations
WARN_CFLAGS += -Wno-unused-function
OPT_LDFLAGS ?= -Wl,-gc-sections
CPPFLAGS = -I.

# TARGET_FLAGS holds things like -msr20, -md20, -mc20, or -mmemory-model=.
# Like -mmcu, it gets passed in both CFLAGS and LDFLAGS.
ifndef TARGET_FLAGS
ifdef MEMORY_MODEL
TARGET_FLAGS=-mmemory-model=$(MEMORY_MODEL)
endif # MEMORY_MODEL
endif # TARGET_FLAGS

CFLAGS=-mmcu=$(MCU) $(TARGET_FLAGS) $(OPT_CFLAGS) $(WARN_CFLAGS) $(XCFLAGS)
LDFLAGS=-mmcu=$(MCU) $(TARGET_FLAGS) $(OPT_LDFLAGS)

# Object file derived from assembler source including preprocessor
%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

SRC = \
hal_board.c \
hal_buttons.c \
hal_serial.c \
main.c


OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

disc.bin: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJ)
	msp430-size disc.bin
clean:
	-rm -f $(OBJ)

realclean: clean
	-rm -f disc.bin $(DEP)

install: disc.bin
	mspdebug tilib 'prog disc.bin'

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEP)
