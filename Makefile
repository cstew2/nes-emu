TARGET          = cnes

MODULES         = nes mappers emu sim util

CC              = gcc
CXX		= g++

CFLAGS          := -std=c11 -I./ 
CXXFLAGS	:= -std=c++11 -fPIC -I./ -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore \
		   -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets

DCFLAGS         := -g -ggdb3 -O0 -Wall -pedantic -Wextra -Wundef -Wshadow \
                  -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
                  -Wswitch-default -Wswitch-enum \
                  -Wunreachable-code -Winit-self

RCFLAGS         := -O2 -fwhole-program

LDFLAGS		:= 

LIBS            := -lQt5Gui -lQt5Core -lpthread

MOC		:= moc

include         $(patsubst %, %/module.mk, $(MODULES))

OBJ             := $(patsubst %.c, %.o, $(filter %.c,$(SRC)))

.PHONY: debug
debug: CFLAGS += $(DCFLAGS)
debug: build

.PHONY: release
release: CFLAGS += $(RCFLAGS)
release: build


.PHONY: build
build: $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET) $(LIBS)
	@echo [LD] Linked $^ into binary $(TARGET)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo [CC] Compiled $^ into $@

.PHONY: clean
clean:
	@rm -f $(OBJ) $(OBJXX) $(MOCXX) $(OBJMOCXX) $(TARGET) cnes.log core
	@echo Cleaned $(OBJ) and $(TARGET)
