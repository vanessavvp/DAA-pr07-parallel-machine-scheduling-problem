/**
 * PROJECT HEADER
 * @input multiboot.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <iostream>

#include "./algorithm.h"
#include "./problem.h"
#include "./localSearch.h"
#include "./GRASP.h"

#pragma once

class Multiboot : public Algorithm {
  public:
    Multiboot(){};
    Multiboot(LocalSearch* localSearch, bool isAnxious);
    ~Multiboot(){};
    Solution execute(Problem problem);

    void setK(int k);
    int getK();
    void setAnxious(bool isAnxious);
    void setDelimiter(int delimiter);
    void introduceDelimiter();
    void setStopCriteria(bool stopCriteria);
    void introduceStopCriteria();
    void setLocalSearch(LocalSearch* localSearch);

  private:
    GRASP generatedSolution_;
    LocalSearch* localSearch_;
    int delimiter_;
    bool isAnxious_;
    bool stopCriteria_;
};
#endif // !MULTIBOOT_H