#!/bin/bash
PYTHON_BIN_PATH=$(which python) ~/bin/bazel build :my_ext.so
