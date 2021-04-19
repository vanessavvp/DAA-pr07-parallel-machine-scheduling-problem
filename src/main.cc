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

#include "../include/parallelMachine.h"
#include "../include/machine.h"
#include "../include/task.h"

int main(int argc, char* argv[]) {
  std::string fileName = argv[1];
  ParallelMachine parallelMachine(fileName);
  parallelMachine.executeMachines();
  //std::cout << "PROBANDO\n";

  /*/ Insert in a specific position of the myVector
  std::vector<int> myVector{1, 3, 5};
  std::vector<int> myVector2{4,9,10};
  myVector2 = myVector;

  for (std::vector<int>::iterator it = myVector2.begin(); it < myVector2.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

*/


  /*
  for (std::vector<int>::iterator it = myVector.begin(); it < myVector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::vector<int>::iterator it2 = myVector.begin() + 0 + 1;
  myVector.insert(it2, 2);
  for (std::vector<int>::iterator it = myVector.begin(); it < myVector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::vector<int>::iterator it3 = myVector.begin() + 2 + 1;
  myVector.insert(it3, 4);
  for (std::vector<int>::iterator it = myVector.begin(); it < myVector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
  12345
  std::vector<int>::iterator it4 = myVector.begin() + 4 + 1;
  myVector.insert(it4, 6);
  for (std::vector<int>::iterator it = myVector.begin(); it < myVector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';*/
}