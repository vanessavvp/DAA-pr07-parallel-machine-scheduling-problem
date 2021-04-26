/**
 * PROJECT HEADER
 * @input VND.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef VND_H
#define VND_H

#include <iostream>

#include "../include/solution.h"
#include "../include/intraChange.h"
#include "../include/interChange.h"
#include "../include/intraReinsertion.h"
#include "../include/interReinsertion.h"

class VND {
  public:
    VND();
    ~VND();
    Solution execute(Solution& solution, bool isAnxious);

  private:
    std::vector<LocalSearch*> environments_;
    bool isAnxious_;
    int l_;
};

#endif // !VND_H