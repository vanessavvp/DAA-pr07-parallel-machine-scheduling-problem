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


void defineMultibootValues(Problem& problem, LocalSearch* localSearch);
void executeAndMeasureAlgorithms(Problem& problem, Algorithm* algorithm);

int main(int argc, char* argv[]) {
  std::cout << "\n\tParallel Machine Scheduling Problem with Dependent Setup Times\n";
  std::string fileName = argv[1];
  Problem problem(fileName);
  Problem problemB(fileName);

  std::cout << "\tThe inputfile " + fileName + " was correctly readed...\n";
  std::cout << "\n\tSetup time Matrix\n";
  problem.printSetupMatrix();


  // ------------- First week assignment --------------------------------------------------- //
  std::cout << "\n\tFIRST PART - Different algorithms implemented";
  FirstGreedy* firstGreedy = new FirstGreedy;
  SecondGreedy* secondGreedy = new SecondGreedy;
  GRASP* grasp = new GRASP;
  GRASP* graspB = new GRASP;


  /*std::cout << "\n[ Greedy ]";
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


  // ------------- Second week assignment --------------------------------------------------- //
  std::cout << "\n\n\tSECOND PART - Multiboot and different local searchs implementations";
  IntraChange* intraChange = new IntraChange;
  IntraReinsertion* intraReinsertion = new IntraReinsertion;
  InterChange* interChange = new InterChange;
  InterReinsertion* interReinsertion = new InterReinsertion;
  defineMultibootValues(problem, intraChange);
  defineMultibootValues(problem, intraReinsertion);
  defineMultibootValues(problem, interChange);
  defineMultibootValues(problem, interReinsertion);*/
  
  // ------------- Third week assignment --------------------------------------------------- //
  VNS* vns = new VNS(true);
  vns->introduceDelimiter();
  vns->setKGRASP(3);
  vns->setStopCriteria(false);
  executeAndMeasureAlgorithms(problem, vns);

}


void defineMultibootValues(Problem& problem, LocalSearch* localSearch) {
  Multiboot* multiboot = new Multiboot;
  std::string selectedStopCriteria;

  multiboot->introduceDelimiter();
  for (int i = 2; i <= 3; i++) {
    multiboot->setK(i);
    for (int stopCriteria = 0; stopCriteria < 2; stopCriteria++) {
      multiboot->setStopCriteria((bool)stopCriteria);
      if (stopCriteria == 0) {
        selectedStopCriteria = " number of iterations without improvement ";
      } else if (stopCriteria == 1) {
        selectedStopCriteria = " number of iterations with improvement ";
      }
      for (int isAnxious = 0; isAnxious < 2; isAnxious++) {
        multiboot->setAnxiety((bool)isAnxious);
        std::cout << "\n[ Multiboot, with k = " << multiboot->getK() << " -> Local Search: " ; // TODO: Añadir nombre
        std::cout << "-> Stop criteria: " << selectedStopCriteria << " -> Anxious activated?: " << std::boolalpha << ((bool)isAnxious);
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
