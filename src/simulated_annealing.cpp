#include "simulated_annealing.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
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

double calcTi_0(int i, double T0, double TN, double N) {
  return (T0 - i * ((T0 - TN) / N));
}

double calcTi_2(int i, double T0, double TN, double N) {
  const double a = ((T0 - TN) * (N + 1)) / N;
  const double b = T0 - a;
  return (a / (i + 1) + b);
}

double calcTi_3(int i, double T0, double TN, double N) {
  const double a = std::log(T0 - TN) / std::log(N);
  return (T0 - std::pow(i, a));
}

std::vector<Trio> simulated_annealing(std::vector<Trio> &s) {
  std::vector<PontoH> historico;
  int SAmax = 555;
  double T0 = 1000.0f;
  double TN = 0.000001f;
  double N = SAmax;  //??????
  // double a = 0.5f;
  double T = T0;
  int i = 1;
  std::cout << "T=" << T << std::endl;

  std::shuffle(s.begin(), s.end(), gen);
  std::vector<Trio> sBest;
  sBest.assign(s.begin(), s.end());

  while(T > 0.0001) {
    for(int iterT = 0; iterT < SAmax; ++iterT) {
      ++i;

      std::vector<Trio> s_ = swapRand(s);  // s'
      double delta = tspTotal(s_) - tspTotal(s);

      if(delta < 0) {
        s.assign(s_.begin(), s_.end());
        if(tspTotal(s_) < tspTotal(sBest)) {
          sBest.assign(s_.begin(), s_.end());
          historico.push_back({i, tspTotal(s)});
        }

      } else {
        if(prob0_1(gen) < std::exp(-delta / T)) {
          s.assign(s_.begin(), s_.end());
          historico.push_back({i, tspTotal(s)});
        }
      }
    }
    // T = calcTi_0(i, T0, TN, N);
    T *= 0.9;
    std::cout << "T=" << T << "s.size()=" << s.size() << std::endl;
  }

  std::ofstream os("convergencia.txt");

  for(auto &p : historico) {
    os << p.i << ',' << p.cost << '\n';
  }
  os.flush();
  os.close();

  std::system("python3 conver.py");

  return sBest;
}

}  // namespace sa