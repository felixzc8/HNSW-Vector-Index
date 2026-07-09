#pragma once

// Header-only on purpose: tiny, hot functions called in the inner loop of every
// search. Defining them `inline` here lets the compiler inline them into callers
// in other translation units (no .cpp for this module).

namespace hnsw {

// Phase 1: define l2_sqr(const float* a, const float* b, int dim), dot(...), etc.
inline float l2_sqr(const float* a, const float* b, int dim) {
  float s = 0.f;

  for (int i = 0; i < dim; i++) {
    float d = (a[i] - b[i]);
    s += d * d;
  }

  return s;
}

inline float dot(const float* a, const float* b, int dim) {
  float product = 0;
  
  for (int i = 0; i < dim; i++) {
    product += a[i] * b[i];
  }

  return product;
}

inline float cosine_distance(const float* a, const float* b, int dim) {
  return 1 - dot(a, b, dim);
}
}  // namespace hnsw
