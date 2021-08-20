#ifndef INGEST_HPP
#define INGEST_HPP

#include <string>
#include <vector>

namespace sa {

struct Trio {
  int n;
  int x;
  int y;
};

std::vector<Trio> ingest_data(std::string filename);

}  // namespace sa

#endif