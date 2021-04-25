OBJECTS = main.o problem.o machine.o task.o firstGreedy.o solution.o secondGreedy.o GRASP.o
CFLAGS = -c -O3 -std=c++17 -I../include
SRC = src/main.cc src/problem.cc src/machine.cc src/task.cc src/firstGreedy.cc src/solution.cc src/secondGreedy.cc src/GRASP.cc

exe: $(OBJECTS)
	g++ $(SRC) -o exe
	mv *.o ./obj
	
main.o:
	g++ $(CFLAGS) ./src/main.cc

problem.o:
	g++ $(CFLAGS) ./src/problem.cc

machine.o:
	g++ $(CFLAGS) ./src/machine.cc

task.o:
	g++ $(CFLAGS) ./src/task.cc

firstGreedy.o:
	g++ $(CFLAGS) ./src/firstGreedy.cc

secondGreedy.o:
	g++ $(CFLAGS) ./src/secondGreedy.cc

solution.o:
	g++ $(CFLAGS) ./src/solution.cc

GRASP.o:
	g++ $(CFLAGS) ./src/GRASP.cc


.PHONY: 

default:
	make exe

clean:
	rm -rf ./obj/*.o

run:
	./exe input/I40j_2m_S1_1.txt