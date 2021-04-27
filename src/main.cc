/**
 * PROJECT HEADER
 * @input main.cc
 * @author: Vanessa Valentina Villalba Perez
 * Contact: alu0101265704@ull.edu.es
 * @date: 11/04/2021
 * Subject: Diseño y Análisis de Algoritmos
 * Practice: Numberº7
 * Purpose: Parallel Machine Scheduling Problem with Dependent Setup Times
 */

#include "../include/problem.h"
#include "../include/firstGreedy.h"
#include "../include/secondGreedy.h"
#include "../include/GRASP.h"
#include "../include/intraChange.h"
#include "../include/intraReinsertion.h"
#include "../include/interChange.h"
#include "../include/interReinsertion.h"
#include "../include/multiboot.h"
#include "../include/VNS.h"
#include <chrono>

void defineMultibootValues(Problem& problem, LocalSearch* localSearch, std::string localSearchName);
void executeAndMeasureAlgorithms(Problem& problem, Algorithm* algorithm);

int main(int argc, char* argv[]) {
  std::cout << "\n\tParallel Machine Scheduling Problem with Dependent Setup Times\n";
  std::string fileName = argv[1];
  Problem problem(fileName);
  Problem problemB(fileName);
  std::cout << "\tThe inputfile " + fileName + " was correctly readed...\n";
  

  // ------------- First week assignment --------------------------------------------------- //
  std::cout << "\n\n\tFIRST PART - Different algorithms implemented";
  FirstGreedy* firstGreedy = new FirstGreedy;
  SecondGreedy* secondGreedy = new SecondGreedy;
  GRASP* grasp = new GRASP;
  GRASP* graspB = new GRASP;


  std::cout << "\n[ Greedy ]";
  executeAndMeasureAlgorithms(problem, firstGreedy);
  std::cout << "\n\n[ Second Greedy ]";
  executeAndMeasureAlgorithms(problem, secondGreedy);
  srand(time(NULL));
  std::cout << "\n\n[ Constructive Phase of GRASP, with k = 2 ]";
  grasp->setK(2);
  srand(time(NULL));
  executeAndMeasureAlgorithms(problem, grasp);
  std::cout << "\n\n[ Constructive Phase of GRASP, with k = 3 ]";
  graspB->setK(3);
  srand(time(NULL));
  executeAndMeasureAlgorithms(problemB, graspB);

  std::string option;
  std::cout << "Do you want to generate EVERY combination of the Multiboot and VNS algorithms? [y/n]: ";
  std::cin >> option;
  int k;
  int iterationsLimit = 0;
  std::string isAnxious;
  bool anxious;
  std::string stopCriteria;
  bool criteria;
  std::string algorithm;
  IntraChange* intraChange = new IntraChange;
  IntraReinsertion* intraReinsertion = new IntraReinsertion;
  InterChange* interChange = new InterChange;
  InterReinsertion* interReinsertion = new InterReinsertion;

  if (option == "n") {
    std::cout << "Iterations limit o delimiter [20-50-100]: "; std::cin >> iterationsLimit;
    std::cout << "K value [2-3]: "; std::cin >> k;
    std::cout << "Anxious approach [y/n]: "; std::cin >> isAnxious;
    if (isAnxious == "y") {
      anxious = true;
    } else if (isAnxious == "n") {
      anxious = false;
    }
    std::cout << "Stop criteria, number of iterations with improvement [y/n]: "; std::cin >> stopCriteria;
    if (stopCriteria == "y") {
      criteria = true;
    } else if (stopCriteria == "n") {
      criteria = false;
    }
    std::cout << "Multiboot or VNS algorithm [m/v]: "; std::cin >> algorithm;
    if (algorithm == "m") {
      Multiboot* multiboot = new Multiboot;
      multiboot->setDelimiter(iterationsLimit);
      multiboot->setK(k);
      multiboot->setAnxious(anxious);
      multiboot->setStopCriteria(criteria);

      std::cout << "\n\tINTRACHANGE\n";
      multiboot->setLocalSearch(intraChange);
      executeAndMeasureAlgorithms(problem, multiboot);

      std::cout << "\n\tINTRAREINSERTION\n";
      multiboot->setLocalSearch(intraReinsertion);
      executeAndMeasureAlgorithms(problem, multiboot);

      std::cout << "\n\tINTERCHANGE\n";
      multiboot->setLocalSearch(interChange);
      executeAndMeasureAlgorithms(problem, multiboot);

      std::cout << "\n\tINTERREINSERTION\n";
      multiboot->setLocalSearch(interReinsertion);
      executeAndMeasureAlgorithms(problem, multiboot);
    } else if (algorithm == "v") {
      VNS* vns = new VNS();
      vns->setDelimiter(iterationsLimit);
      vns->setKGRASP(k);
      vns->setAnxious(anxious);
      vns->setStopCriteria(criteria);
      executeAndMeasureAlgorithms(problem, vns);
    }
  } else if (option == "y") {
    // ------------- Second week assignment --------------------------------------------------- //
    std::cout << "\n\n\tSECOND PART - Multiboot and different local searchs implementations";
    IntraChange* intraChange = new IntraChange;
    IntraReinsertion* intraReinsertion = new IntraReinsertion;
    InterChange* interChange = new InterChange;
    InterReinsertion* interReinsertion = new InterReinsertion;
    defineMultibootValues(problem, intraChange, "IntraChange");
    defineMultibootValues(problem, intraReinsertion, "IntraReinsertion");
    defineMultibootValues(problem, interChange, "InterChange");
    defineMultibootValues(problem, interReinsertion, "InterReinsertion");

    // ------------- Third week assignment --------------------------------------------------- //
    std::cout << "\n\n\tTHIRD PART - VNS with VND implementation";
    std::string selectedStopCriteria;
    VNS* vns = new VNS();
    vns->introduceDelimiter();
    std::cout << "\n\n\tLOADING...\n\n";
    for (int anxious = 0; anxious < 2; anxious++) {
      vns->setAnxious((bool)anxious);
      for (int stopCriteria = 0; stopCriteria < 2; stopCriteria++) {
        vns->setStopCriteria((bool)stopCriteria);
        if (stopCriteria == 0) {
          selectedStopCriteria = " number of iterations without improvement ";
        } else if (stopCriteria == 1) {
          selectedStopCriteria = " number of iterations with improvement ";
        }
        for (int k = 2; k <= 3; k++) {
          vns->setKGRASP(k);
          std::cout << "\n\t-> VNS, with k = " << vns->getKGRASP();
          std::cout << "\n\t-> Stop criteria: " << selectedStopCriteria << "\n\t-> Anxious aproach activated?: " << std::boolalpha << ((bool)anxious);
          executeAndMeasureAlgorithms(problem, vns);
        }
      }
    }
  }
}


void defineMultibootValues(Problem& problem, LocalSearch* localSearch, std::string localSearchName) {
  Multiboot* multiboot = new Multiboot;
  std::string selectedStopCriteria;

  multiboot->introduceDelimiter();
  std::cout << "\n\n\tLOADING...\n\n";
  for (int anxious = 0; anxious < 2; anxious++) {
    multiboot->setAnxious((bool)anxious);
    for (int stopCriteria = 0; stopCriteria < 2; stopCriteria++) {
      multiboot->setStopCriteria((bool)stopCriteria);
      if (stopCriteria == 0) {
        selectedStopCriteria = " number of iterations without improvement ";
      } else if (stopCriteria == 1) {
        selectedStopCriteria = " number of iterations with improvement ";
      }
      for (int k = 2; k <= 3; k++) {
        multiboot->setK(k);
        std::cout << "\n\t-> Multiboot, with k = " << multiboot->getK() << "\n\t-> Local Search: " << localSearchName;
        std::cout << "\n\t-> Stop criteria: " << selectedStopCriteria << "\n\t-> Anxious aproach activated?: " << std::boolalpha << ((bool)anxious);
        multiboot->setLocalSearch(localSearch);
        executeAndMeasureAlgorithms(problem, multiboot);
      }
    }
  }
}


void executeAndMeasureAlgorithms(Problem& problem, Algorithm* algorithm) {
  problem.setAlgorithm(algorithm);
  auto begin = std::chrono::system_clock::now();
  problem.execute();
  auto end = std::chrono::system_clock::now();
  auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  problem.printGeneratedSolution();
  std::cout << "Program execution time: " << std::to_string(totalTime.count() * 1e-9) + " seconds\n";
}
