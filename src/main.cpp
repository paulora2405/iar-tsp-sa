#include <filesystem>
#include <iostream>
#include <string>

#include "simulated_annealing.hpp"

int main(int /* argc */, char const* /* argv */[]) {
  // auto cities = sa::ingest_data("res/test.txt");
  auto cities = sa::ingest_data("res/eil51-tsp.txt");
  // auto cities = sa::ingest_data("res/kroA100-tsp.txt");

  sa::simulated_annealing(cities);
}
