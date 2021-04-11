OBJECTS = main.o parallelMachine.o machine.o task.o
CFLAGS = -c -O3 -std=c++17 -I../include

exe: $(OBJECTS)
	g++  $(OBJECTS) -o exe
	mv *.o ./obj
	
main.o:
	g++ $(CFLAGS) ./src/main.cc

parallelMachine.o:
	g++ $(CFLAGS) ./src/parallelMachine.cc

machine.o:
	g++ $(CFLAGS) ./src/machine.cc

task.o:
	g++ $(CFLAGS) ./src/task.cc

.PHONY: 

default:
	make exe

clean:
	rm -rf ./obj/*.o