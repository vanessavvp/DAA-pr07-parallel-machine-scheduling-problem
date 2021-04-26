/**
 * PROJECT HEADER
 * @file problem.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "./machine.h"
#include "./solution.h"
#include "./algorithm.h"

class Problem {
  public:
    Problem(std::string& inputFileName);
    ~Problem();

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

    int evaluateObjectiveFunction(Task task, int machine, int position);
    void updateObjectiveFunction();
    std::vector<Machine> originalGreedyAlgorithm();
    std::vector<Machine> greedyAlgorithm();
    std::vector<Machine> GRASP();
    void executeMachines();

  private:
    int numberOfTasks_;
    int numberOfMachines_;
    //Algorithm* algorithm_;
    std::vector<Machine> solutionMachines_;
    //Solution solutionMachines_;
    std::vector<int> executionTimes_;
    std::vector<std::vector<Task>> tasksMatrix_;
};

#endif // !PROBLEM_H