/**
 * PROJECT HEADER
 * @file task.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/task.h"


Task::Task() {}


Task::Task(int taskID, int executionTime) {
  taskID_ = taskID;
  executionTime_ = executionTime;
}


Task::~Task() {}


int Task::getTaskID() {
  return taskID_;
}


int Task::getExecutionTime() {
  return executionTime_;
}


bool Task::isExecuted() {
  return executed_;
}
