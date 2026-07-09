#include "dataset.hpp"
#include <cstddef>
#include <fstream>
#include <ios>
#include <stdexcept>

// Phase 1: implement the fvecs/ivecs loaders declared in dataset.hpp.
namespace hnsw {

hnsw::Dataset load_fvecs(const std::string &path) {
  hnsw::Dataset dataset;

  std::ifstream f(path, std::ios::binary);
  if (!f)
    throw std::runtime_error("cannot open " + path);

  int dim;
  f.read(reinterpret_cast<char *>(&dim), sizeof(dim));

  f.seekg(0, std::ios::end);
  std::streamoff bytes = f.tellg();
  f.seekg(0);
  int record_bytes = 4 + dim * 4;
  int num = bytes / record_bytes;

  dataset.dim = dim;
  dataset.num = num;
  dataset.data.resize((size_t)num * dim);

  for (int i = 0; i < num; ++i) {
    f.seekg(4, std::ios::cur);
    f.read(reinterpret_cast<char *>(&dataset.data[(size_t)i * dim]),
           dim * sizeof(float));
  }

  return dataset;
}

std::vector<int32_t> load_ivecs(const std::string &path, int &dim, int &num) {
  std::vector<int32_t> vecs;
  std::ifstream f(path, std::ios::binary);
  if (!f)
    throw std::runtime_error("cannot open " + path);

  f.read(reinterpret_cast<char *>(&dim), sizeof(dim));

  f.seekg(0, std::ios::end);
  std::streamoff bytes = f.tellg();
  f.seekg(0);

  int record_bytes = 4 + dim * 4;
  num = bytes / record_bytes;
  vecs.resize((size_t)num * dim);

  for (int i = 0; i < num; ++i) {
    f.seekg(4, std::ios::cur);
    f.read(reinterpret_cast<char *>(&vecs[(size_t)i * dim]), dim * sizeof(int));
  }

  return vecs;
}
} // namespace hnsw
