
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall
OBJECTS = joystick.o main.o
INCFLAGS = -I/usr/local/include/SDL2
LDFLAGS = -Wl,-rpath,-L/usr/local/lib
LIBS = -lpthread -lSDL2

all: joystick

joystick: $(OBJECTS)
	$(CC) -o joystick $(OBJECTS) $(LDFLAGS) $(LIBS) $(INCFLAGS)

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
