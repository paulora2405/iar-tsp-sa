#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP

#include <vector>

#include "ingest.hpp"

namespace sa {

std::vector<Trio> swapRand(std::vector<Trio> cities);

double euclDist(Trio &first, Trio &second);

double tspTotal(std::vector<Trio> &cities);

double calcTi(std::vector<Trio> &s);

std::vector<Trio> simulated_annealing(std::vector<Trio> &cities);

}  // namespace sa

#endif