#include <gtest/gtest.h>

#include "state.hh"

namespace sp {

TEST(StateTest, DefaultInitializedStatesShouldBeEqual) {
  // SETUP
  const State a;
  const State b;

  // VERIFICATION
  EXPECT_EQ(a, b);
}

TEST(StateTest, DefaultInitializedStateDeltaShouldNotChangeState) {
  // SETUP
  const State state;
  const StateDelta delta;

  // ACTION
  const State new_state = state + delta;

  // VERIFICATION
  EXPECT_EQ(state, new_state);
}

} // namespace sp
