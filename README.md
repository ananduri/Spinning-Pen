# Spinning Pen simulation

See the file `analysis.pdf` for the writeup.

## Running the code
Building the code requires a C++ compiler supporting C++17 or later, and Bazel installed on a Linux system.

The code can be built on Linux by running
```sh
bazel build spinning_pen
```

To run the code in main(), use
```sh
bazel run spinning_pen
```

The tests can be run with
```sh
bazel test --test_output=all //:spinning_pen_tests
```
