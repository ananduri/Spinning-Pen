#include <gtest/gtest.h>

#include "dynamics.hh"
#include "state.hh"

namespace sp {

TEST(DynamicsTest, DynamicsAppliedForZeroTimeDoesNotChangeState) {
  // SETUP
  constexpr static double G = -9.8;
  Dynamics dynamics{G};
  State state;
  const double dt = 0;

  // ACTION
  StateDelta delta = dynamics.get_derivative(state)(dt);
  const State new_state = state + delta;

  // VERIFICATION
  EXPECT_EQ(state, new_state);
}

TEST(DynamicsTest, ZeroGravityDynamicsDoesNotChangeVelocity) {
  // SETUP
  constexpr static double G = 0.;
  Dynamics dynamics{G};
  State state;
  const double dt = 0.1;

  // ACTION
  StateDelta delta = dynamics.get_derivative(state)(dt);
  const State new_state = state + delta;

  // VERIFICATION
  EXPECT_EQ(state.linear_v, new_state.linear_v);
  EXPECT_EQ(state, new_state);
}

} // namespace sp
