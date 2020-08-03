########################################################################
# Description:
#  Makefile
########################################################################

ifneq ($TARGET),)
CROSS_TARGET = $(TARGET)-
endif

CC=$(CROSS_TARGET)gcc
CXX=$(CROSS_TARGET)g++

# Name of the application
OUTFILE = kman

SRC = src
BUILD = build

# List of object files
OBJECTS = \
	$(SRC)/main.o

ifneq ($(SYSROOT),)
INCLUDE	:=-I$(SYSROOT)/usr/include -I$(SYSROOT)/usr/local/include 
CFLAGS	:=--sysroot=$(SYSROOT) 
endif

INCLUDE +=-I$(SRC) -I$(SRC)/kman 
CFLAGS 	+=$(INCLUDE) $(CROSS_CC_FLAGS)
LFLAGS 	=-lmenu -lcurses -lpthread

all: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BUILD)/$@ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: $(SRC)/%.cc
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm $(SRC)/*.o $(BUILD)/*.map $(BUILD)/$(OUTFILE)
