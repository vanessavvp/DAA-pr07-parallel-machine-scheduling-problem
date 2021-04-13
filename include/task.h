/**
 * PROJECT HEADER
 * @file task.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>

class Task {
 public:
  Task();
  Task(int taskID, int executionTime, int setupTime);
  ~Task();

  int getTaskID();
  int getSetupTime();
  int getExecutionTime();
  int getTotalTime();
  void setExecuted(bool executed);
  bool isExecuted();

 private:
  int taskID_;
  int executionTime_;
  int setupTime_;
  bool executed_;
};

#endif // !TASK_H