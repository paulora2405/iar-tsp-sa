#include "simulated_annealing.hpp"

#include <iostream>

namespace sa {

void simulated_annealing(std::vector<Trio> cities) {
  for(size_t i = 0; i < 10; i++) {
    std::cout << cities[i].n << ' ' << cities[i].x << ' ' << cities[i].y << '\n';
  }
}

}  // namespace sa