#include "pen.hh"

#include <cassert>
#include <cmath>

namespace sp {

Pen::Pen(const PenConfig &config, State initial_state)
    : mass{config.mass}, length{config.length},
      com_location{com_location}, state{std::move(initial_state)} {
  assert(mass > 0);
  assert(length > 0);
  assert(com_location >= 0);
  assert(com_location <= 1);

  I = mass * std::pow(length, 2) *
      (std::pow(com_location, 3) + std::pow(1 - com_location, 3)) / 3.0;
}

const State &Pen::get_state() const { return state; }

State &Pen::get_mutable_state() { return state; }

double get_moment_of_inertia(const Pen &pen) { return pen.I; }

} // namespace sp
