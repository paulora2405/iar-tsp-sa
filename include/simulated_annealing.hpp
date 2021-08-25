#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP

#include <vector>

#include "ingest.hpp"

namespace sa {

struct PontoH {
  int i;
  double cost;
};

std::vector<Trio> swapRand(std::vector<Trio> cities);

double euclDist(Trio &first, Trio &second);

double tspTotal(std::vector<Trio> &cities);

double calcTi_0(int i, double T0, double TN, double N);

double calcTi_2(int i, double T0, double TN, double N);

double calcTi_3(int i, double T0, double TN, double N);

std::vector<Trio> simulated_annealing(std::vector<Trio> &cities);

}  // namespace sa

#endif