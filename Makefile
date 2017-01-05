TARGET          = cnes

MODULES         = nes mappers emu sim util

CC              = gcc
CXX		= g++

CFLAGS          := -std=c99 -I./ 
CXXFLAGS	:= -std=c++11 -I./ `pkg-config --cflags QtCore QtGui`

DCFLAGS         := -g -ggdb3 -O0 -Wall -pedantic -Wextra -Wundef -Wshadow \
                  -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
                  -Wswitch-default -Wswitch-enum \
                  -Wunreachable-code -Winit-self

RCFLAGS         := -O2 -fwhole-program


LIBS            := `pkg-config --libs QtCore QtGui`

MOC		:= moc

include         $(patsubst %, %/module.mk, $(MODULES))

OBJ             := $(patsubst %.c, %.o, $(filter %.c,$(SRC)))
OBJXX		:= $(patsubst %.cxx, %.o, $(filter %.cxx,$(SRCXX)))
MOCXX		:= $(patsubst %.hxx, %.moc.cxx, $(filter %.hxx, $(INCXX)))
OBJMOCXX	:= $(patsubst %.moc.cxx, %.moc.o, $(filter %.moc.cxx, %.moc.o, $(MOCXX)))


.PHONY: debug
debug: CFLAGS += $(DCFLAGS)
debug: CXXFLAGS += $(DCFLAGS)
debug: build

.PHONY: release
release: CFLAGS += $(RCFLAGS)
release: CXXFLAGS += $(RCFLAGS)
release: build


.PHONY: build
build: $(OBJ) $(OBJMOCXX) $(OBJXX) 
	@$(CXX) $(LDFLAGS) $(OBJ) $(OBJMOCXX) $(OBJXX) -o $(TARGET) $(LIBS)
	@echo [LD] Linked $^ into binary $(TARGET)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo [CC] Compiled $^ into $@

%.o:%.cxx
	@$(CXX) $(CXXFLAGS) -c $^ -o $@
	@echo [CXX] Compiled $^ into $@

%.moc.cxx: %.hxx
	@$(MOC) $< -o $@
	@echo [MOC] Compiled $^ into $@

%.moc.o: %.moc.cxx
	@$(CXX) $(CXXFLAGS) -c $^ -o $@
	@echo [MOC[ Compiled $^ into $@

.PHONY: clean
clean:
	@rm -f $(OBJ) $(OBJXX) $(MOCXX) $(MOCOBJXX) $(TARGET) cnes.log core
	@echo Cleaned $(OBJ) $(OBJXX) $(MOCXX) $(OBJMOCXX) and $(TARGET)
