OBJECTS = main.o problem.o machine.o task.o firstGreedy.o solution.o secondGreedy.o GRASP.o localSearch.o interChange.o interReinsertion.o intraChange.o intraReinsertion.o multiboot.o VNS.o VND.o
CFLAGS = -c -O3 -std=c++17 -I../include
SRC = src/main.cc src/problem.cc src/machine.cc src/task.cc src/firstGreedy.cc src/solution.cc src/secondGreedy.cc src/GRASP.cc src/localSearch.cc src/interChange.cc src/interReinsertion.cc src/intraChange.cc src/intraReinsertion.cc src/multiboot.cc src/VNS.cc src/VND.cc

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

localSearch.o:
	g++ $(CFLAGS) ./src/localSearch.cc

interChange.o:
	g++ $(CFLAGS) ./src/interChange.cc

interReinsertion.o:
	g++ $(CFLAGS) ./src/interReinsertion.cc

intraChange.o:
	g++ $(CFLAGS) ./src/intraChange.cc

intraReinsertion.o:
	g++ $(CFLAGS) ./src/intraReinsertion.cc

multiboot.o:
	g++ $(CFLAGS) ./src/multiboot.cc

VNS.o:
	g++ $(CFLAGS) ./src/VNS.cc

VND.o:
	g++ $(CFLAGS) ./src/VND.cc

.PHONY: 

default:
	make exe

clean:
	rm -rf ./obj/*.o

run:
	./exe input/I40j_8m_S1_1.txt