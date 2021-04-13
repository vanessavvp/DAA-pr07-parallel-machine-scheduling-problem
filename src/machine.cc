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

std::vector<Task> Machine::getTasks() {
  return tasks_;
}

int Machine::getLastTaskAddedID() {
  return tasks_[tasks_.size() - 1].getTaskID();
}