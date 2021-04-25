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
  for (int i = 0; i < solution_.size(); i++) {
    std::cout << "Machine " << i << " : " << std::endl;
    for (int j = 0; j < solution_[i].getTasks().size(); j++) {
      std::cout << solution_[i].getTasks()[j].getTaskID()<< " ";
    }
  }
}

/**
 * Calculates the objetive function when adding a new task in a specific position
 * but without changing the original parcial tct
 **/
int Solution::evaluateObjectiveFunction(Task task, int machine, int position) {
  std::vector<Task> tasks = solution_[machine].getTasks();
  std::vector<Task>::iterator it = tasks.begin() + position + 1;
  tasks.insert(it, task);

  int tct = 0;
  for (int i = 0; i < tasks.size(); i++) {
    tct += (tasks[i].getTotalTime() * (tasks.size() - i));
  }
  return tct;
}


Machine& Solution::operator[](int machineIndex) {
  if (machineIndex >= solution_.size()) {
    std::cerr << "Required index greater than the number of tasks within the machine";
    exit(1);
  }
  return solution_[machineIndex];
}

int Solution::getSize() {
  return solution_.size();
}

std::vector<Machine> Solution::getSolution() {
  return solution_;
}
