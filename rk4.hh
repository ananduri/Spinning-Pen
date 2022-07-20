#pragma once

#include <cassert>

#include "dynamics.hh"
#include "integrator.hh"
#include "state.hh"

namespace sp {

class RK4 final : public Integrator {
private:
  State step(const State &state, const Dynamics &dynamics, double t,
             double dt) const override {
    assert(dt > 0);
    const DerivativeToDelta k0 = dynamics.get_derivative(state);

    const auto intermediate_state1 = state + k0(0.5 * dt);
    const DerivativeToDelta k1 = dynamics.get_derivative(intermediate_state1);

    const auto intermediate_state2 = state + k1(0.5 * dt);
    const DerivativeToDelta k2 = dynamics.get_derivative(intermediate_state2);

    const auto intermediate_state3 = state + k2(dt);
    const DerivativeToDelta k3 = dynamics.get_derivative(intermediate_state3);

    return state + k0(dt / 6.) + k1(dt / 3.) + k2(dt / 3.) + k3(dt / 6.);
  }
};

} // namespace sp
