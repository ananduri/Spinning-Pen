#include "state.hh"

#include <iostream>

namespace sp {

State operator+(const State &state, const StateDelta &d_state) {
  return State{
      .linear_d = state.linear_d + d_state.linear_d,
      .linear_v = state.linear_v + d_state.linear_v,
      .axis = state.axis,
      .angular_d = state.angular_d + d_state.angular_d,
      .angular_v = state.angular_v + d_state.angular_v,
  };
}

std::ostream &operator<<(std::ostream &stream, const State &state) {
  return stream << "Position: " << state.linear_d.transpose() << "\n"
                << "Velocity: " << state.linear_v.transpose() << "\n"
                << "Rotation axis: " << state.axis.transpose() << "\n"
                << "Angle: " << state.angular_d << "\n"
                << "Angular speed: " << state.angular_v << "\n";
}

bool operator==(const State &lhs, const State &rhs) {
  return lhs.linear_d == rhs.linear_d && lhs.linear_v == rhs.linear_v &&
         lhs.axis == rhs.axis && lhs.angular_d == rhs.angular_d &&
         lhs.angular_v == rhs.angular_v;
}

} // namespace sp
