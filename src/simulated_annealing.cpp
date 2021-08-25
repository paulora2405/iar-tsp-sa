#include "simulated_annealing.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

namespace sa {
static std::default_random_engine gen(time(NULL));
static std::uniform_real_distribution<double> prob0_1(0.0f, 1.0f);

std::vector<Trio> swapRand(std::vector<Trio> cities) {
  static std::uniform_int_distribution<int> dist(0, cities.size() - 1);
  static std::uniform_int_distribution<int> swapQnt(1, 5);

  for(int i = 0; i < swapQnt(gen); i++) {
    int first = dist(gen), second;
    do {
      second = dist(gen);
    } while(first == second);

    std::swap(cities.at(first), cities.at(second));
  }

  return cities;
}

double euclDist(Trio &first, Trio &second) {
  return std::sqrt(std::pow((first.x - second.x), 2) + std::pow((first.y - second.y), 2));
}

double tspTotal(std::vector<Trio> &s) {  // O(n)
  double sumEucl = 0;
  for(size_t i = 0; i < s.size() - 1; ++i) {
    sumEucl += euclDist(s[i], s[i + 1]);
  }
  sumEucl += euclDist(s.front(), s.back());
  return sumEucl;
}

double calcTi(int formula, int i, double T0, double TN, double N) {
  double a, b;
  switch(formula) {
    case 0:
      return (T0 - i * ((T0 - TN) / N));

    case 1:
      return T0 * std::pow(TN / T0, i / N);

    case 2:
      a = ((T0 - TN) * (N + 1)) / N;
      b = T0 - a;
      return (a / (i + 1) + b);

    case 3:
      a = std::log(T0 - TN) / std::log(N);
      return (T0 - std::pow(i, a));

    default:
      return 0;
  }
}

double simulated_annealing(std::vector<Trio> &s, int formula, bool drawGraph) {
  std::vector<PontoH> historico;
  int SAmax = 500;
  double T0 = 1500.0f;
  double N = 100000.0f;
  double TN = 0.000001f;
  double T = T0;
  int i = 0;
  std::cout << "T=" << T << " T0=" << T0 << " N=" << N << " TN=" << TN << " Formula " << formula
            << std::endl;

  std::shuffle(s.begin(), s.end(), gen);
  std::vector<Trio> sBest;
  sBest = s;

  while(T > 0.00001) {
    for(int iterT = 0; iterT < SAmax; ++iterT) {
      ++i;

      std::vector<Trio> s_ = swapRand(s);  // s'
      double delta = tspTotal(s_) - tspTotal(s);

      if(delta < 0) {
        s = s_;
        if(tspTotal(s_) < tspTotal(sBest)) {
          sBest = s_;
          historico.push_back({i, tspTotal(s)});
        }

      } else {
        if(prob0_1(gen) < std::exp(-delta / T)) {
          s = s_;
          historico.push_back({i, tspTotal(s)});
        }
      }
    }
    T = calcTi(formula, i, T0, TN, N);
  }

  if(drawGraph) {
    std::ofstream os("convergencia.txt");

    for(auto &p : historico) {
      os << p.i << ',' << p.cost << '\n';
    }
    os.flush();
    os.close();

    std::string call = "python3 conver.py " + std::to_string(formula);
    if(std::system(call.c_str()) == 0)
      std::cout << "Generated Graph" << std::endl;
  }

  return tspTotal(sBest);
}

}  // namespace sa