#include "simulated_annealing.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

namespace sa {
static std::default_random_engine gen(time(NULL));
static std::uniform_real_distribution<double> prob0_1(0.0f, 1.0f);

std::vector<Trio> swapRand(std::vector<Trio> cities) {
  static std::uniform_int_distribution<int> dist(1, cities.size());
  int first = dist(gen), second;
  do {
    second = dist(gen);
  } while(first == second);

  std::swap(cities[first], cities[second]);

  return cities;
}

double euclDist(Trio &first, Trio &second) {
  // raiz( (x1-x2)^2 + (y1-y2)^2 )
  return std::pow(std::pow((first.x - second.x), 2) + std::pow((first.y - second.y), 2), 0.5f);
}

double tspTotal(std::vector<Trio> &s) {  // O(n)
  double sumEucl = 0.0f;
  for(size_t i = 0; i < s.size() - 1; ++i) {
    // std::cout << "Dist(" << s[i].n << "->" << s[i + 1].n
    //           << "):" << euclDist(s[i], s[i + 1]) << '\n';
    sumEucl += euclDist(s[i], s[i + 1]);
  }
  return sumEucl;
}

double calcTi(std::vector<Trio> &s) {}

std::vector<Trio> simulated_annealing(std::vector<Trio> &s) {
  // std::vector<double> tsps;
  int SAmax = 100;
  int iterT = 0;
  double T0 = 1000.0f;
  double a = 0.5f;
  double T = T0;

  std::shuffle(s.begin(), s.end(), gen);
  std::vector<Trio> sBest;
  sBest.clear();
  std::copy(s.begin(), s.end(), std::back_inserter(sBest));  // sBest = s;

  while(T > 0.0001) {
    while(iterT < SAmax) {
      ++iterT;
      std::vector<Trio> s_ = swapRand(s);  // s'
      double delta = tspTotal(s_) - tspTotal(s);
      if(delta < 0) {
        s.clear();
        std::copy(s_.begin(), s_.end(), std::back_inserter(s));  // s = s_;
        if(tspTotal(s_) < tspTotal(sBest)) {
          sBest.clear();
          std::copy(s_.begin(), s_.end(), std::back_inserter(sBest));  // sBest = s;
        }
      } else {
        if(prob0_1(gen) < std::exp(-delta / T)) {
          s.clear();
          std::copy(s_.begin(), s_.end(), std::back_inserter(s));  // s = s_;
        }
      }
    }
    T = T * a;
    iterT = 0;
  }

  // std::cerr << "Vetor:\n";
  // for(size_t i = 0; i < sBest.size(); ++i) {
  //   std::cerr << sBest[i].n << '(' << sBest[i].x << ',' << sBest[i].y << ")->";
  // }
  // std::cerr << '\n';

  return sBest;
}

}  // namespace sa