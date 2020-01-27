FLAGS=-Wall -std=c++11

all: main

main: main.o kernel.o source.o camera.o object.o surface.o display.o
	g++ $(FLAGS) -o main $^

main.o: main.cpp 
	g++ $(FLAGS) -c $<

kernel.o: kernel.cpp
	g++ $(FLAGS) -c $<

camera.o: camera.cpp
	g++ $(FLAGS) -c $<

object.o: object.cpp
	g++ $(FLAGS) -c $<

surface.o:surface.cpp
	g++ $(FLAGS) -c $<

source.o: source.cpp
	g++ $(FLAGS) -c $<

display.o: display.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o




