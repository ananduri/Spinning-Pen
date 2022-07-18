#pragma once

#include "Eigen/Dense"

namespace sp {

using Vec3 = Eigen::Vector3d;

// A struct representing the state of the system being simulated; in this case,
// it represents the state of a pen in free-fall.
struct State {
  // The position of the center of mass (COM) of the pen in three-dimensional
  // space, in meters. This vector is situated in an orthonormal frame where
  // gravity acts along the negative z direction, and the x and y directions are
  // chosen arbitrarily.
  Vec3 linear_d = Vec3::Zero();

  // The linear velocity of the pen, in meters per second.
  Vec3 linear_v = Vec3::Zero();

  // The angular configuration of the pen in three-dimensional space,
  // using an axis-angle representation.
  Vec3 axis = Vec3::UnitZ();

  // The angular displacement of the pen about the rotation axis, in
  // radians.
  double angular_d = 0;

  // The angular velocity of the pen about the rotation axis, in
  // radians per second.
  double angular_v = 0;
};

// A struct representing a change in the state of the system. Instances can be
// added directly to State instances to obtain new State instances representing
// the changed system. Note that there is no field here representing a change in
// the axis of rotation of the pen; this is because changes in the axis of
// rotation are not currently supported.
struct StateDelta {
  Vec3 linear_d = Vec3::Zero();

  Vec3 linear_v = Vec3::Zero();

  double angular_d = 0;

  double angular_v = 0;
};

State operator+(const State &state, const StateDelta &d_state);

std::ostream &operator<<(std::ostream &stream, const State &state);

bool operator==(const State &lhs, const State &rhs);

} // namespace sp
