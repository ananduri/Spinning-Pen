#pragma once

#include <cassert>
#include <cmath>

#include "dynamics.hh"
#include "state.hh"

namespace sp {

// An interface that can be used to integrate the system being simulated.
// This class has a virtual step method to allow for different integration
// methods to be supported. Currently, a forward Euler method and a
// fourth-order Runge-Kutta method are available.
class Integrator {
public:
  // This function takes the state of a system along with the associated
  // dynamics, the current time, and a length of an interval of time, and
  // integrates the state across that time interval. The state is passed as an
  // in-out argument. Optionally, a step size for the steps taken by the
  // integrator may be passed in, to trade off between accuracy and
  // computational cost.
  void integrate(State &state, const Dynamics &dynamics, double t,
                 const double duration, const double step_size = 0.01) const {
    assert(duration >= 0);
    assert(step_size > 0);
    const int num_steps = std::floor(duration / step_size);
    const double remainder = duration - (num_steps * step_size);

    for (int i = 0; i < num_steps; ++i) {
      state = step(state, dynamics, t, step_size);
      t += step_size;
    }

    if (remainder > 0.) {
      state = step(state, dynamics, t, remainder);
      t += remainder;
    }
  }

  virtual State step(const State &state, const Dynamics &dynamics, double t,
                     double dt) const = 0;

  virtual ~Integrator() = default;
};

} // namespace sp
