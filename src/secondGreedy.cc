/**
 * PROJECT HEADER
 * @input secondGreedy.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/secondGreedy.h"

Solution SecondGreedy::execute(Problem problem) {
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

  
  // Second part 
  while (taskDone < problem.getNumberOfTasks()) {
    Machine actualMachine = solution.findMachineWithLeaserTCT();
    int machineID = actualMachine.getMachineID();  
    int lastTask = actualMachine.getLastTaskAddedID();  // Revisar fila  
    Task task = problem.findTaskWithLessTotalTime(lastTask);
    int taskIndex = task.getTaskID();

    int temporalTCT = 0;
    solution[machineID].setTask(problem.getTasksMatrix()[lastTask][taskIndex]);
    problem.setTaskExecuted(taskIndex);
    for (int i = 0; i < solution[machineID].getTasks().size(); i++) {
      temporalTCT += ((solution[machineID].getTasks()[i].getTotalTime()) * (solution[machineID].getTasks().size() - i));
      solution[machineID].setTCT(temporalTCT);
    }

    taskDone++;
  }
  solution.calculateObjectiveFunction();
  
  return solution;
}
