load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

ARROW_COMMIT = "3afdc8746ae167978970717670d86ee20a083760"  # HEAD 2020/03/05
new_git_repository(
    name = "arrow",
    build_file = "//third_party:arrow.BUILD",
    commit = ARROW_COMMIT,
    remote = "https://github.com/apache/arrow.git",
)

PYBIND11_BAZEL_COMMIT = "311665c4255b70f38e58e9efeb73a9f54637032f"
http_archive(
  name = "pybind11_bazel",
  strip_prefix = "pybind11_bazel-%s" % PYBIND11_BAZEL_COMMIT,
  urls = ["https://github.com/pybind/pybind11_bazel/archive/%s.zip" % PYBIND11_BAZEL_COMMIT],
)
# We still require the pybind library.
PYBIND11_COMMIT = "fe755dce12766820a99eefbde32d6ceb0a828ca8"
http_archive(
  name = "pybind11",
  build_file = "@pybind11_bazel//:pybind11.BUILD",
  strip_prefix = "pybind11-%s" % PYBIND11_COMMIT,
  urls = ["https://github.com/pybind/pybind11/archive/%s.tar.gz" % PYBIND11_COMMIT],
)

load("@pybind11_bazel//:python_configure.bzl", "python_configure")
python_configure(name = "local_config_python")
