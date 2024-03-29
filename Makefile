
#
# rrstest, 2013 by Antonio Dell'elce, antonio@dellelce.com
#

CC             = gcc
TARGET         = rrstest

SHELL          = /bin/bash

CFILES         = src/main.c src/rrs.c
OFILES         = obj/main.o obj/rrs.o
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

obj/main.o: src/main.c $(HFILES) ./includes/rrs.h
	@echo "CC "src/main.c
	@$(CC) -c $(CFLAGS) -o obj/main.o src/main.c

obj/rrs.o: src/rrs.c $(HFILES) ./includes/rrs.h
	@echo "CC "src/rrs.c
	@$(CC) -c $(CFLAGS) -o obj/rrs.o src/rrs.c

 
#  
# clean
#    
     
clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
# redo
#

redo: clean all

