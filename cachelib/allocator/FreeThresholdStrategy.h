/*
 * Copyright (c) Facebook, Inc. and its affiliates.
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

#pragma once

#include "cachelib/allocator/BackgroundMoverStrategy.h"
#include "cachelib/allocator/Cache.h"

namespace facebook {
namespace cachelib {

// Base class for background mover strategy.
class FreeThresholdStrategy : public BackgroundMoverStrategy {
 public:
  FreeThresholdStrategy(double lowEvictionAcWatermark,
                        double highEvictionAcWatermark,
                        uint64_t maxEvictionBatch,
                        uint64_t minEvictionBatch);
  ~FreeThresholdStrategy() {}

  std::vector<size_t> calculateBatchSizes(
      const CacheBase& cache,
      std::vector<std::tuple<TierId, PoolId, ClassId>> acVecs);
  BackgroundStrategyStats getStats();

 private:
  double lowEvictionAcWatermark{2.0};
  double highEvictionAcWatermark{5.0};
  uint64_t maxEvictionBatch{40};
  uint64_t minEvictionBatch{5};
  std::vector<std::vector<std::vector<std::vector<double>>>> highEvictionAcWatermarks;

  std::vector<std::vector<std::vector<std::vector<double>>>> acLatencies; 

private:
  //void calculateBenefitMig(uint64_t p99, unsigned int tid, PoolId pid, ClassId cid); //function to calculate the benefit of eviction for a certain ac class
  void calculateLatency(uint64_t p99, unsigned int tid, PoolId pid, ClassId cid);

};

} // namespace cachelib
} // namespace facebook
