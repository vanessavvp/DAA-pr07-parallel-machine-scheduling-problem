/**
 * PROJECT HEADER
 * @input GRASP.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/GRASP.h"

void GRASP::setK() {
  std::cout << "\nIntroduce the k value: ";
  std::cin >> k_;
}

void GRASP::setK(int k) {
  k_ = k;
}

bool operator<(const resultValues& a, const resultValues& b) {
  return (std::get<0>(a) < std::get<0>(b));
}


std::vector<resultValues> GRASP::bestKValues(std::vector<resultValues>& totalResults) {
  std::vector<resultValues> organizedValues;
  std::vector<resultValues> bestValues;
  resultValues minimum;

  int min = 0;
  while (organizedValues.size() < k_) {
    for (int i = 0; i < totalResults.size(); i++) {
      if (std::get<0>(totalResults[i]) > min) {
        min = std::get<0>(totalResults[i]);
        minimum = totalResults[i];
      }
    }
    organizedValues.push_back(minimum);
  }
  
  std::cout << std::endl;
  return organizedValues;
}

Solution GRASP::execute(Problem& problem) {
  std::cout << "\n\tc) Constructive GRASP";
  Solution solution(problem.getNumberOfMachines());
  int taskDone = 0;

  // First part - Finds the smallests values
  for (int i = 0; i < solution.getSize(); i++) {
    Task firstTask = problem.findTaskWithLessTotalTime(0);
    int firstTaskIndex = firstTask.getTaskID();
    solution[i].setTask(problem.getTasksMatrix()[0][firstTaskIndex]);
    problem.setTaskExecuted(firstTaskIndex); 
    solution[i].setTCT(firstTask.getTotalTime());
    taskDone++;
    
    std::cout << "\nNew task: " << problem.getTasksMatrix()[0][firstTaskIndex].getTaskID() << 
     " -> TT: " <<  problem.getTasksMatrix()[0][firstTaskIndex].getTotalTime() << " -> ";
    std::cout << "New TCT: " << solution[i].getTCT();
  }

  problem.setTaskExecuted(0);

  // Second part 
  while (taskDone < problem.getNumberOfTasks()) {
    int lessIncrement = INT16_MAX;
    int increment = INT16_MAX;
    int bestTaskPosition = 0;
    int bestMachine = 0;
    Task bestTask;
    int possibleTCT = 0;
    std::vector<Task> tasksCopy;
    std::vector<resultValues> results;

    for (int i = 0; i < solution.getSize(); i++) {
      for (int j = 0; j < solution[i].getTasks().size(); j++){
        int actualTask = solution[i].getTasks()[j].getTaskID();
        for (int k = 1; k <= problem.getNumberOfTasks(); k++) {
          Task task = problem.getTasksMatrix()[actualTask][k];
          if (task.isExecuted() == false) {
            possibleTCT = solution.evaluateObjectiveFunction(task, i, j);
            increment = possibleTCT - solution[i].getTCT();
            if (increment < lessIncrement) {
              lessIncrement = increment;
              bestMachine = solution[i].getMachineID();
              bestTaskPosition = j + 1;
              bestTask = task;
              results.push_back(std::make_tuple(lessIncrement, bestMachine, bestTaskPosition, bestTask));
            }
          }
        }
      }
    }
    std::sort(results.begin(), results.end());
    std::vector<resultValues> bestKValues;
    int i = 0;
    while (bestKValues.size() < k_) {
      bestKValues.push_back(results[i]);
      i++;
    }
    
    int random = std::rand() % bestKValues.size();  // Cuando se tenga el vector de 3 solamente, que se coja aleatoriamente una posicion
    problem.setTaskExecuted(std::get<3>(bestKValues[random]).getTaskID());
    solution[std::get<1>(bestKValues[random])].setTaskPosition(std::get<3>(bestKValues[random]), std::get<2>(bestKValues[random]));
    solution[std::get<1>(bestKValues[random])].calculateTCT();
    
    taskDone++;
  }

  std::cout << std::endl;
  int solutionTCT = 0;
  for (int i = 0; i < solution.getSize(); i++) {
    std::cout << "\n[ Machine: " << solution[i].getMachineID() << " ]" ;
    int tasksSizes = solution[i].getTasks().size();
    for (int j = 0; j < tasksSizes; j++) {
      std::cout << " " << solution[i].getTasks()[j].getTaskID();
    }
    std::cout << " with TCT: " << solution[i].getTCT();
    solutionTCT += solution[i].getTCT();
  }
  std::cout << "\n\nZ -> Total completion time using the greedy algorithm (a): " << solutionTCT << std::endl;

  return solution;
}


