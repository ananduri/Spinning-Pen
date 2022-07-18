#include "dynamics.hh"

namespace sp {

Dynamics::Dynamics(const double g) : g{g} {}

// Potentiall, an "angular impulse term" could be included here to improve the
// simulation.
// We would then have to recalculate the axis of rotation.
// This could be used to simulate hitting the floor; the normal force in the z
// direction would create a torque about the COM and an angular impulse (in the
// yz plane); add it on to the existing angular momentum in the yz plane to get
// a new axis of rotation (and value of angular velocity; moment of inertia
// remains the same in this plane).
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
