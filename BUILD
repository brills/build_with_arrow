load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library")

pybind_extension(
  name = "my_ext",
  srcs = ["my_ext.cc"],
  deps = [
      ":array_util",
      ":array_wrapper",
  ],
)

cc_library(
  name = "array_util",
  srcs = ["array_util.cc"],
  hdrs = ["array_util.h"],
  deps = ["@arrow//:arrow"],
)

cc_library(
  name = "array_wrapper",
  srcs = ["array_wrapper.cc"],
  hdrs = ["array_wrapper.h"],
  deps = ["@arrow//:arrow"],
)
