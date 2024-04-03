#
# rrstest, 2013 by Antonio Dell'elce, antonio@dellelce.com
#
CC             = gcc
TARGET         = rrstest

SHELL          = /bin/bash

CFILES         = src/main.c src/rrs.c
OFILES         = o/main.o o/rrs.o
LDFLAGS	       = 

LOC_HFILES     = 
HFILES         = $(LOC_HFILES)

INCLUDES       =  -I./includes
DEBUG          = 
CFLAGS         = -Wall -O2  $(INCLUDES) $(DEBUG)
LIBS           = 

#
# --- RULES ---
#
all: $(TARGET)

$(TARGET):   $(OFILES)
	@echo "LINK " $(TARGET)
	@$(CC) -o $(TARGET) $(LDFLAGS) $(OFILES) $(LIBS)

#
# -- DEPS --
#
o/main.o: src/main.c $(HFILES) ./includes/rrs.h
	@echo "CC "src/main.c
	@$(CC) -c $(CFLAGS) -o o/main.o src/main.c

o/rrs.o: src/rrs.c $(HFILES) ./includes/rrs.h
	@echo "CC "src/rrs.c
	@$(CC) -c $(CFLAGS) -o o/rrs.o src/rrs.c

#  
# clean
clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
run: $(TARGET)
	@./$(TARGET)

#
# redo
redo: clean all
