CC=g++
EXE_FILE=tycoon
HEADERS=zoo.hpp animal.hpp monkey.hpp seaotter.hpp sloth.hpp robot.hpp
OBJS=zoo.o animal.o monkey.o seaotter.o sloth.o robot.o main.o
CXXFLAGS=-std=c++11 -g

all: $(EXE_FILE)

$(EXE_FILE): $(OBJS)
	$(CC) $^ -o $@ $(CXXFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CXXFLAGS)
	
clean: 
	rm -f $(OBJS) $(EXE_FILE)