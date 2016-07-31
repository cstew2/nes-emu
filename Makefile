TARGET          = cnes

MODULES         = nes mappers emu sim util

CC              = gcc

CFLAGS          := -std=c99 -I./

DCFLAGS         := -g -ggdb3 -O0 -Wall -pedantic -Wextra -Wundef -Wshadow \
                  -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
                  -Waggregate-return -Wswitch-default -Wswitch-enum \
                  -Wunreachable-code -Winit-self

RCFLAGS         := -O2 -fwhole-program

LDFLAGS         :=

LIBS            := -lX11 -lGL -lGLU -lglut

include         $(patsubst %, %/module.mk, $(MODULES))

OBJ             := $(patsubst %.c,%.o, $(filter %.c,$(SRC)))


.PHONY: debug
debug: CFLAGS += $(DCFLAGS)
debug:  build

.PHONY: release
release: CFLAGS += $(RCFLAGS)
release: build


.PHONY: build
build: $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET) $(LIBS)
	@echo [LD] Linked $^ into $@

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo [CC] Compiled $^ into $@

.PHONY: clean
clean:
	@rm -f $(OBJ) $(TARGET) cnes.log core
	@echo Cleaned $(OBJ) and $(TARGET)
