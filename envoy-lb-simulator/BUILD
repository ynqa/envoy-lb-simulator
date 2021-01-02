load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_platform_dep",
    "envoy_package",
)

envoy_package()

envoy_cc_binary(
    name = "envoy-lb-simulator",
    repository = "@envoy",
    srcs = [
        "main.cc",
    ],
    deps = [
        "@envoy//source/exe:envoy_main_common_lib",
    ] + envoy_cc_platform_dep("@envoy//source/exe:platform_impl_lib"),
)
