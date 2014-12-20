
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall
OBJECTS = joystick.o main.o
INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = -lpthread

all: joystick

joystick: $(OBJECTS)
	$(CC) -o joystick $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o *~ joystick

.PHONY: all
.PHONY: count
.PHONY: clean
