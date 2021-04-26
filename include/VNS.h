/**
 * PROJECT HEADER
 * @input VNS.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#ifndef VNS_H
#define VNS_H

#include "../include/algorithm.h"
#include "../include/GRASP.h"
#include "../include/interReinsertion.h"
#include "../include/VND.h"
#include "../include/problem.h"

#pragma once

class VNS : public Algorithm {
  public:
    VNS();
    VNS(bool isAnxious);
    ~VNS() {};
    Solution shaking(Solution solution, int k);
    Solution execute(Problem problem);

    void setStopCriteria(bool stopCriteria);
    void setAnxiety(bool isAnxious);
    void setKGRASP(int kGRASP);
    void setDelimiter(int delimiter);
    void introduceStopCriteria();
    void introduceDelimiter();
    
  private:
    VND localSearch_;
    GRASP generatedSolution_;
    InterReinsertion improvement_;
    bool isAnxious_;
    bool stopCriteria_;
    int kMax_;
    int delimiter_;
};

#endif // !VNS_H