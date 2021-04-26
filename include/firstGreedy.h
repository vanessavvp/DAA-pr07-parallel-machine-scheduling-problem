/**
 * PROJECT HEADER
 * @file firstGreedy.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef FIRST_GREEDY_H
#define FIRST_GREEDY_H

#include <iostream>

#include "./algorithm.h"
#include "./problem.h"

#pragma once

class FirstGreedy : public Algorithm {
  public: 
    FirstGreedy() {}
    ~FirstGreedy() {}
    Solution execute(Problem problem);

};

#endif // !FIRST_GREEDY_H

