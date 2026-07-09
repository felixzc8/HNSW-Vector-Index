#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace hnsw {

// Phase 1: declare the fvecs/ivecs loaders here; define them in
// src/dataset.cpp.
struct Dataset {
  std::vector<float> data;
  int dim = 0;
  int num = 0;
};

Dataset load_fvecs(const std::string &path);
std::vector<int32_t> load_ivecs(const std::string &path, int &dim, int &num);
} // namespace hnsw
