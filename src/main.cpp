#include <filesystem>
#include <iostream>
#include <string>

#include "simulated_annealing.hpp"

int main(int /* argc */, char const* /* argv */[]) {
  auto cities = sa::ingest_data("res/eil51-tsp.txt");
  sa::simulated_annealing(cities);
}
