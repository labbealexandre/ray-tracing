CXXFLAGS=-Wall -std=c++11 -fopenmp
CXX= g++
SRCDIR= src
BUILDDIR= build
AIM= main
TARGET = bin/$(AIM)
TARGETCPP = test/$(AIM).cpp
SRCEXT = cpp
BINDIR=bin
SOURCES= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
EXEC = rayTracing

all: main

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(shell mkdir -p $(BUILDDIR))
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) $(TARGETCPP)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

main: $(OBJECTS) test/main.cpp tinyxml2/tinyxml2.cpp
	$(shell mkdir -p $(BINDIR))
	$(CXX) $(CXXFLAGS) $^ -o $(BINDIR)/$@

clean:
	rm -rf $(BUILDDIR) $(TARGET) bin/*
	rm -rf docs