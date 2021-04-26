/**
 * PROJECT HEADER
 * @input multiboot.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/multiboot.h"

Multiboot::Multiboot(LocalSearch* localSearch, bool isAnxious) {
  isAnxious_ = isAnxious;
  localSearch_ = localSearch;
}

Solution Multiboot::execute(Problem problem) {
  int iterations = 0;
  Solution actualSolution(problem.getNumberOfMachines());
  Solution bestSolution(problem.getNumberOfMachines());
  actualSolution = generatedSolution_.execute(problem);
  bestSolution = actualSolution;
  do {
    actualSolution = localSearch_->execute(actualSolution, isAnxious_); // Generar solución vecina, con local search
    if (actualSolution.getTotalTCT() < bestSolution.getTotalTCT()) { 
      bestSolution = actualSolution;
      if (stopCriteria_ == true) {
        iterations = 0;
      }
    } else {
      if (stopCriteria_ == true) {
        iterations++;
      }
    }
    if (stopCriteria_ == false) {
      iterations++;
    }
    actualSolution = generatedSolution_.execute(problem);
  } while(iterations < delimiter_);

  return bestSolution;
}


void Multiboot::setK(int k) {
  generatedSolution_.setK(k);
}

int Multiboot::getK() {
  return generatedSolution_.getK();
}


void Multiboot::setAnxiety(bool isAnxious) {
  isAnxious_ = isAnxious;
}


void Multiboot::setLocalSearch(LocalSearch* localSearch) {
  localSearch_ = localSearch;
}

void Multiboot::setDelimiter(int delimiter) {
  delimiter_ = delimiter;
}

void Multiboot::setStopCriteria(bool stopCriteria) {
  stopCriteria_ = stopCriteria;
}

void Multiboot::introduceStopCriteria() {
  std::cout << "\nIntroduce the stop criteria for the MultiBoot algorithm:\n\t[1]Number of iterations or [0]Number of iterations without improvement: ";
  std::cin >> stopCriteria_;
}

void Multiboot::introduceDelimiter() {
  std::cout << "\nIntroduce the delimiter for the MultiBoot algorithm: ";
  std::cin >> delimiter_;
}