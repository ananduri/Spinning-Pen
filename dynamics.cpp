#include "dynamics.hh"

namespace sp {

Dynamics::Dynamics(const double g) : g{g} {}

DerivativeToDelta Dynamics::get_derivative(const State &state) const {
  return [&state, this](const double dt) {
    return StateDelta{
        .linear_d = dt * state.linear_v,
        .linear_v = dt * g * Vec3::UnitZ(),
        .angular_d = dt * state.angular_v,
        .angular_v = 0,
    };
  };
}

} // namespace sp
