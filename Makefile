
TARGET  := bin/boids
SRCS    := src/boids.c
OBJS    := $(SRCS:.c=.o)
INCLUDE	+= -Iinclude
LIBS    += `pkg-config --libs --cflags raylib`
CC      = cc

all: dirs $(TARGET)

dirs::
	mkdir -p bin

$(TARGET): $(OBJS)
	$(CC) $(INCLUDE) -o $@ $^ $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $(INCLUDE) -o $@ -c $<

run: all
	./bin/boids

clean:
	-rm -f src/*.o
	-rm -rf bin