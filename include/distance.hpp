#pragma once

// Header-only on purpose: tiny, hot functions called in the inner loop of every
// search. Defining them `inline` here lets the compiler inline them into callers
// in other translation units (no .cpp for this module).

namespace hnsw {

// Phase 1: define l2_sqr(const float* a, const float* b, int dim), dot(...), etc.

}  // namespace hnsw
