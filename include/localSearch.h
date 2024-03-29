/**
 * PROJECT HEADER
 * @file localSearch.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <chrono>

#include "./solution.h"

#pragma once

class LocalSearch {
  public:
    ~LocalSearch() = default;
    Solution execute(Solution& generatedSolution, bool isAnxious);
    virtual std::vector<Solution> generateNeighbours(Solution generatedSolution) = 0;
};

#endif // !LOCAL_SEARCH_H