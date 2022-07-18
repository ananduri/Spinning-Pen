#include <gtest/gtest.h>
#include <vector>

#include "Eigen/Dense"

#include "dynamics.hh"
#include "pen.hh"
#include "rk4.hh"
#include "state.hh"

namespace sp {

class RK4Test : public ::testing::Test {
protected:
  constexpr static double G = -9.8;
  constexpr static double PI = 3.141592653;
  PenConfig config{
      .mass = 1.,
      .length = 0.2,
      .com_location = 0.5,
  };
  RK4 rk4{};
  Dynamics dynamics{G};
  double initial_time = 0;
};

TEST_F(RK4Test, IntegratingForZeroTimeShouldReturnSameState) {
  // SETUP
  const State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0,
      .angular_v = 2 * PI,
  };
  Pen pen{config, initial_state};

  // ACTION
  rk4.integrate(pen.get_mutable_state(), dynamics, initial_time,
                /*duration=*/0.);

  // VERIFICATION
  EXPECT_EQ(initial_state, pen.get_state());
}

TEST_F(RK4Test,
       IntegratingWithStepSizeBiggerThanDurationIsSameAsSteppingWithDuration) {
  // SETUP
  const State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0,
      .angular_v = 2 * PI,
  };
  Pen pen_integrate{config, initial_state};
  Pen pen_step{config, initial_state};
  const double duration = 1.;
  const double step_size = 1.5;

  // ACTION
  rk4.integrate(pen_integrate.get_mutable_state(), dynamics, initial_time,
                duration, step_size);
  rk4.integrate(pen_step.get_mutable_state(), dynamics, initial_time, duration,
                step_size);

  // VERIFICATION
  EXPECT_EQ(pen_integrate.get_state(), pen_step.get_state());
}

TEST_F(RK4Test, IntegratingFallingPenShouldMatchAnalyticResult) {
  // SETUP
  const State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0,
      .angular_v = 2 * PI,
  };
  Pen pen{config, initial_state};

  const auto StateOverTime = [&initial_state](const double t) {
    return State{
        .linear_d = initial_state.linear_d + t * initial_state.linear_v +
                    0.5 * std::pow(t, 2) * G * Vec3::UnitZ(),
        .linear_v = initial_state.linear_v + t * G * Vec3::UnitZ(),
        .axis = initial_state.axis,
        .angular_d = initial_state.angular_d + t * initial_state.angular_v,
        .angular_v = initial_state.angular_v,
    };
  };
  std::vector<double> durations{1.0, 5.0, 0.5, 10.0};

  // ACTION and VERIFICATION
  constexpr double TOLERANCE = 0.1;

  double total_duration = 0.;
  for (const double duration : durations) {
    rk4.integrate(pen.get_mutable_state(), dynamics, initial_time, duration);

    total_duration += duration;
    const State analytic_state = StateOverTime(total_duration);
    const State integrated_state = pen.get_state();

    EXPECT_NEAR(analytic_state.linear_d.x(), integrated_state.linear_d.x(),
                TOLERANCE);
    EXPECT_NEAR(analytic_state.linear_d.y(), integrated_state.linear_d.y(),
                TOLERANCE);
    EXPECT_NEAR(analytic_state.linear_d.z(), integrated_state.linear_d.z(),
                TOLERANCE);
    EXPECT_NEAR(analytic_state.linear_v.x(), integrated_state.linear_v.x(),
                TOLERANCE);
    EXPECT_NEAR(analytic_state.linear_v.y(), integrated_state.linear_v.y(),
                TOLERANCE);
    EXPECT_NEAR(analytic_state.linear_v.z(), integrated_state.linear_v.z(),
                TOLERANCE);
    EXPECT_EQ(analytic_state.axis, integrated_state.axis);
    EXPECT_NEAR(analytic_state.angular_d, integrated_state.angular_d,
                TOLERANCE);
    EXPECT_NEAR(analytic_state.angular_v, integrated_state.angular_v,
                TOLERANCE);
  }
}

} // namespace sp
