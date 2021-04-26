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

Solution Multiboot::execute(Problem& problem) {
  int iterations = 0;
  Solution actualSolution(problem.getNumberOfMachines());
  Solution bestSolution(problem.getNumberOfMachines());
  actualSolution = generatedSolution_.execute(problem);
  bestSolution = actualSolution;
  do {
    // Generar solución vecina, con local search
    // ACEPTA(SOLUCION_VECINA) Verificamos si con esa solucion el tct es menor respecto al de la mejor solucion
      // bestsolucion = actualSolution; QUE MOVIMIENTO ME DA ESE VALOR Y SU RESULTADO
    // Generar entorno con actualSolution, o sea GRASP
  } while(iterations < delimiter_);
  return bestSolution;
}


void Multiboot::setK(int k) {
  generatedSolution_.setK(k);
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