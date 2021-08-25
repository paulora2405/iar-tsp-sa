#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "simulated_annealing.hpp"

int main(int argc, char const* argv[]) {
  int formula = argc == 2 ? std::atoi(argv[1]) : 0;
  // auto cities = sa::ingest_data("res/test.txt");
  auto cities = sa::ingest_data("res/eil51-tsp.txt");
  // auto cities = sa::ingest_data("res/kroA100-tsp.txt");

  std::ofstream bp("boxplot.txt");

  bool draw = true;
  for(int i = 0; i < 10; ++i) {
    std::cout << "Execution n" << i + 1 << std::endl;
    bp << sa::simulated_annealing(cities, formula, draw) << '\n';
    draw = false;
  }
  bp.flush();
  bp.close();

  std::string call = "python3 boxplot.py " + std::to_string(formula);
  if(std::system(call.c_str()) == 0)
    std::cout << "Generated Boxplot" << std::endl;
}
