/**
 * PROJECT HEADER
 * @input VND.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/VND.h"

VND::VND() {
  IntraChange* intraChange = new IntraChange();
  IntraReinsertion* intraReinsertion = new IntraReinsertion();
  InterChange* interChange = new InterChange();
  InterReinsertion* interReinsertion = new InterReinsertion();

  environments_.push_back(intraChange);
  environments_.push_back(intraReinsertion);
  environments_.push_back(interChange);
  environments_.push_back(interReinsertion);
}


VND::~VND() {}


Solution VND::execute(Solution& solution, bool isAnxious) {
  isAnxious_ = isAnxious;
  l_ = 0;
  Solution actualSolution = solution;
  Solution bestNeighbour = actualSolution;
  do {
    std::vector<Solution> totalNeighbours = environments_[l_]->generateNeighbours(actualSolution);
    for (int i = 0; i < totalNeighbours.size(); i++) {
      Solution actualNeighbour = totalNeighbours[i];
      if (actualNeighbour.getTotalTCT() < bestNeighbour.getTotalTCT()) {
        bestNeighbour = actualNeighbour;
        if (isAnxious_) {
          break;
        }
      }
    }
    if (bestNeighbour.getTotalTCT() < actualSolution.getTotalTCT()) {
      actualSolution = bestNeighbour;
      l_ = 0;
    } else {
      l_++; // Change within the environments because there is no upgrade
    }
  } while (l_ < environments_.size());
  return actualSolution;
}
