/**
 * PROJECT HEADER
 * @file solution.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/solution.h"

Solution::Solution() {
  totalTCT_ = 0;
}

Solution::Solution(int numberOfMachines) {
  totalTCT_ = 0;
  solution_.resize(numberOfMachines);
  for (int i = 0; i < solution_.size(); i++) {
    Machine newMachine(i);
    solution_[i] = newMachine;
  }
}

Solution::~Solution() {}

void Solution::printSolution() {
  for (int i = 0; i < getSize(); i++) {
    std::cout << "\n[ Machine: " << i << " ] ";
    for (int j = 0; j < solution_[i].getTasks().size(); j++) {
      std::cout << solution_[i].getTasks()[j].getTaskID()<< " ";
    }
    std::cout << "with TCT: " << solution_[i].getTCT();
  }
  std::cout << "\nZ -> Total completion time: " << totalTCT_ << std::endl;
}

int Solution::getTotalTCT() const {
  return totalTCT_;
}


void Solution::calculateObjectiveFunction() {
  totalTCT_ = 0;
  for (int i = 0; i < solution_.size(); i++) {
    for (int j = 0; j < solution_[i].getTasks().size(); j++) {
      totalTCT_ += (solution_[i][j].getTotalTime() * (solution_[i].getTasks().size() - j));
    }
  }
}

/**
 * Calculates the objetive function when adding a new task in a specific position
 * but without changing the original parcial tct
 **/
int Solution::evaluateObjectiveFunction(Task task, int machine, int position) {
  std::vector<Task> tasks = solution_[machine].getTasks();
  std::vector<Task>::iterator it = tasks.begin() + position;
  tasks.insert(it, task);

  int tct = 0;
  for (int i = 0; i < tasks.size(); i++) {
    tct += (tasks[i].getTotalTime() * (tasks.size() - i));
  }
  return tct;
}


Machine Solution::findMachineWithLeaserTCT() {
  int minTCT = solution_[0].getTCT();
  Machine leaserTCTMachine;

  for (int i = 0; i < solution_.size(); i++) {
    if (solution_[i].getTCT() <= minTCT) {
      minTCT = solution_[i].getTCT();
      leaserTCTMachine = solution_[i];
    }
  }
  
  return leaserTCTMachine;
}


Machine& Solution::operator[](int machineIndex) {
  if (machineIndex >= solution_.size()) {
    std::cout << "MACHINE INDEX " << machineIndex << " SOLUTION.SIZE " << solution_.size();
    std::cerr << "\nSolution ERROR: Required index greater than the number of tasks within the machine\n";
    exit(1);
  }
  return solution_[machineIndex];
}

      
int Solution::getSize() {
  return solution_.size();
}

std::vector<Machine> Solution::getSolution() const {
  return solution_;
}


bool Solution::operator ==(const Solution& solution) {
  if ((solution.getSolution() == solution_) && (solution.getTotalTCT() == totalTCT_)) {
    return true;
  }
  return false;
}


bool Solution::operator!=(const Solution& solution) {
  Solution solutionCopy = solution;
  return !(solutionCopy == *this);
}
