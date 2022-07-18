#pragma once

#include <functional>

#include "Eigen/Dense"

#include "state.hh"

namespace sp {

// This function must be supplied a delta t.
using DerivativeToDelta = std::function<StateDelta(double)>;

// This class holds information encoding the dynamics of the system (a pen in
// free-fall, in this case.)
//
// The way dynamics are represented in this simulation is as a mapping from
// two parameters, the current state and the length of a (small) time
// interval, to the change in the system state that occurs over that
// time interval (the change being represented as a StateDelta).
//
// The get_derivative function of this class returns a curried version of that
// mapping, where the current state is supplied and a function then mapping from
// the length of a time interval to a StateDelta is returned. This is to
// facilitate consumption of the dynamics mapping; oftentimes the current state
// is known but more flexibility is required with the time intervals the
// dynamics is applied over. Also, a curried function (a lambda expression) is
// returned instead of a StateDelta (that we might then multiply by a dt) to
// have stricter type safety; a StateDelta should never be added to a State
// unless a length of time over which the dynamics is applied has been supplied.
// Returning a function that takes a length of time before returning a
// StateDelta enforces this condition.
//
// Note that the dynamics of a spinning pen is assumed not to have any time
// dependence, and so time is not a parameter supplied to the get_derivative
// function. The function could be extended to incorporate the current time if
// we wanted to simulate time-dependent dynamics.
class Dynamics {
public:
  explicit Dynamics(double g);

  DerivativeToDelta get_derivative(const State &state) const;

private:
  // Gravity, modeled as an acceleration in the z direction.
  double g = 0;
};

} // namespace sp
