/**
 * PROJECT HEADER
 * @file problem.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/problem.h"

Problem::Problem(std::string& inputFileName) {
  readFile(inputFileName);
}


Problem::~Problem() {}


std::vector<Machine> Problem::getSolutionMachines() {
  return solutionMachines_;
}


int Problem::getNumberOfMachines() {
  return numberOfMachines_;
}



std::vector<int> Problem::getExecutionTimes() {
  return executionTimes_;
}


std::vector<std::vector<Task>> Problem::getTasksMatrix() {
  return tasksMatrix_;
}


int Problem::getNumberOfTasks() {
  return numberOfTasks_;
}

Solution Problem::getSolution() {
  return solution_;
}

void Problem::setAlgorithm(Algorithm* algorithm) {
  algorithm_ = algorithm;
}


void Problem::execute() {
  solution_ = algorithm_->execute(*this);
}


void Problem::printSetupMatrix() {
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_[i].size(); j++) {
      std::cout << std::setw(4) << tasksMatrix_[i][j].getSetupTime() << " ";
    }
    std::cout << "\n";
  }
}


void Problem::printGeneratedSolution() {
  solution_.printSolution();
}



/**
 * Finds the task with less Total Time (Setup time + Execution time) that has not
 * been executed yet and returns it.
 **/
Task Problem::findTaskWithLessTotalTime(int task) {
  int minTime = findFirstAvailableTask(task);
  Task minTask;

  for (int i = 1; i < tasksMatrix_.size(); i++) {
    Task actualTask = tasksMatrix_[task][i];
    if ((actualTask.isExecuted() == false) && (actualTask.getTaskID() != task) &&
       (actualTask.getSetupTime() != 0) && (actualTask.getTotalTime() != 0) &&
       (actualTask.getTotalTime() <= minTime)){ 
        minTime = actualTask.getTotalTime();
        minTask = actualTask;
    }
  }
  return minTask;
}


/**
 * Finds the first task that is not been executed yet and returns it, for it to be 
 * added as the first task of a machine.
 **/
int Problem::findFirstAvailableTask(int task) {
  for (int i = 1; i < tasksMatrix_.size(); i++) {
    Task actualTask = tasksMatrix_[task][i];
    if (actualTask.isExecuted() == false) {
      return actualTask.getTotalTime();
    }
  }
  return 0;
}


/**
 * Sets an entire column in the task matrix from a given task ID that, the task 
 * has been executed.
 **/
void Problem::setTaskExecuted(int taskID) {
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    tasksMatrix_[i][taskID].setExecuted(true);
  }
}


/**
 * Creates a number new machines from a given number of machines and adds
 * it to the solution, which contains the different machines with its own 
 * tasks.
 **/
void Problem::addMachinesToSolution(int numberOfMachines) {
  for (int i = 0; i < numberOfMachines; i++) {
    Machine newMachine(i);
    solution_.getSolution().push_back(newMachine);
  }
}


/**
 * Reads the input file and stores everything into its data structures
 **/
void Problem::readFile(std::string& inputFileName) {
  std::ifstream file(inputFileName);
  std::string data;

  if (!file.good()) {
    std::cerr << "\nERROR: Opening file error\n"; 
  }

  // Number of tasks
  getline(file, data);
  std::istringstream tasks(data);
  while (tasks >> data);
  numberOfTasks_ = std::stoi(data);
  getTasksMatrix().resize((numberOfTasks_ + 1), std::vector<Task>(numberOfTasks_ + 1));

  // Number of machines
  getline(file, data);
  std::istringstream machines(data);
  while (machines >> data);
  numberOfMachines_ = std::stoi(data);
  addMachinesToSolution(numberOfMachines_);

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
  setupMatrix.resize(numberOfTasks_ + 1);
  for (int i = 0; i <= numberOfTasks_; i++) {
    getline(file, data);
    std::istringstream setupTime(data);
    while (setupTime >> data) {
      setupMatrix[i].push_back(std::stoi(data));
    }
  }
  tasksMatrix_.resize(setupMatrix.size());
  for (int i = 0; i < setupMatrix.size(); i++) {
    for (int j = 0; j < setupMatrix.size(); j++) {
      Task newTask(j, executionTimes_[j], setupMatrix[i][j]);
      tasksMatrix_[i].push_back(newTask);
    }
  }
  
  // Verifying correct values
  /*std::cout << "\nNumber of tasks: " << (tasksMatrix_.size() - 1);
  std::cout << "\nNumber of machines: " << solutionMachines_.size();
  std::cout << "\nExecution times: ";
  for (int i = 0; i < executionTimes_.size(); i++) {
    std::cout << executionTimes_[i] << " ";
  }*/
 /* std::cout << "\nSetups times: \n";
  for (int i = 0; i < setupMatrix.size(); i++) {
    for (int j = 0; j < setupMatrix.size(); j++) {
      std::cout << setupMatrix[i][j] << " ";
    }
    std::cout << "\n";
  }*/
  
  /*std::cout << "\nExecution times from tasks matrix: \n";
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      std::cout << tasksMatrix_[i][j].getExecutionTime() << " ";
    }
    std::cout << "\n";
  }*/
/*
  std::cout << "\nSetup times: \n";
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      std::cout << tasksMatrix_[i][j].getSetupTime() << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\nTask ID: \n";
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      std::cout << tasksMatrix_[i][j].getTaskID() << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\nExecution time: \n";
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      std::cout << tasksMatrix_[i][j].getExecutionTime() << " ";
    }
    std::cout << "\n";
  }*/


  file.close();
}
