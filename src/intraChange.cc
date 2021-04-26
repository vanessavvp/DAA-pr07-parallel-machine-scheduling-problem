/**
 * PROJECT HEADER
 * @input intraChange.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/intraChange.h"

std::vector<Solution> IntraChange::generateNeighbours(Solution previousSolution) {
  std::vector<Solution> result;
  Solution actualSolution;

  for (int i = 0; i < previousSolution.getSize(); i++) {
    for (int j = 0; j < previousSolution[i].getMachineSize(); j++) {
      for (int k = 0; k < previousSolution[i].getMachineSize(); k++) {
        if (j != k) {
          actualSolution = previousSolution;
          Task tempTask = actualSolution[i][j];
          actualSolution[i][j] = actualSolution[i][k];
          actualSolution[i][k] = tempTask;
          actualSolution.calculateObjectiveFunction();
          result.push_back(actualSolution);
        }
      }
    }
  }
  return result;
}
