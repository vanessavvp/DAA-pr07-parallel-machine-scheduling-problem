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

#include "./machine.h"
#include "./solution.h"
#include "./algorithm.h"

#pragma once

class Algorithm;
class Problem {
  public:
    Problem(std::string& inputFileName);
    ~Problem();

    int getNumberOfTasks();
    int getNumberOfMachines();
    std::vector<Machine> getSolutionMachines();
    std::vector<int> getExecutionTimes();
    std::vector<std::vector<Task>> getTasksMatrix();
    Algorithm* getAlgorithm();
    Solution getSolution();

    void setTaskExecuted(int taskID);
    void addMachinesToSolution(int numberOfMachines);
    void execute();
    void setAlgorithm(Algorithm* algoritmo);

    int findFirstAvailableTask(int task);
    Task findTaskWithLessTotalTime(int task);

    void readFile(std::string& inputFileName);

    void updateObjectiveFunction();

  private:
    int numberOfTasks_;
    int numberOfMachines_;
    Algorithm* algorithm_;
    std::vector<Machine> solutionMachines_;
    Solution solution_;
    std::vector<int> executionTimes_;
    std::vector<std::vector<Task>> tasksMatrix_;
};

#endif // !PROBLEM_H