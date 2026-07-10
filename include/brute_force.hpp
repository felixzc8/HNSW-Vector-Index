#pragma once

#include "dataset.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace hnsw {

// Phase 1: declare brute_force_knn here; define it in src/brute_force.cpp.
// This is your correctness oracle for measuring recall in every later phase.
std::vector<std::uint32_t> brute_force_knn(const float *query,
                                           const Dataset &base, std::size_t k);

} // namespace hnsw
