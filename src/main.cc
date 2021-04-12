/**
 * PROJECT HEADER
 * @input main.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/parallelMachine.h"
#include "../include/machine.h"
#include "../include/task.h"

int main(int argc, char* argv[]) {
  std::string fileName = argv[1];
  ParallelMachine parallelMachine(fileName);
  parallelMachine.readFile(fileName);
  //parallelMachine.executeMachines();
}