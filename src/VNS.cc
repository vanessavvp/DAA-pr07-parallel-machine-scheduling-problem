/**
 * PROJECT HEADER
 * @input VNS.h
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 24/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/VNS.h"

VNS::VNS() {
  kMax_ = 5;
}


VNS::VNS(bool isAnxious) {
  isAnxious_ = isAnxious;
  kMax_ = 5;
}

/** 
 * Find a task and a position within two random machines and deletes it
 * from one to insert into the other machina that task, is that to say, that 
 * it will return a solution that is far enough of the solution, for it to scape
 **/
Solution VNS::shaking(Solution solution, int k) {
  for (int i = 0; i < k; i++) {
    int firstMachine = 0;
    int secondMachine = 0;
    do {
      // Gets two machine randomly
      firstMachine = (std::rand() % solution.getSize());
      secondMachine = (std::rand() % solution.getSize());

    } while(firstMachine == secondMachine);
    // Gets a task and a position randomly
    int firstTask = std::rand() % solution[firstMachine].getMachineSize();
    int position = std::rand() % solution[secondMachine].getMachineSize();
    Task aux = solution[firstMachine][firstTask];
    solution[firstMachine].deleteTask(firstTask);
    solution[secondMachine].insertTask(position - 1, aux);
    solution.calculateObjectiveFunction();
  } 
  return solution;
}


/** Execute the VNS algorithm that explores more deeply every environment
 * to find the bestSolution and returns it
 **/
Solution VNS::execute(Problem problem) {
  int iterations = 0;
  int k;
  Solution x(problem.getNumberOfMachines());
  Solution x1;
  Solution x2;
  // Initial solution
  x = generatedSolution_.execute(problem); // GRASP
  x = improvement_.execute(x, isAnxious_);
  for (int i = 0; i < x.getSize(); i++) {
    // Kmax will be a value within 5 or a leaser size for the machine
    if(x[i].getMachineSize() < kMax_) {
      kMax_ = x[i].getMachineSize();
    }
  }
  Solution bestSolution = x;
  do {
    k = 1;
    do {
      x1 = shaking(x, k);
      x2 = localSearch_.execute(x1, isAnxious_);
      if (x2.getTotalTCT() < x.getTotalTCT()) {
        x = x2;
        k = 1; // Restart k
      } else {
        k++; // Bigger environment because there are no longer better tct values
      }
    } while (k <= kMax_);
    if (x.getTotalTCT() < bestSolution.getTotalTCT()) {
      bestSolution = x;
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
    x = generatedSolution_.execute(problem);
    x = improvement_.execute(x, isAnxious_);
    iterations++;
  } while (iterations < delimiter_);
  return bestSolution;
}


void VNS::setStopCriteria(bool stopCriteria) {
  stopCriteria_ = stopCriteria;
}


void VNS::introduceStopCriteria() {
  std::cout << "\nIntroduce the stop criteria for the MultiBoot algorithm:\n\t[1]Number of iterations or [0]Number of iterations without improvement: ";
  std::cin >> stopCriteria_;
}


void VNS::introduceDelimiter() {
  std::cout << "\nIntroduce the delimiter for the VNS algorithm: ";
  std::cin >> delimiter_;
}


void VNS::setAnxious(bool isAnxious) {
  isAnxious_ = isAnxious;
}


void VNS::setKGRASP(int kGRASP) {
  generatedSolution_.setK(kGRASP);
}


void VNS::setDelimiter(int delimiter) {
  delimiter_ = delimiter;
}


int VNS::getKGRASP() {
  return generatedSolution_.getK();
}
