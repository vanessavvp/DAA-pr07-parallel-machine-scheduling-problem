/**
 * PROJECT HEADER
 * @file machine.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/machine.h"


Machine::Machine() {
  tct_ = 0;
}


Machine::Machine(int machineID) {
  machineID_ = machineID;
  tct_ = 0;
}


Machine::~Machine() {}


void Machine::setTask(Task newTask) {
  tasks_.push_back(newTask);
}


void Machine::setTaskPosition(Task newTask, int position) {
  std::vector<Task>::iterator it = tasks_.begin() + position;
  tasks_.insert(it, newTask);
}


void Machine::setTCT(int newTCT) {
  tct_ = newTCT;
}


void Machine::setMachineID(int newID) {
  machineID_ = newID;
}


int Machine::getTCT() {
  return tct_;
}


int Machine::getMachineID() {
  return machineID_;
}


std::vector<Task> Machine::getTasks() const {
  return tasks_;
}


int Machine::getLastTaskAddedID() {
  return tasks_[tasks_.size() - 1].getTaskID();
}


void Machine::calculateTCT() {
  tct_ = 0;
  for (int i = 0; i < tasks_.size(); i++) {
    tct_ += (tasks_[i].getTotalTime() * (tasks_.size() - i));
  }
}


Task& Machine::operator[](int taskIndex) {
  if (taskIndex >= getMachineSize()) {
    std::cerr << "The required task index is greater than the size of the machine" << std::endl;
    exit(1);
  }
  return tasks_[taskIndex];
}


int Machine::getMachineSize() {
  return tasks_.size();
}


bool Machine::operator==(const Machine& machine) const {
  if(machine.getTasks() == tasks_) {
    return true;
  }
  return false;
}


/** 
 * Inserts a specific task whithin the machine by giving its position
 **/
void Machine::insertTask(int taskIndex, Task task) {
  std::vector<Task>::iterator it = tasks_.begin() + taskIndex + 1;
  tasks_.insert(it, task);
  calculateTCT();
}


/** 
 * Erases a specific task whithin the machine by giving its position
 **/
void Machine::deleteTask(int taskIndex) {
  std::vector<Task>::iterator it = tasks_.begin() + taskIndex;
  tasks_.erase(it);
  calculateTCT();
}


void Machine::printTasks() {
  for (int i = 0; i < tasks_.size(); i++) {
    std::cout << tasks_[i].getTaskID() << " ";
  }
}
