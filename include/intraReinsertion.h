/**
 * PROJECT HEADER
 * @input intraReinsertion.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef INTRA_REINSERTION_H
#define INTRA_REINSERTION_H

#include "./solution.h"
#include "./localSearch.h"

#pragma once

class IntraReinsertion : public LocalSearch {
  public:
    IntraReinsertion() {}
    ~IntraReinsertion() {}
    std::vector<Solution> generateNeighbours(Solution generatedSolution);
};

#endif // !INTRA_REINSERTION_H