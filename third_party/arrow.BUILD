cc_library(
    name = "arrow",
    srcs = glob(
        [
            "cpp/src/arrow/*.cc",
            "cpp/src/arrow/c/*.cc",
            "cpp/src/arrow/compute/**/*.cc",
            "cpp/src/arrow/array/**/*.cc",
            "cpp/src/arrow/util/**/*.cc",
            "cpp/src/arrow/vendored/**/*.cpp",
            "cpp/src/arrow/vendored/**/*.hpp",
            "cpp/src/arrow/vendored/**/*.cc",
            "cpp/src/arrow/vendored/**/*.c",
            "cpp/src/arrow/vendored/**/*.h",
            "cpp/src/arrow/io/*.h",
            "cpp/src/arrow/io/*.cc",
        ],
        exclude = [
            # Excluding files which we don't depend on, but needs
            # additional dependencies like boost, snappy etc.
            "cpp/src/arrow/util/compression*",
            "cpp/src/arrow/**/*test*.cc",
            "cpp/src/arrow/**/*benchmark*.cc",
            "cpp/src/arrow/**/*hdfs*.cc",
            "cpp/src/arrow/**/*hdfs*.h",
            "cpp/src/arrow/ipc/json*.cc",
            "cpp/src/arrow/ipc/stream-to-file.cc",
            "cpp/src/arrow/ipc/file-to-stream.cc",
            "cpp/src/arrow/vendored/xxhash/**",
        ],
    ),
    hdrs = glob([
     "cpp/src/arrow/*.h",
     "cpp/src/arrow/array/*.h",
     "cpp/src/arrow/util/**/*.h",
     "cpp/src/arrow/compute/**/*.h",
     "cpp/src/arrow/c/*.h",
    ]),
    includes = [
        "cpp/src",
    ],
    deps = [
      ":xxhash",
      "@//third_party:arrow_config_h",
    ],
    visibility = ["@//:__subpackages__"],
)

cc_library(
    name = "xxhash",
    srcs = [],
    hdrs = [
        "cpp/src/arrow/vendored/xxhash/xxh3.h",
        "cpp/src/arrow/vendored/xxhash/xxhash.c",
        "cpp/src/arrow/vendored/xxhash/xxhash.h",
    ],
    copts = ["-Wno-implicit-fallthrough"],
    includes = ["."],
    visibility = ["//visibility:private"],
)

