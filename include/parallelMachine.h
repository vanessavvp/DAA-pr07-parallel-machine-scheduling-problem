/**
 * PROJECT HEADER
 * @file parallelMachine.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef PARALLEL_MACHINE_H
#define PARALLEL_MACHINE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "./machine.h"
#include "./task.h"

class ParallelMachine {
 public:
  ParallelMachine(std::string& inputFileName);
  ~ParallelMachine();

  std::vector<int> getExecutionTimes();
  std::vector<Machine> getSolutionMachines();
  std::vector<std::vector<Task>> getTasksMatrix();
  int getNumberOfTasks();
  void pushTask(Task newTask);
  void addMachinesToSolution(int numberOfMachines);
  Task findTaskWithLessTotalTime(int task);
  int firstAvailableTask(int task);
  void readFile(std::string& inputFileName);
  void executeMachines();
  Machine getMachineIDWithLeaserTCT();
  std::vector<Machine> greedyConstructiveAlgorithm();
  void setTaskExecuted(int taskID);

 private:
  std::vector<Machine> solutionMachines_;
  std::vector<int> executionTimes_;
  std::vector<std::vector<Task>> tasksMatrix_;
  int numberOfTasks_;
  int numberOfMachines_;
};

#endif // !PARALLEL_MACHINE_H