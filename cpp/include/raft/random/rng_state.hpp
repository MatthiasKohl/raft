/*
 * Copyright (c) 2022, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __RNG_STATE_H
#define __RNG_STATE_H

#pragma once

namespace raft {
namespace random {

/** all different generator types used */
enum GeneratorType {
  /** curand-based philox generator */
  GenPhilox = 0,
  /** Permuted Congruential Generator */
  GenPC
};

/**
 * The RNG state used to keep RNG state around on the host.
 *
 * @note: The default generator type is GenPhilox for backward compatibility.
 *        For best performance, you should always try to use GenPC first,
 *        since the PC generator is up to 2x faster in many use cases.
 */
struct RngState {
  explicit RngState(uint64_t _seed) : seed(_seed) {}
  RngState(uint64_t _seed, GeneratorType _type) : seed(_seed), type(_type) {}
  RngState(uint64_t _seed, uint64_t _base_subsequence, GeneratorType _type)
    : seed(_seed), base_subsequence(_base_subsequence), type(_type)
  {
  }

  uint64_t seed{0};
  uint64_t base_subsequence{0};
  /**
   * The generator type. For now, use Philox as default since PCGenerator
   * caused issues in RAFT DivideTests and cugraph RMAT tests.
   * This should be changed to GenPC as soon as all dependent tests are passing.
   */
  GeneratorType type{GeneratorType::GenPhilox};

  void advance(uint64_t max_uniq_subsequences_used,
               uint64_t max_numbers_generated_per_subsequence = 0)
  {
    base_subsequence += max_uniq_subsequences_used;
  }
};

};  // end namespace random
};  // end namespace raft

#endif
