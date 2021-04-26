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

Solution FirstGreedy::execute(Problem problem) {
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
        for (int k = 1; k <= problem.getNumberOfTasks(); k++) {
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
  solution.calculateObjectiveFunction();

  return solution;
}