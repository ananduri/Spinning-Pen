#pragma once

#include <cmath>

#include "state.hh"

namespace sp {

struct PenConfig {
  double mass = 0;
  double length = 0;
  double com_location = 0;
};

// The pen is modeled as an infinitely thin rod with its center of
// mass (COM) located somewhere along its length (to take into account
// a non-uniform mass distribution).
class Pen final {
public:
  explicit Pen(const PenConfig &config, State initial_state);

  const State &get_state() const;

  State &get_mutable_state();

private:
  // The mass of the pen in kg.
  double mass = 0;

  // The length of the pen in meters.
  double length = 0;

  // The distance of the COM from the top of the pen, expressed as a
  // fraction of the pen's length.
  double com_location = 0;

  // The moment of inertia of the pen, in kg * meters^2
  // Since the pen is modeled as an infinitely thin rod, the moments
  // of inertia about the two principal axes that are perpendicular
  // to the pen's length are the same, and that quantity is what is
  // represented here. The moment about the axis going through the
  // pen is 0 using this model.
  double I = 0;

  State state;

  // Helper function used for testing.
  friend double get_moment_of_inertia(const Pen &pen);
};

} // namespace sp
