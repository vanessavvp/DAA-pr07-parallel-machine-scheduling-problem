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


Task::Task() {
  executed_ = false;
}


Task::Task(int taskID, int executionTime, int setupTime) {
  taskID_ = taskID;
  executionTime_ = executionTime;
  setupTime_ = setupTime;
  executed_ = false;
}


Task::~Task() {}


int Task::getTaskID() const {
  return taskID_;
}


int Task::getExecutionTime() {
  return executionTime_;
}


int Task::getSetupTime() {
  return setupTime_;
}


int Task::getTotalTime() const {
  return (setupTime_ + executionTime_);
}


void Task::setExecuted(bool executed) {
  executed_ = executed;
}

bool Task::isExecuted() const {
  return executed_;
}


bool Task::operator==(const Task& task) const {
  if ((task.getTotalTime() == getTotalTime()) && (task.getTaskID() == taskID_) && (task.isExecuted() == executed_)) {
    return true;
  }
  return false;
}
