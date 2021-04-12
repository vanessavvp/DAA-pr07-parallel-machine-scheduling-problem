/**
 * PROJECT HEADER
 * @file parallelMachine.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/parallelMachine.h"

ParallelMachine::ParallelMachine(std::string& inputFileName) {
  //readFile(inputFileName);
}


ParallelMachine::~ParallelMachine() {}


std::vector<Machine> ParallelMachine::getSolution() {
  return solution_;
}


std::vector<int> ParallelMachine::getExecutionTimes() {
  return executionTimes_;
}


std::vector<std::vector<Task>> ParallelMachine::getTasksMatrix() {
  return tasksMatrix_;
}


void ParallelMachine::findSmallestTime() {

}


std::vector<Machine> ParallelMachine::greedyConstructiveAlgorithm() {
  std::vector<Machine> resultado;
  std::cout << "Hola\n";

  // Find the smallests values
  

  return resultado;
}


void ParallelMachine::executeMachines() {
  // First greedy algorithm
  this->greedyConstructiveAlgorithm();

  // Second greedy algorithm
}


void ParallelMachine::addMachinesToSolution(int numberOfMachines) {
  for (int i = 0; i < numberOfMachines; i++) {
    Machine newMachine(i);
    solution_.push_back(newMachine);
  }
}


void ParallelMachine::readFile(std::string& inputFileName) {
  std::ifstream file(inputFileName);
  std::string data;
  int numberOfTasks;
  int numberOfMachines;

  if (!file.good()) {
    std::cerr << "\nERROR: Opening file error\n"; 
  }

  // Number of tasks
  getline(file, data);
  std::istringstream tasks(data);
  while (tasks >> data);
  numberOfTasks = std::stoi(data);
  getTasksMatrix().resize((numberOfTasks + 1), std::vector<Task>(numberOfTasks + 1));

  // Number of machines
  getline(file, data);
  std::istringstream machines(data);
  while (machines >> data);
  numberOfMachines = std::stoi(data);
  addMachinesToSolution(numberOfMachines);
  //getSolution().resize(numberOfMachines);

  // Execution times
  getline(file, data);
  std::istringstream executionTime(data);
  int count = 0;
  while (executionTime >> data) {
    if (count == 0) {
     executionTimes_.push_back(0);
      count ++;
  
    } else {
     executionTimes_.push_back(std::stoi(data));
    }
  }
  getline(file, data);

  // Creating tasks vector with the setups time matrix
  std::vector<std::vector<int>> setupMatrix;
  setupMatrix.resize(numberOfTasks + 1);
  for (int i = 0; i <= numberOfTasks; i++) {
    getline(file, data);
    std::istringstream setupTime(data);
    while (setupTime >> data) {
      setupMatrix[i].push_back(std::stoi(data));
    }
  }
  tasksMatrix_.resize(setupMatrix.size());
  for (int i = 0; i < setupMatrix.size(); i++) {
    for (int j = 0; j < setupMatrix.size(); j++) {
      Task newTask(i, executionTimes_[j]);
      tasksMatrix_[i].push_back(newTask);
    }
  }
  
  // Verifying correct values
  std::cout << "\nNumber of tasks: " << numberOfTasks;
  std::cout << "\nNumber of machines: " << numberOfMachines;
  std::cout << "\nExecution times: ";
  for (int i = 0; i < executionTimes_.size(); i++) {
    std::cout << executionTimes_[i] << " ";
  }
  std::cout << "\nSetups times: \n";
  for (int i = 0; i < setupMatrix.size(); i++) {
    for (int j = 0; j < setupMatrix.size(); j++) {
      std::cout << setupMatrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  
  std::cout << "\nExecution times from tasks matrix: \n";
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      std::cout << tasksMatrix_[i][j].getExecutionTime() << " ";
    }
    std::cout << "\n";
  }

  file.close();
}
