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
  readFile(inputFileName);
}


ParallelMachine::~ParallelMachine() {}


std::vector<Machine> ParallelMachine::getSolutionMachines() {
  return solutionMachines_;
}


std::vector<int> ParallelMachine::getExecutionTimes() {
  return executionTimes_;
}


std::vector<std::vector<Task>> ParallelMachine::getTasksMatrix() {
  return tasksMatrix_;
}


Task ParallelMachine::findTaskWithLessTotalTime(int task) {
  int minTime = firstAvailableTask(task);
  Task minTask;

  for (int i = 1; i < tasksMatrix_.size(); i++) {
    Task actualTask = tasksMatrix_[task][i];
    if ((actualTask.isExecuted() == false) && (actualTask.getTaskID() != 0) &&
       (actualTask.getSetupTime() != 0) && (actualTask.getTotalTime() != 0) &&
       (actualTask.getTotalTime() < minTime)){
        minTime = actualTask.getTotalTime();
        minTask = actualTask;
    }
  }
  return minTask;
}


int ParallelMachine::firstAvailableTask(int task) {
  for (int i = 1; i < tasksMatrix_.size(); i++) {
    Task actualTask = tasksMatrix_[task][i];
    if (actualTask.isExecuted() == false) {
      return actualTask.getTotalTime();
    }
  }
  return 0;
}


void ParallelMachine::setTaskExecuted(int taskID) {
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    for (int j = 0; j < tasksMatrix_.size(); j++) {
      if (taskID == i) {
        tasksMatrix_[i][j].setExecuted(true);
      }
    }
  }
}


// Apartado B
std::vector<Machine> ParallelMachine::greedyConstructiveAlgorithm() {
  std::vector<Machine> resultado;
  int taskDone = 0;

  // Find the smallests values
  for (int i = 0; i < solutionMachines_.size(); i++) {
    Task firstTask = findTaskWithLessTotalTime(0);
    int firstTaskIndex = firstTask.getTaskID();
    solutionMachines_[i].setTask(tasksMatrix_[0][firstTaskIndex]);
    tasksMatrix_[0][firstTaskIndex].setExecuted(true);
    taskDone++;
    solutionMachines_[i].setTCT(firstTask.getTotalTime());
    std::cout << " ID: " << tasksMatrix_[0][firstTaskIndex].getTaskID() << 
      " TT: " <<  tasksMatrix_[0][firstTaskIndex].getTotalTime() << "\n";
  }

  // Second part
  while (taskDone < numberOfTasks_) {
    Machine actualMachine = getMachineIDWithLeaserTCT();
    int machineID = actualMachine.getMachineID();   
    int lastTask = actualMachine.getLastTaskAddedID();  // Revisar fila  

    for (int i = 0; i < tasksMatrix_.size(); i++) {
      Task task = findTaskWithLessTotalTime(lastTask);
      int taskIndex = task.getTaskID();
      int temporalTCT = ((actualMachine.getTCT()) + (task.getTotalTime()));
      solutionMachines_[actualMachine.getMachineID()].setTask(tasksMatrix_[lastTask][taskIndex]);
      this->setTaskExecuted(taskIndex);
      //tasksMatrix_[actualMachine.getLastTaskAddedID()][taskIndex].setExecuted(true);
      solutionMachines_[actualMachine.getMachineID()].setTCT(temporalTCT);
      //std::cout << " Actual TCT: " << solutionMachines_[i].getTCT();
      //std::cout << " Temporal TCT: " << temporalTCT;
      //std::cout << " ID: " << tasksMatrix_[minTCTMachine][taskIndex].getTaskID() << 
      //  " TCT: " <<  tasksMatrix_[minTCTMachine][taskIndex].getTotalTime() << "\n";*/
      taskDone++;
    }
  }

  for (int i = 0; i < solutionMachines_.size(); i++) {
    std::cout << "\n[ Machine: " << (solutionMachines_[i].getMachineID() + 1) << " ]" ;
    int tasksSizes = solutionMachines_[i].getTasks().size();
    for (int j = 0; j < tasksSizes; j++) {
      std::cout << " " << solutionMachines_[i].getTasks()[j].getTaskID();
    }
    std::cout << " with TCT: " << solutionMachines_[i].getTCT();
  }
  std::cout << "\n";
  
  return resultado;
}


Machine ParallelMachine::getMachineIDWithLeaserTCT() {
  int minTCT = solutionMachines_[0].getTCT();
  Machine leaserTCTMachine;

  for (int i = 0; i < solutionMachines_.size(); i++) {
    if (solutionMachines_[i].getTCT() <= minTCT) {
      minTCT = solutionMachines_[i].getTCT();
      leaserTCTMachine = solutionMachines_[i];
    }
  }
  
  return leaserTCTMachine;
}


int ParallelMachine::getNumberOfTasks() {
  return numberOfTasks_;
}

void ParallelMachine::executeMachines() {
  // First greedy algorithm
  this->greedyConstructiveAlgorithm();

  // Second greedy algorithm
}


void ParallelMachine::addMachinesToSolution(int numberOfMachines) {
  for (int i = 0; i < numberOfMachines; i++) {
    Machine newMachine(i);
    solutionMachines_.push_back(newMachine);
  }
}


void ParallelMachine::readFile(std::string& inputFileName) {
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
