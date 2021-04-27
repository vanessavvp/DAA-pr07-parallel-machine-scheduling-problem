/**
 * PROJECT HEADER
 * @input interReinsertion.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 25/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/interReinsertion.h"

std::vector<Solution> InterReinsertion::generateNeighbours(Solution previousSolution) {
  std::vector<Solution> result;
  Solution actualSolution;
  for (int i = 0; i < previousSolution.getSize(); i++) {
    for (int j = 0; j < previousSolution.getSize(); j++) {
      // Verifies if the machines are not the same ones
      if (i != j) {
        for (int k = 0; k < previousSolution[i].getMachineSize(); k++) {
          for (int l = 0; l <= previousSolution[j].getMachineSize(); l++) {
            actualSolution = previousSolution;
            Task tempTask = actualSolution[i][k];
            // Deletes the tasks that will be inserted into the other machine
            actualSolution[i].deleteTask(k);
            actualSolution[j].insertTask(l - 1, tempTask);
            actualSolution.calculateObjectiveFunction();
            result.push_back(actualSolution);
          }
        }
      }
    }
  }
  return result;
}
