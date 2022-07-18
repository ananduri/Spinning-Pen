#pragma once

#include <cassert>

#include "dynamics.hh"
#include "integrator.hh"
#include "state.hh"

namespace sp {

class ForwardEuler final : public Integrator {
public:
  State step(const State &state, const Dynamics &dynamics, double t,
             double dt) const override {
    assert(dt > 0);
    const auto derivative = dynamics.get_derivative(state);
    const auto state_delta = derivative(dt);
    return state + state_delta;
  }
};

} // namespace sp
