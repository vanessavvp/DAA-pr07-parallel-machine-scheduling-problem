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

Solution SecondGreedy::execute(Problem& problem) {
  std::cout << "\n\n\tb) Trace for the greedy implementation";
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

  std::cout << std::endl;
  int solutionTCT = 0;
  for (int i = 0; i < solution.getSize(); i++) {
    std::cout << "\n[ Machine: " << (solution[i].getMachineID()) << " ]" ;
    int tasksSizes = solution[i].getTasks().size();
    for (int j = 0; j < tasksSizes; j++) {
      std::cout << " " << solution[i].getTasks()[j].getTaskID();
    }
    std::cout << " with TCT: " << solution[i].getTCT();
    solutionTCT += solution[i].getTCT();
  }
  std::cout << "\n\nZ -> Total completion time using the greedy algorithm (b): " << solutionTCT << std::endl;
  
  return solution;
}
