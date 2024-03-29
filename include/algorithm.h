/**
 * PROJECT HEADER
 * @file algorithm.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>

#include "./solution.h"

#pragma once

class Problem;
class Algorithm {
  public:
    virtual ~Algorithm() = default;
    virtual Solution execute(Problem problem) = 0;
};

#endif // !ALGORITHM_H
