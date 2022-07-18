cc_binary(
  name = "spinning_pen",
  srcs = [
    "main.cpp",
  ],
  deps = [
    ":state",
    ":dynamics",
    ":pen",
    ":integrator",
  ],
)

cc_library(
  name = "state",
  srcs = ["state.cpp"],
  hdrs = ["state.hh"],
)

cc_library(
  name = "dynamics",
  srcs = ["dynamics.cpp"],
  hdrs = ["dynamics.hh"],
  deps = [":state"], 
)

cc_library(
  name = "pen",
  srcs = ["pen.cpp"],
  hdrs = ["pen.hh"],
  deps = [":state"],
)

cc_library(
  name = "integrator",
  # srcs = [
  #   "forward_euler.cpp",
  #   "integrator.cpp",
  #   "rk4.cpp",
  # ],
  hdrs = [
    "forward_euler.hh",
    "integrator.hh",
    "rk4.hh",
  ],
  deps = [
    ":dynamics",
    ":state",
  ],
)

cc_test(
  name = "state_test",
  size = "small",
  srcs = ["state_test.cpp"],
  deps = [  
    ":state",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_test(
  name = "pen_test",
  size = "small",
  srcs = ["pen_test.cpp"],
  deps = [  
    ":pen",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_test(
  name = "dynamics_test",
  size = "small",
  srcs = ["dynamics_test.cpp"],
  deps = [  
    ":state",
    ":dynamics",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_test(
  name = "forward_euler_test",
  size = "small",
  srcs = ["forward_euler_test.cpp"],
  deps = [  
    ":state",
    ":dynamics",
    ":pen",
    ":integrator",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_test(
  name = "rk4_test",
  size = "small",
  srcs = ["rk4_test.cpp"],
  deps = [  
    ":state",
    ":dynamics",
    ":pen",
    ":integrator",
    "@com_google_googletest//:gtest_main",
  ],
)

test_suite(
    name = "spinning_pen_tests",
    tests = [
        ":forward_euler_test",
        ":rk4_test",
	":pen_test",
	":state_test",
    ],
)
