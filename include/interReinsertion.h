/**
 * PROJECT HEADER
 * @input interReinsertion.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef INTER_REINSERTION_H
#define INTER_REINSERTION_H

#include "./solution.h"
#include "./localSearch.h"

#pragma once

class InterReinsertion : public LocalSearch {
  public:
    InterReinsertion() {}
    ~InterReinsertion() {}
    std::vector<Solution> generateNeighbours(Solution generatedSolution);
};

#endif // !INTER_REINSERTION_H