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
  Machine();
  Machine(int machineID);
  ~Machine();

  std::vector<Task> getTasks();
  int getTCT();
  int getMachineID();

  void setTask(Task newTask);
  void setTaskPosition(Task newTask, int position);
  void setTCT(int newTCT);
  void setMachineID(int newID);
  void calculateTCT();
  
  int getLastTaskAddedID();

 private:
  std::vector<Task> tasks_;
  int tct_;
  int machineID_;
};

#endif // !MACHINE_H