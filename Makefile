
all: dirs
	cc src/boids.c `pkg-config --libs --cflags raylib` -o bin/boids

dirs: bin

bin:
	mkdir -p bin

run: all
	./bin/boids

clean:
	rm -rf dirs