#include "brute_force.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

void test_returns_nearest_ids_in_order() {
  const hnsw::Dataset base{
      {
          0.f,
          0.f,
          1.f,
          0.f,
          2.f,
          0.f,
          3.f,
          0.f,
      },
      2,
      4,
  };
  const float query[] = {2.f, 1.f};

  const auto actual = hnsw::brute_force_knn(query, base, 3);
  const std::vector<std::uint32_t> expected = {2, 1, 3};

  assert(actual == expected);
}

void test_zero_k_returns_empty() {
  const hnsw::Dataset base{{0.f, 0.f}, 2, 1};
  const float query[] = {0.f, 0.f};

  const auto actual = hnsw::brute_force_knn(query, base, 0);

  assert(actual.empty());
}

void test_k_larger_than_dataset_returns_all() {
  const hnsw::Dataset base{
      {
          0.f,
          0.f,
          2.f,
          0.f,
      },
      2,
      2,
  };
  const float query[] = {1.5f, 0.f};

  const auto actual = hnsw::brute_force_knn(query, base, 10);
  const std::vector<std::uint32_t> expected = {1, 0};

  assert(actual == expected);
}

int main() {
  test_returns_nearest_ids_in_order();
  test_zero_k_returns_empty();
  test_k_larger_than_dataset_returns_all();
}
