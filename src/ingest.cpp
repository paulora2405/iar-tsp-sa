#include "ingest.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace sa {

std::vector<Trio> ingest_data(std::string filename) {
  std::string path = std::filesystem::current_path();
  if(path.find("build/src") != std::string::npos) {
    std::filesystem::current_path("../..");
  }
  std::ifstream is(filename);
  if(!is.is_open())
    std::cerr << "Erro ao abrir " << filename, exit(EXIT_FAILURE);

  int dimension;
  char buffer[1024];
  is.getline(buffer, 1024);  // first line discarted
  is.getline(buffer, 1024);  // second line discarted
  is >> buffer >> buffer >> buffer;
  dimension = std::atoi(buffer);
  is.getline(buffer, 1024);  // \n discarted
  is.getline(buffer, 1024);  // fourth line discarted
  is.getline(buffer, 1024);  // fifth line discarted

  std::vector<Trio> cities;
  cities.reserve(dimension);

  std::string n, x, y;
  for(int i = 0; i < dimension; i++) {
    is >> n >> x >> y;
    cities.push_back({
        std::atoi(n.c_str()),  //
        std::atoi(x.c_str()),  //
        std::atoi(y.c_str())   //
    });
  }

  return cities;
}

}  // namespace sa
