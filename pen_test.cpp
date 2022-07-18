#include <cmath>
#include <gtest/gtest.h>

#include "Eigen/Dense"

#include "pen.hh"

namespace sp {

TEST(PenTest, PenShouldReturnSameStateItWasInitializedWith) {
  // SETUP
  const PenConfig config{
      .mass = 1.,
      .length = 0.2,
      .com_location = 0.5,
  };
  const State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0.,
      .angular_v = 0.,
  };

  // ACTION
  Pen pen{config, initial_state};

  // VERIFICATION
  EXPECT_EQ(initial_state, pen.get_state());
}

TEST(PenTest, PenMomentOfInertiaIsBoundedByAnalyticResults) {
  // SETUP
  const double mass = 1.;
  const double length = 0.2;
  const PenConfig config{
      .mass = mass,
      .length = length,
      .com_location = 0.75,
  };
  const State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0.,
      .angular_v = 0.,
  };

  // The moment of inertia for a uniform rod rotating about one end.
  const double I_rotating_end = (1.0 / 3.0) * mass * std::pow(length, 2);
  // The moment of inertia for a uniform rod rotating about its center.
  const double I_rotating_middle = (1.0 / 12.0) * mass * std::pow(length, 2);

  // ACTION
  Pen pen{config, initial_state};

  // VERIFICATION
  const double I = get_moment_of_inertia(pen);
  EXPECT_LE(I, I_rotating_end);
  EXPECT_GE(I, I_rotating_middle);
}

} // namespace sp
