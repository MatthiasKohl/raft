/*
 * Copyright (c) 2020, NVIDIA CORPORATION.
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

#include <gtest/gtest.h>
#include <iostream>
#include <raft/integer_utils.h>

namespace raft {

TEST(Raft, rounding_up)
{
  ASSERT_EQ(raft::div_rounding_up_safe(5, 3), 2);
  ASSERT_EQ(raft::div_rounding_up_safe(0, 3), 0);
  ASSERT_EQ(raft::div_rounding_up_safe(7, 8), 1);
  ASSERT_EQ(raft::div_rounding_up_unsafe(5, 3), 2);
  ASSERT_EQ(raft::div_rounding_up_unsafe(0, 3), 0);
  ASSERT_EQ(raft::div_rounding_up_unsafe(7, 8), 1);
}

TEST(Raft, is_a_power_of_two)
{
  ASSERT_EQ(raft::is_a_power_of_two(1 << 5), true);
  ASSERT_EQ(raft::is_a_power_of_two((1 << 5) + 1), false);
}

}  // namespace raft
