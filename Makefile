TARGET		= nes

CC		= gcc

CFLAGS		= -I./src -I./util -I./mappers --std=c99

LD		= gcc
LDFLAGS		= 

LIBS		= 

SRCD		=./src
UTILD		=./util
MAPD		=./mappers

DEB		=./debug
REL		=./release


SRC		:= $(wildcard $(SRCD)/*.c) $(wildcard $(UTILD)/*.c) $(wildcard $(MAPD)/*.c)
INC		:= $(wildcard $(SRCD)/*.h) $(wildcard $(UTILD)/*.h) $(wildcard $(MAPD)/*.h)


#debug
DCFLAGS		= -g -ggdb3 -O0 -Wall -pedantic -Wextra -Wundef -Wshadow \
		  -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
		  -Waggregate-return -Wswitch-default -Wswitch-enum \
		  -Wunreachable-code -Winit-self 

DLDFLAGS	= 

DOBJD		:=$(DEB)/obj
DOBJ		:=$(SRC:$(SRCD)/%.c=$(DOBJD)/%.o)

DBIND		:=$(DEB)/bin
DBIN		:=$(DBIND)/$(TARGET)


#release
RCFLAGS		= -O3 -fwhole-program
RLDFLAGS	= 

ROBJD		:=$(REL)/obj
ROBJ		:=$(SRC:$(SRCD)/%.c=$(ROBJD)/%.o)

RBIND		:=$(REL)/bin
RBIN		:=$(RBIND)/$(TARGET)

RM		= rm -rf
MKDIR		= mkdir -p

all: release debug

release: $(RBIN)
$(RBIN): $(ROBJ)
	$(MKDIR) $(RBIND)
	$(LD) $(LDFLAGS) $(RLDFLAGS) -o $@ $^
	@echo "[LD] Linked "$(ROJB)", executable "$@" created"

$(ROBJ): $(ROBJD)/%.o: $(SRCD)/%.c $(INC)
	$(MKDIR) $(REL) $(ROBJD)
	$(CC) $(CFLAGS) $(RCFLAGS) -o $@ -c $<
	@echo "[CC] Compiled "$<" succesfully"


debug: $(DBIN)
$(DBIN): $(DOBJ)
	$(MKDIR) $(DBIND)
	$(LD) $(LDFLAGS) $(DLDFLAGS) -o $@ $^
	@echo "[LD] linked "$(DOBJ)", executable "$@" created"

$(DOBJ): $(DOBJD)/%.o : $(SRCD)/%.c $(INC)
	$(MKDIR) $(DEB) $(DOBJD) 
	$(CC) $(CFLAGS) $(DCFLAGS) -o $@ -c $<
	@echo "[CC] Compiled "$<" succesfully"

clean:
	@$(RM) $(DEB) $(REL) $(SRCD)/*~ $(INCD)/*~ $(MAPD)/*~ $(UTILD)/*~ ./*~
	@echo "build cleaned"

