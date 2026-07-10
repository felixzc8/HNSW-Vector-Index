#include "brute_force.hpp"
#include "distance.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

namespace hnsw {

std::vector<std::uint32_t>
brute_force_knn(const float *query, const hnsw::Dataset &base, std::size_t k) {

  if (k == 0) {
    return std::vector<std::uint32_t>();
  }

  using Candidate = std::pair<float, std::uint32_t>;

  std::priority_queue<Candidate> max_heap;

  for (int i = 0; i < base.num; ++i) {
    const float *point = &base.data[static_cast<std::size_t>(i) * base.dim];

    float dist = hnsw::l2_sqr(query, point, base.dim);
    Candidate candidate{dist, static_cast<std::uint32_t>(i)};

    if (max_heap.size() < k) {
      max_heap.emplace(candidate);
    } else if (candidate < max_heap.top()) {
      max_heap.pop();
      max_heap.emplace(candidate);
    }
  }

  std::vector<std::uint32_t> res;

  while (!max_heap.empty()) {
    res.push_back(static_cast<std::uint32_t>(max_heap.top().second));
    max_heap.pop();
  }
  std::reverse(res.begin(), res.end());

  return res;
}
} // namespace hnsw
