/**
 * PROJECT HEADER
 * @file GRASP.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef GRASP_H
#define GRASP_H

#include <iostream>

#include "./algorithm.h"

class GRASP : public Algorithm {
  public:
    Solution execute(Problem problem);


};

#endif // !GRASP_H

