/**
 * PROJECT HEADER
 * @file localSearch.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/localSearch.h"

Solution LocalSearch::execute(Solution& generatedSolution, bool isAnxious) {
  Solution actualSolution;
  Solution bestSolution = actualSolution;
  do {
    actualSolution = bestSolution;
    std::vector<Solution> neighbours = generateNeighbours(actualSolution);
    for (int i = 0; i < neighbours.size(); i++) {
      if (neighbours[i].getTotalTCT() < bestSolution.getTotalTCT()) {
        bestSolution = neighbours[i];
        if (isAnxious) {
          return bestSolution;
        }
      }
    }

  } while (bestSolution != actualSolution);
  return bestSolution;
}
