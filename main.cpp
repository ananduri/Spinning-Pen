#include <iostream>

#include "Eigen/Dense"

#include "dynamics.hh"
#include "forward_euler.hh"
#include "integrator.hh"
#include "pen.hh"
#include "rk4.hh"
#include "state.hh"

using sp::Vec3;

int main() {
  constexpr double G = -9.8;
  constexpr double PI = 3.141592653;

  const sp::PenConfig config{
      .mass = 1.,
      .length = 0.2,
      .com_location = 0.5,
  };
  // Set the initial conditions.
  const sp::State initial_state{
      .linear_d = Vec3::Zero(),
      .linear_v = 1 * Vec3::UnitZ(),
      .axis = Vec3::UnitY(),
      .angular_d = 0.,
      .angular_v = 2 * PI,
  };
  sp::Pen pen{config, initial_state};

  const sp::Dynamics dynamics{G};

  const double initial_time = 0.;
  const double duration = 50.;
  const double step_size = 0.01;

  const sp::ForwardEuler integrator{};
  // const sp::RK4 integrator{};

  std::cout << initial_state << "\n";

  integrator.integrate(pen.get_mutable_state(), dynamics, initial_time,
                       duration, step_size);
  std::cout << pen.get_state() << "\n";

  return 0;
}
