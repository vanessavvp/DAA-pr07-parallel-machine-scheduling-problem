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

#include "../include/problem.h"
#include "../include/machine.h"
#include "../include/task.h"

int main(int argc, char* argv[]) {
  std::string fileName = argv[1];
  Problem machineA(fileName);
  machineA.originalGreedyAlgorithm();

  Problem machineB(fileName);
  machineB.greedyAlgorithm();
}