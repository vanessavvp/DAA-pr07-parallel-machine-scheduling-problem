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

#pragma once

class Machine {
 public:
  Machine();
  Machine(int machineID);
  ~Machine();

  int getTCT();
  int getMachineID();
  int getMachineSize();
  int getLastTaskAddedID();
  std::vector<Task> getTasks() const;

  void setTCT(int newTCT);
  void setTask(Task newTask);
  void printTasks();
  void calculateTCT();
  void setMachineID(int newID);
  void setTaskPosition(Task newTask, int position);
  
  void insertTask(int taskIndex, Task task);
  void deleteTask(int taskIndex);
  Task& operator[](int taskIndex);
  bool operator==(const Machine& machine) const;

 private:
  std::vector<Task> tasks_;
  int tct_;
  int machineID_;
};

#endif // !MACHINE_H