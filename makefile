FLAGS=-Wall -std=c++11

all: main

main: main.o kernel.o source.o camera.o object.o surface.o display.o tinyxml2.o loadxml.o
	g++ $(FLAGS) -fopenmp -o main $^

main.o: main.cpp 
	g++ $(FLAGS) -c $<

kernel.o: kernel.cpp
	g++ $(FLAGS) -fopenmp -c $<

camera.o: camera.cpp
	g++ $(FLAGS) -fopenmp -c $<

object.o: object.cpp
	g++ $(FLAGS) -c $<

surface.o:surface.cpp
	g++ $(FLAGS) -c $<

source.o: source.cpp
	g++ $(FLAGS) -c $<

display.o: display.cpp
	g++ $(FLAGS) -c $<

tinyxml2.o: tinyxml2/tinyxml2.cpp
	g++ $(FLAGS) -c $<

loadxml.o: loadxml.cpp
	g++ $(FLAGS) -c $<

clean:
	rm -rf *.o




