/**
 * PROJECT HEADER
 * @file GRASP.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef GRASP_H
#define GRASP_H

#include <iostream>
#include <utility>
#include <tuple>
#include <algorithm>

#include "./algorithm.h"
#include "./problem.h"

#pragma once


typedef std::tuple<int, int, int, Task> resultValues;
class GRASP : public Algorithm {
  public:
    GRASP() {}
    ~GRASP() {}

    void setK();
    void setK(int k);
    std::vector<resultValues> bestKValues(std::vector<resultValues>& totalResults);
    bool sortByFirst(const resultValues& a, const resultValues& b);
    Solution execute(Problem& problem);
    friend bool operator<(const resultValues& a, const resultValues& b);

  private:
    int k_;
};

#endif // !GRASP_H

