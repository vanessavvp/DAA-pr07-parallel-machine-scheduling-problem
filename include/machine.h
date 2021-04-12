/**
 * PROJECT HEADER
 * @file machine.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <vector>

#include "./task.h"

class Machine {
 public:
  Machine(int machineID);
  ~Machine();

  std::vector<Task> getTasks();
  int getComputingTime();

 private:
  std::vector<Task> tasks_;
  int tct_;
  int machineID_;
};

#endif // !MACHINE_H