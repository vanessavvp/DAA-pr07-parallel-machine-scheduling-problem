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


int ParallelMachine::getNumberOfMachines() {
  return numberOfMachines_;
}



std::vector<int> ParallelMachine::getExecutionTimes() {
  return executionTimes_;
}


std::vector<std::vector<Task>> ParallelMachine::getTasksMatrix() {
  return tasksMatrix_;
}


int ParallelMachine::getNumberOfTasks() {
  return numberOfTasks_;
}


/**
 * Executes machines with the different Greedy algorithm implemented
 **/
void ParallelMachine::executeMachines() {
  // First greedy algorithm
  this->originalGreedyAlgorithm();

  // Second greedy algorithm proposal
  //this->greedyAlgorithm();
}


/**
 * Finds the task with less Total Time (Setup time + Execution time) that has not
 * been executed yet and returns it.
 **/
Task ParallelMachine::findTaskWithLessTotalTime(int task) {
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
int ParallelMachine::findFirstAvailableTask(int task) {
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
void ParallelMachine::setTaskExecuted(int taskID) {
  for (int i = 0; i < tasksMatrix_.size(); i++) {
    tasksMatrix_[i][taskID].setExecuted(true);
  }
}

/**
 * Calculates the objetive function when adding a new task in a specific position
 * but without changing the original parcial tct
 **/
int ParallelMachine::evaluateObjectiveFunction(Task task, int machine, int position) {
  std::vector<Task> tasks = solutionMachines_[machine].getTasks();
  std::vector<Task>::iterator it = tasks.begin() + position + 1;
  tasks.insert(it, task);

  int tct = 0;
  for (int i = 0; i < tasks.size(); i++) {
    tct += (tasks[i].getTotalTime() * (tasks.size() - i));
  }
  return tct;
}


/**
 * Section A
 **/
std::vector<Machine> ParallelMachine::originalGreedyAlgorithm() {
  std::cout << "\n\ta) Trace for the greedy implementation";
  std::vector<Machine> resultado;
  int taskDone = 0;

  // First part - Finds the smallests values
  for (int i = 0; i < solutionMachines_.size(); i++) {
    Task firstTask = findTaskWithLessTotalTime(0);
    int firstTaskIndex = firstTask.getTaskID();
    solutionMachines_[i].setTask(tasksMatrix_[0][firstTaskIndex]);
    this->setTaskExecuted(firstTaskIndex);
    solutionMachines_[i].setTCT(firstTask.getTotalTime());
    taskDone++;

    std::cout << "\nNew task: " << tasksMatrix_[0][firstTaskIndex].getTaskID() << 
     " -> TT: " <<  tasksMatrix_[0][firstTaskIndex].getTotalTime() << " -> ";
    std::cout << "New TCT: " << solutionMachines_[i].getTCT();
  }

  this->setTaskExecuted(0);
  // Second part 
  while (taskDone < numberOfTasks_) {
    int lessIncrement = INT16_MAX;
    int increment = INT16_MAX;
    int bestTaskPosition = 0;
    int possibleTCT = 0;
    int bestMachine = 0;
    std::vector<Task> tasksCopy;
    Task bestTask;

    for (int i = 0; i < solutionMachines_.size(); i++) {
      //tasksCopy = solutionMachines_[i].getTasks();
      for (int j = 0; j < solutionMachines_[i].getTasks().size(); j++){
        //for (Task task : tasksMatrix_[tasksCopy[j].getTaskID()]) {
        int actualTask = solutionMachines_[i].getTasks()[j].getTaskID();
        for (int k = 1; k < numberOfTasks_; k++) {
          Task task = tasksMatrix_[actualTask][k];
          if (task.isExecuted() == false) {
            possibleTCT = evaluateObjectiveFunction(task, i, j);
            increment = possibleTCT - solutionMachines_[i].getTCT();
            std::cout << "\nMaq: " << solutionMachines_[i].getMachineID() << " Tarea: " << task.getTaskID() << " Posible TCT: " << possibleTCT << " Incremento actual: " << increment << " Menor incremento: " << lessIncrement;
            if (increment < lessIncrement) {
              bestMachine = solutionMachines_[i].getMachineID();
              lessIncrement = increment;
              bestTaskPosition = j + 1;
              bestTask = task;
            }
          }
        }
      }
    }
    std::cout << "\nTAREA: " << bestTask.getTaskID() << " En máquina: " << bestMachine + 1;

    setTaskExecuted(bestTask.getTaskID());
    solutionMachines_[bestMachine].setTaskPosition(bestTask, bestTaskPosition);
    solutionMachines_[bestMachine].calculateTCT();
    taskDone++;
  }

  std::cout << std::endl;
  int solution = 0;
  for (int i = 0; i < solutionMachines_.size(); i++) {
    std::cout << "\n[ Machine: " << (solutionMachines_[i].getMachineID() + 1) << " ]" ;
    int tasksSizes = solutionMachines_[i].getTasks().size();
    for (int j = 0; j < tasksSizes; j++) {
      std::cout << " " << solutionMachines_[i].getTasks()[j].getTaskID();
    }
    std::cout << " with TCT: " << solutionMachines_[i].getTCT();
    solution += solutionMachines_[i].getTCT();
  }
  std::cout << "\n\nZ -> Total completion time using the greedy algorithm (a): " << solution << std::endl;

  return resultado;
}


/** 
 * Section B - Proposal of the greedy algorithm. Additions every tasks with
 *              the best completion time at the end of the selected machine 
 *              until restoring all the tasks needed on each existing machine
 *              and, finally, calculates the TCT.
 **/
std::vector<Machine> ParallelMachine::greedyAlgorithm() {
  std::cout << "\n\n\tb) Trace for the greedy implementation";
  std::vector<Machine> resultado;
  int taskDone = 0;

  // First part - Finds the smallests values
  for (int i = 0; i < solutionMachines_.size(); i++) {
    Task firstTask = findTaskWithLessTotalTime(0);
    int firstTaskIndex = firstTask.getTaskID();
    solutionMachines_[i].setTask(tasksMatrix_[0][firstTaskIndex]);
    this->setTaskExecuted(firstTaskIndex);
    solutionMachines_[i].setTCT(firstTask.getTotalTime());
    taskDone++;

    std::cout << "\nNew task: " << tasksMatrix_[0][firstTaskIndex].getTaskID() << 
     " -> TT: " <<  tasksMatrix_[0][firstTaskIndex].getTotalTime() << " -> ";
    std::cout << "New TCT: " << solutionMachines_[i].getTCT();
  }
  
  // Second part 
  while (taskDone < numberOfTasks_) {
    Machine actualMachine = findMachineWithLeaserTCT();
    int machineID = actualMachine.getMachineID();   
    int lastTask = actualMachine.getLastTaskAddedID();  // Revisar fila  
    Task task = findTaskWithLessTotalTime(lastTask);
    int taskIndex = task.getTaskID();

    int temporalTCT = 0;
    solutionMachines_[machineID].setTask(tasksMatrix_[lastTask][taskIndex]);
    this->setTaskExecuted(taskIndex);
    for (int i = 0; i < solutionMachines_[machineID].getTasks().size(); i++) {
      temporalTCT += ((solutionMachines_[machineID].getTasks()[i].getTotalTime()) * (solutionMachines_[machineID].getTasks().size() - i));
      solutionMachines_[machineID].setTCT(temporalTCT);
    }

    std::cout << "\nNew task: " << tasksMatrix_[lastTask][taskIndex].getTaskID() << 
     "-> TT: " <<  tasksMatrix_[lastTask][taskIndex].getTotalTime() << " + ";
    std::cout << "Actual TCT: " << actualMachine.getTCT();
    std::cout << " -> New TCT: " << solutionMachines_[machineID].getTCT();
   
    taskDone++;
  }

  std::cout << std::endl;
  int solution = 0;
  for (int i = 0; i < solutionMachines_.size(); i++) {
    std::cout << "\n[ Machine: " << (solutionMachines_[i].getMachineID() + 1) << " ]" ;
    int tasksSizes = solutionMachines_[i].getTasks().size();
    for (int j = 0; j < tasksSizes; j++) {
      std::cout << " " << solutionMachines_[i].getTasks()[j].getTaskID();
    }
    std::cout << " with TCT: " << solutionMachines_[i].getTCT();
    solution += solutionMachines_[i].getTCT();
  }
  std::cout << "\n\nZ -> Total completion time using the greedy algorithm (b): " << solution << std::endl;
  
  return resultado;
}


/** 
 * Finds and returns the machine with the leaser TCT value 
 **/
Machine ParallelMachine::findMachineWithLeaserTCT() {
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


/**
 * Creates a number new machines from a given number of machines and adds
 * it to the solution, which contains the different machines with its own 
 * tasks.
 **/
void ParallelMachine::addMachinesToSolution(int numberOfMachines) {
  for (int i = 0; i < numberOfMachines; i++) {
    Machine newMachine(i);
    solutionMachines_.push_back(newMachine);
  }
}


/**
 * Reads the input file and stores everything into its data structures
 **/
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
