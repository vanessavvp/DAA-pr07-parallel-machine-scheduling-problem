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
#include "../include/firstGreedy.h"
#include "../include/secondGreedy.h"
#include "../include/GRASP.h"
#include <chrono>

int main(int argc, char* argv[]) {
  std::string fileName = argv[1];
  Problem machineA(fileName);
  Problem machineB(fileName);
  Problem machineC(fileName);

  FirstGreedy* firstGreedy = new FirstGreedy;
  SecondGreedy* secondGreedy = new SecondGreedy;
  GRASP* grasp = new GRASP;
  grasp->setK(2);

  machineA.setAlgorithm(firstGreedy);
  machineA.execute();
  machineB.setAlgorithm(secondGreedy);
  machineB.execute();
  machineC.setAlgorithm(grasp);
  srand(time(NULL));
  machineC.execute();
}