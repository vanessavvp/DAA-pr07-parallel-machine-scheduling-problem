/**
 * PROJECT HEADER
 * @file parallelMachine.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef PARALLEL_MACHINE_H
#define PARALLEL_MACHINE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "./machine.h"
#include "./task.h"

class ParallelMachine {
  public:
    ParallelMachine(std::string& inputFileName);
    ~ParallelMachine();

    int getNumberOfTasks();
    int getNumberOfMachines();
    std::vector<Machine> getSolutionMachines();
    std::vector<int> getExecutionTimes();
    std::vector<std::vector<Task>> getTasksMatrix();

    void setTaskExecuted(int taskID);
    void addMachinesToSolution(int numberOfMachines);

    int findFirstAvailableTask(int task);
    Task findTaskWithLessTotalTime(int task);
    Machine findMachineWithLeaserTCT();

    void readFile(std::string& inputFileName);
    std::vector<Machine> greedyAlgorithm();
    void executeMachines();

  private:
    int numberOfTasks_;
    int numberOfMachines_;
    std::vector<Machine> solutionMachines_;
    std::vector<int> executionTimes_;
    std::vector<std::vector<Task>> tasksMatrix_;
};

#endif // !PARALLEL_MACHINE_H