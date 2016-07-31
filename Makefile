TARGET          = cnes

MODULES         = nes mappers emu sim util

CC              = gcc
CXX		= g++

CFLAGS          := -std=c99 -I./ 
CXXFLAGS	:= -std=c++11 -I./ `pkg-config --cflags QtCore QtGui`

DCFLAGS         := -g -ggdb3 -O0 -Wall -pedantic -Wextra -Wundef -Wshadow \
                  -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
                  -Waggregate-return -Wswitch-default -Wswitch-enum \
                  -Wunreachable-code -Winit-self

RCFLAGS         := -O2 -fwhole-program


LIBS            := -lX11 -lGL -lGLU -lglut `pkg-config --libs QtCore QtGui`

include         $(patsubst %, %/module.mk, $(MODULES))

OBJ             := $(patsubst %.c,%.o, $(filter %.c,$(SRC)))
OBJXX		:= $(patsubst %.cxx,%.o, $(filter %.cxx,$(SRCXX)))

.PHONY: debug
debug: CFLAGS += $(DCFLAGS)
debug: CXXFLAGS += $(DCFLAGS)
debug: build

.PHONY: release
release: CFLAGS += $(RCFLAGS)
release: CXXFLAGS += $(RCFLAGS)
release: build


.PHONY: build
build: $(OBJ) $(OBJXX)
	@$(CXX) $(LDFLAGS) $(OBJ) $(OBJXX) -o $(TARGET) $(LIBS)
	@echo [LD] Linked $^ into $@

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo [CC] Compiled $^ into $@

%.o:%.cxx
	@$(CXX) $(CXXFLAGS) -c $^ -o $@
	@echo [CXX] Compiled $^ into $@

.PHONY: clean
clean:
	@rm -f $(OBJ) $(OBJXX) $(TARGET) cnes.log core
	@echo Cleaned $(OBJ) and $(TARGET)
