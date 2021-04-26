/**
 * PROJECT HEADER
 * @input intraChange.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef INTRA_CHANGE_H
#define INTRA_CHANGE_H

#include "./solution.h"
#include "./localSearch.h"

#pragma once

class IntraChange : public LocalSearch {
  public:
    IntraChange() {}
    ~IntraChange() {}
    std::vector<Solution> generateNeighbours(Solution previousSolution);
};

#endif // !INTRA_CHANGE_H