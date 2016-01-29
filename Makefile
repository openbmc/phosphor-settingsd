
EXE     = settings_manager

OBJS    = $(EXE).o   \


DEPPKGS = libsystemd
CC      ?= $(CROSS_COMPILE)gcc
INCLUDES += $(shell pkg-config --cflags $(DEPPKGS)) 
LIBS += $(shell pkg-config --libs $(DEPPKGS))
CFLAGS += -Wall

all: $(EXE)

%.o : %.c 
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(EXE): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f $(OBJS) $(EXE) *.o 
