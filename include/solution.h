/**
 * PROJECT HEADER
 * @file solution.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>

#include "./machine.h"

#pragma once

class Solution {
  public:
    Solution();
    Solution(int numberOfMachines);
    ~Solution();

    int getSize();
    std::vector<Machine> getSolution();
    Machine findMachineWithLeaserTCT();

    int evaluateObjectiveFunction(Task task, int machine, int position);
    void printSolution();

    Machine& operator[](int machineIndex);
    
  private:
    std::vector<Machine> solution_;
    int totalTCT_ = 0;

};

#endif // !SOLUTION_H
