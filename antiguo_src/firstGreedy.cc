/**
 * PROJECT HEADER
 * @input firstGreedy.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/firstGreedy.h"

Solution FirstGreedy::execute(Problem& problem) {
  std::cout << "\n\ta) Trace for the greedy implementation";
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
    int possibleTCT = 0;
    int bestMachine = 0;
    std::vector<Task> tasksCopy;
    Task bestTask;

    for (int i = 0; i < solution.getSize(); i++) {
      for (int j = 0; j < solution[i].getTasks().size(); j++){
        int actualTask = solution[i].getTasks()[j].getTaskID();
        for (int k = 1; k < problem.getNumberOfTasks(); k++) {
          Task task = problem.getTasksMatrix()[actualTask][k];
          if (task.isExecuted() == false) {
            possibleTCT = solution.evaluateObjectiveFunction(task, i, j);
            increment = possibleTCT - solution[i].getTCT();
            if (increment < lessIncrement) {
              bestMachine = solution[i].getMachineID();
              lessIncrement = increment;
              bestTaskPosition = j + 1;
              bestTask = task;
            }
          }
        }
      }
    }
    problem.setTaskExecuted(bestTask.getTaskID());
    solution[bestMachine].setTaskPosition(bestTask, bestTaskPosition);
    solution[bestMachine].calculateTCT();
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